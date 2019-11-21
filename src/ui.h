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

std::string LICENSE_MSG = "Onnch  Copyright (C) 2019  Steven Xia\n"
                          "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
                          "This is free software, and you are welcome to redistribute it\n"
                          "under certain conditions; type `show c' for details.";

std::string LICENSE_W = "Onnch is distributed in the hope that it will be useful,\n"
                        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
                        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
                        "GNU General Public License for more details.";

std::string LICENSE_C = "Onnch is free software: you can redistribute it and/or modify\n"
                        "it under the terms of the GNU General Public License as published by\n"
                        "the Free Software Foundation, either version 3 of the License, or\n"
                        "(at your option) any later version.";


bitboard get_bot_move(Board &current_board);

bitboard get_human_move(const bitboard &legal_moves);


class UI {
public:
    player player1, player2;
    Board board;

    UI(player p1, player p2) {
        std::cout << LICENSE_MSG << std::endl;

        player1 = p1;
        player2 = p2;
        board = Board();
    }

    void do_turn();
};


#endif  // CONNECT4_UI_H
