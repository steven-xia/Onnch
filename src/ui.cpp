/*
  Onnch, a Connect 4 bot specializing in short time control games.
  Copyright (C) 2019  Steven Xia

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "ui.h"


bitboard get_bot_move(Board &current_board) {
    search_result result = search(current_board);
    return result.best_move;
}

bitboard get_human_move(const bitboard &legal_moves) {
    unsigned int user_input;
    bitboard possible_move = 0;
    do {
        std::cout << ">" << std::flush;
        std::cin >> user_input;
        if (!(0 < user_input && user_input <= 7))
            continue;

        possible_move = COLUMN_ARRAY[user_input - 1] & legal_moves;
    } while (!possible_move);

    return possible_move;
}


void UI::do_turn() {
    player current_player = (board.turn_number % 2 == 0) ? player1 : player2;

    bitboard player_move;
    bitboard legal_moves_bitboard = 0;
    if (current_player == human) {
        for (auto bit : board.get_legal_moves())
            legal_moves_bitboard |= bit;
        player_move = get_human_move(legal_moves_bitboard);
    } else {
        player_move = get_bot_move(board);
    }

    board.make_move(player_move);
}
