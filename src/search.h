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


#ifndef CONNECT4_SEARCH_H
#define CONNECT4_SEARCH_H

#include <algorithm>
#include <climits>

#include "bitboard.h"

struct search_result {
    int score;
    bitboard best_move;
};

constexpr int MAX_SCORE = INT_MAX;


int negamax(Board &current_board, unsigned char depth, signed char color);

search_result search(Board &current_board, unsigned char depth);


#endif  // CONNECT4_SEARCH_H
