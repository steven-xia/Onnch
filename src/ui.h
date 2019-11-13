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


#ifndef CONNECT4_UI_H
#define CONNECT4_UI_H

#include <iostream>
#include <string>
#include <vector>

#include "bitboard.cpp"
#include "search.cpp"

enum player : unsigned char {
    human, bot
};


bitboard get_bot_move(Board &current_board);

bitboard get_human_move(const bitboard &legal_moves);


class UI {
public:
    player player1, player2;
    Board board;

    UI(player p1, player p2) {
        player1 = p1;
        player2 = p2;
        board = Board();
    }

    void do_turn();
};


#endif  // CONNECT4_UI_H
