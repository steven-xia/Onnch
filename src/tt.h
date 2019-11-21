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


#ifndef CONNECT4_TT_H
#define CONNECT4_TT_H

#include <array>
#include <cassert>
#include <random>

#include "bitboard.h"

bitboard ZOBRIST[BOARD_SIZE][2];

// 53 is the largest prime above 49 (BOARD_SIZE).
bitboard BIT_TO_ZOBRIST[53];

struct tt_entry {
    int score;
    bitboard hash;

    bool operator==(const tt_entry &x) {
        return x.hash == hash;
    }
};

constexpr unsigned long long MEBIBYTE = 1024 * 1024;
constexpr tt_entry UNFILLED_ENTRY = tt_entry{0, 1};


void initialize_zobrist();
bitboard hash_board(const Board &b);


class TranspositionTable {
private:
    size_t entries;
    size_t tt_size;
    tt_entry *tt;

public:
    explicit TranspositionTable(const int &size) {
        entries = 0;
        tt_size = (MEBIBYTE / sizeof(tt_entry)) * size;
        tt = new tt_entry[tt_size];

        initialize_zobrist();
        clear();
    }

    ~TranspositionTable() {
        delete[] tt;
    }

    tt_entry at(bitboard hash_key);

    void clear();

    int hashfull();

    void insert(bitboard hash_key, int v);
};


#endif // CONNECT4_TT_H
