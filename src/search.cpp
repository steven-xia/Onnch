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


#include "search.h"


unsigned long long get_current_time() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}


unsigned long long get_precise_time() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}


int negamax(Board &current_board, const unsigned char depth, const signed char color) {
    if (get_current_time() > MOVE_END_MILLISECONDS)
        return 0;

    searched_nodes++;

    game_const game_state = current_board.get_game_result();
    if (game_state != UNKNOWN) {
        return color * ((game_state == DRAW) ? 0
                                             : (game_state == YELLOW) ? MAX_SCORE - current_board.turn_number
                                                                      : -MAX_SCORE + current_board.turn_number);
    } else if (depth == 0) {
        return 0;  // replace with evaluation function
    }

    int score = -MAX_SCORE;
    for (bitboard &move : current_board.get_legal_moves()) {
        current_board.make_move(move);
        score = std::max(score, -negamax(current_board, depth - 1, -color));
        current_board.undo_move();
    }

    return score;
}

search_result _search_depth(Board &current_board, unsigned char depth) {
    const signed char search_side = (current_board.side_to_move == YELLOW) ? -1 : 1;

    int current_score = -MAX_SCORE;
    bitboard best_move = 0;
    int child_score;
    for (bitboard &move : current_board.get_legal_moves()) {
        current_board.make_move(move);
        child_score = -negamax(current_board, depth - 1, search_side);
        current_board.undo_move();

        if (child_score > current_score) {
            current_score = child_score;
            best_move = move;
        }
    }

    search_result return_value{
            current_score,
            best_move
    };
    return return_value;
}

search_result search(Board &current_board) {
    MOVE_END_MILLISECONDS = get_current_time() + MOVE_MILLISECONDS - MOVE_OVERHEAD;

    search_result current_result{}, new_result{};
    unsigned long long start_time, end_time;
    unsigned short search_depth;
    for (unsigned char end_turn = current_board.turn_number + 1; end_turn <= MAX_TURNS; end_turn++) {
        searched_nodes = 0;

        start_time = get_precise_time();
        search_depth = end_turn - current_board.turn_number;
        new_result = _search_depth(current_board, search_depth);
        if (get_current_time() > MOVE_END_MILLISECONDS)
            break;
        current_result = new_result;
        end_time = get_precise_time();

        std::cout << "info";
        std::cout << " depth " << search_depth;
        std::cout << " nodes " << searched_nodes;
        std::cout << " nps " << 1000000000 * searched_nodes / (end_time - start_time);
        std::cout << " score " << current_result.score;
        std::cout << std::endl;

        if (abs(current_result.score) >= MAX_SCORE - MAX_TURNS)
            break;
    }

    return current_result;
}
