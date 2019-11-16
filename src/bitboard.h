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


#ifndef CONNECT4_BITBOARD_H
#define CONNECT4_BITBOARD_H

#include <array>

//#define bitboard unsigned long long
typedef unsigned long long bitboard;

enum game_const : unsigned char {
    YELLOW, RED, DRAW, UNKNOWN,
    BOARD_WIDTH = 7,
    MAX_TURNS = 42,
    BOARD_SIZE = 49
};

enum direction : signed char {
    UP = 1,
    RIGHT = 7,
    DOWN = -UP,
    LEFT = -RIGHT,

    UP_RIGHT = UP + RIGHT,
    UP_LEFT = UP + LEFT,
    DOWN_RIGHT = DOWN + RIGHT,
    DOWN_LEFT = DOWN + LEFT
};

constexpr bitboard EMPTY_BOARD = 4432676798593;
constexpr bitboard FULL_BOARD = 18446739641032753022;

constexpr bitboard COLUMN_ARRAY[7] = {
        127, 16256, 2080768, 266338304, 34091302912, 4363686772736, 558551906910208
};

constexpr size_t COLUMN_ORDER[7] = {
        3, 2, 4, 1, 5, 0, 6
};


// split a bitboard into individual bits.
std::array<bitboard, BOARD_SIZE> split_bitboard(const bitboard &bb);

// split a bitboard into individual columns.
std::array<bitboard, BOARD_WIDTH> split_bitboard_columns(const bitboard &bb);


class Board {
public:
    bitboard red_bitboard = 0;
    bitboard yellow_bitboard = 0;
    game_const side_to_move = YELLOW;
    unsigned char turn_number = 0;
    bitboard past_moves[MAX_TURNS] = {0};

    // initialise an empty board object.
    Board() = default;

    // get the current game result.
    game_const get_game_result();

    // get an array of legal moves.
    std::array<bitboard, BOARD_WIDTH> get_legal_moves();

    // make a new move.
    void make_move(const bitboard &bb);

    // undo the last move.
    void undo_move();

    // display the current board.
    void display();
};


#endif  // CONNECT4_BITBOARD_H
