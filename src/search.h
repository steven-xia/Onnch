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


#ifndef CONNECT4_SEARCH_H
#define CONNECT4_SEARCH_H

#include <algorithm>
#include <array>
#include <chrono>
#include <climits>

#include "bitboard.h"
#include "tt.cpp"

#define HASH_MB 256
#define MOVE_MILLISECONDS 1000
#define MOVE_OVERHEAD 10
#define NPS (unsigned long long) 1034482

struct search_result {
    int score;
    std::array<bitboard, MAX_TURNS> pv;
};

constexpr int MAX_SCORE = INT_MAX;

unsigned long long MOVE_END_MILLISECONDS;
unsigned long long searched_nodes;
unsigned long long time_check_nodes;
auto TT = TranspositionTable(HASH_MB);


unsigned long long get_current_time();

unsigned long long get_precise_time();

search_result negamax(Board &current_board, const unsigned char &depth, const signed char &color, const bitboard &hash,
                      int alpha, const int &beta);

search_result search(Board &current_board);


#endif  // CONNECT4_SEARCH_H
