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


#include "bitboard.h"


std::array<bitboard, BOARD_SIZE> split_bitboard(const bitboard &bb) {
    /*
     * summary: split a bitboard into individual bits.
     *
     * return: vector of all the individual bits in bitboards.
     *
     * implementation: iterates through all the possible bits and checks if
     * they exist in the input bitboard. if they do, add them to the return
     * vector.
     */

    std::array<bitboard, BOARD_SIZE> bit_list{0};

    bitboard possible_bit;
    unsigned char current_index = 0;
    for (unsigned char s = 0; s < BOARD_SIZE; s++) {
        possible_bit = bb & ((bitboard) 1 << s);
        if (possible_bit) {
            bit_list[current_index] = possible_bit;
            current_index++;
        }
    }

    return bit_list;
}

std::array<bitboard, BOARD_WIDTH> split_bitboard_columns(const bitboard &bb) {
    /*
     * summary: split a bitboard into individual columns.
     *
     * return: vector of all the bits in each column in bitboards.
     *
     * implementation: iterates through all the (already calculated) board
     * column bitboards and checks the overlap with the input bitboard. if
     * there is overlap, add the overlap to the return vector.
     */

    std::array<bitboard, BOARD_WIDTH> bit_list{0};

    bitboard possible_bit;
    unsigned char current_index = 0;
    for (size_t column_index : COLUMN_ORDER) {
        possible_bit = bb & COLUMN_ARRAY[column_index];
        if (possible_bit) {
            bit_list[current_index] = possible_bit;
            current_index++;
        }
    }

    return bit_list;
};


game_const Board::get_game_result() {
    /*
     * summary: get the current game result.
     *
     * return: the current game state as one of {RED, YELLOW, DRAW, UNKNOWN}.
     *
     * implementation: first determines which side to check; only cares about
     * the side that has just moved because they are the only one that could
     * have won last move. then, checks whether the side has 4 pieces in a
     * row. if they do, respond with their side. otherwise if the game is at
     * the maximum amount of moves, it is a `DRAW`. otherwise, `UNKNOWN`.
     */

    // determine the side to check for a win.
    game_const win_result;
    bitboard active_pieces;
    if (side_to_move == YELLOW) {
        win_result = RED;
        active_pieces = red_bitboard;
    } else {
        win_result = YELLOW;
        active_pieces = yellow_bitboard;
    }

    // determine whether the side has won.
    bitboard temp_bb;

    temp_bb = active_pieces & (active_pieces << UP);
    if (temp_bb & (temp_bb << 2 * UP))
        return win_result;

    temp_bb = active_pieces & (active_pieces << UP_RIGHT);
    if (temp_bb & (temp_bb << 2 * UP_RIGHT))
        return win_result;

    temp_bb = active_pieces & (active_pieces << RIGHT);
    if (temp_bb & (temp_bb << 2 * RIGHT))
        return win_result;

    temp_bb = active_pieces & (active_pieces << DOWN_RIGHT);
    if (temp_bb & (temp_bb << 2 * DOWN_RIGHT))
        return win_result;

    // return `DRAW` if game is over.
    if (turn_number == MAX_TURNS)
        return DRAW;

    // otherwise, result is still unknown.
    return UNKNOWN;
}

std::array<bitboard, BOARD_WIDTH> Board::get_legal_moves() {
    /*
     * summary: get a vector of legal moves.
     *
     * return: a vector of all the legal move bits as bitboards.
     *
     * implementation: finds the bitboard of all legal moves and splits it by
     * the columns (there is only one move per column).
     */

    bitboard all_pieces = EMPTY_BOARD | yellow_bitboard | red_bitboard;
    return split_bitboard_columns((all_pieces << UP) & (~all_pieces));
}

void Board::make_move(const bitboard &bb) {
    /*
     * summary: make a new move.
     *
     * return: void.
     *
     * implementation: first determines which side to move, then adds the move
     * bitboard to the side's bitboard and change the side to move. then,
     * add the move to the array of past moves and increment the move number.
     */

    if (side_to_move == YELLOW) {
        yellow_bitboard += bb;
        side_to_move = RED;
    } else {
        red_bitboard += bb;
        side_to_move = YELLOW;
    }

    past_moves[turn_number] = bb;
    turn_number++;
}

void Board::undo_move() {
    /*
     * summary: undo the last move.
     *
     * return: void.
     *
     * implementation: first decrements the turn number. then, removes the
     * last move from the proper piece bitboard.
     */

    turn_number--;

    if (side_to_move == YELLOW) {
        red_bitboard -= past_moves[turn_number];
        side_to_move = RED;
    } else {
        yellow_bitboard -= past_moves[turn_number];
        side_to_move = YELLOW;
    }
}

void Board::display() {
    /*
     * summary: display the current board.
     *
     * return: void.
     *
     * implementation: first processes the piece bitboards into a 6x7 array
     * with piece locations. then, displays the board based on the array.
     */

    game_const rows_representation[6][7];
    for (unsigned char s = 0; s < BOARD_SIZE; s++) {
        if (s % 7 == 0)
            continue;

        if (yellow_bitboard & ((bitboard) 1 << s)) {
            rows_representation[6 - (s % 7)][s / 7] = YELLOW;
        } else if (red_bitboard & ((bitboard) 1 << s)) {
            rows_representation[6 - (s % 7)][s / 7] = RED;
        } else {
            rows_representation[6 - (s % 7)][s / 7] = UNKNOWN;
        }
    }

    for (auto &row : rows_representation) {
        std::cout << "|";
        for (auto &piece : row) {
            if (piece == YELLOW)
                std::cout << " " << "@" << " |";
            else if (piece == RED)
                std::cout << " " << "-" << " |";
            else
                std::cout << " " << " " << " |";
        }
        std::cout << std::endl;
    }
    std::cout << "  1   2   3   4   5   6   7" << std::endl;
}
