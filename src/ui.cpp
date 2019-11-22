/*
  Onnch, a Connect 4 bot specializing in short time control games.
  Copyright (C) 2019  Steven Xia

  Onnch is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Onnch is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "ui.h"


bitboard get_bot_move(Board &current_board) {
    search_result result = search(current_board);
    for (size_t i = MAX_TURNS; i > 0; i--) {
        if (result.pv[i - 1])
            return result.pv[i - 1];
    }

    return 0;
}

bitboard get_human_move(const bitboard &legal_moves) {
    std::string user_input;
    int input_as_number = 0;
    bitboard possible_move = 0;
    do {
        std::cout << "> " << std::flush;
        std::getline(std::cin, user_input);

        if (user_input.length() == 0) {
            std::cout << "Please give an input." << std::endl;
            continue;
        }

        if (user_input == "show w") {
            std::cout << LICENSE_W << std::endl;
            continue;
        } else if (user_input == "show c") {
            std::cout << LICENSE_C << std::endl;
            continue;
        }

        input_as_number = (int) user_input.at(0) - (int) '0';
        if (!(0 < input_as_number && input_as_number <= 7)) {
            std::cout << "Please give a valid input." << std::endl;
            continue;
        }

        possible_move = COLUMN_ARRAY[input_as_number - 1] & legal_moves;
    } while (!possible_move);

    return possible_move;
}


void UI::do_turn() {
    player current_player = (board.turn_number % 2 == 0) ? player1 : player2;

    bitboard player_move;
    if (current_player == human) {
        player_move = get_human_move(board.get_legal_moves());
    } else {
        player_move = get_bot_move(board);
    }

    board.make_move(player_move);
}
