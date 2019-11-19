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

#include <random>
#include <cassert>

#include "bitboard.h"

constexpr unsigned long long MEBIBYTE = 1024 * 1024;
constexpr int UNFILLED_ENTRY = -724249388;

bitboard ZOBRIST[BOARD_SIZE];


void initialize_zobrist();


class TranspositionTable {
private:
    size_t tt_size;
    int *tt;

public:
    explicit TranspositionTable(const int &size) {
        tt_size = (MEBIBYTE / sizeof(int)) * size;
        tt = new int[tt_size];

        initialize_zobrist();
        clear();
    }

    ~TranspositionTable() {
        delete[] tt;
    }

    int at(const Board &b);

    void clear();

    static bitboard hash(const Board &b);

    void insert(const Board &b, int v);
};


#endif // CONNECT4_TT_H
