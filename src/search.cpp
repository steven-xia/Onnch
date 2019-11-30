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


search_result negamax(Board &current_board, const unsigned char &depth, const signed char &color,
                      const bitboard &hash, int alpha = -MAX_SCORE, const int &beta = MAX_SCORE) {
    search_result return_value{-MAX_SCORE, {0}};
    if (searched_nodes > time_check_nodes) {
        unsigned long long current_time = get_current_time();
        if (current_time > MOVE_END_MILLISECONDS)
            return return_value;
        else
            time_check_nodes += NPS * (MOVE_END_MILLISECONDS - current_time) / 1000;
    }

    searched_nodes++;

    const tt_entry past_result = TT.at(hash);
    if (abs(past_result.score) > MAX_SCORE - MAX_TURNS || past_result.depth >= depth) {
        return_value.score = past_result.score;
        return return_value;
    }

    const game_const game_state = current_board.get_game_result();
    if (game_state != UNKNOWN) {
        return_value.score = color * (
                (game_state == DRAW) ? 0
                                     : (game_state == YELLOW) ? MAX_SCORE - current_board.turn_number
                                                              : -MAX_SCORE + current_board.turn_number
        );
        return return_value;
    } else if (depth == 0) {
        return_value.score = 0;  // replace with evaluation function
        return return_value;
    }

    const bitboard legal_moves = current_board.get_legal_moves();

    search_result child_result{};
    bitboard move;
    for (const bitboard &column_index : COLUMN_ORDER) {
        move = legal_moves & COLUMN_ARRAY[column_index];

        if (!move)
            continue;

        current_board.make_move(move);
        child_result = negamax(
                current_board, depth - 1, -color,
                hash ^ ZOBRIST[BIT_TO_ZOBRIST[(move % 53)]][current_board.turn_number % 2],
                -beta, -alpha
        );
        current_board.undo_move(move);

        child_result.score = -child_result.score;
        if (child_result.score > return_value.score) {
            return_value = child_result;
            return_value.pv[depth - 1] = move;

            alpha = std::max(alpha, return_value.score);
            if (alpha >= beta)
                break;
        }
    }

    TT.insert(hash, return_value.score, depth);

    return return_value;
}

search_result search(Board &current_board) {
    const signed char search_side = (current_board.turn_number % 2 == 0) ? -1 : 1;
    const unsigned long long turn_start_time = get_current_time();
    MOVE_END_MILLISECONDS = turn_start_time + MOVE_MILLISECONDS - MOVE_OVERHEAD;
    TT.clear();

    search_result current_result{}, new_result{};
    unsigned long long search_start_time, search_end_time;
    unsigned short search_depth;
    for (unsigned char end_turn = current_board.turn_number + 1; end_turn <= MAX_TURNS; end_turn++) {
        searched_nodes = 0;
        time_check_nodes = NPS * (MOVE_END_MILLISECONDS - get_current_time()) / 1000;

        search_start_time = get_precise_time();
        search_depth = end_turn - current_board.turn_number;
        new_result = negamax(
                current_board, search_depth + 1, search_side, hash_board(current_board), -MAX_SCORE, MAX_SCORE
        );
        if (get_current_time() > MOVE_END_MILLISECONDS)
            break;
        current_result = new_result;
        search_end_time = get_precise_time();

        std::cout << "info";
        std::cout << " depth " << search_depth;
        std::cout << " score " << current_result.score;
        std::cout << " nodes " << searched_nodes;
        std::cout << " nps " << 1000000000 * searched_nodes / (search_end_time - search_start_time);
        std::cout << " hashfull " << TT.hashfull();
        std::cout << " time " << get_current_time() - turn_start_time;
        std::cout << " pv";
        for (size_t i = MAX_TURNS; i > 0; i--) {
            if (current_result.pv[i - 1])
                for (short s = 0;; s++) {
                    if ((current_result.pv[i - 1] >> s) & 1) {
                        std::cout << " " << (s / 7) + 1;
                        break;
                    }
                }
        }
        std::cout << std::endl;

        if (abs(current_result.score) >= MAX_SCORE - MAX_TURNS)
            break;
    }

    return current_result;
}
