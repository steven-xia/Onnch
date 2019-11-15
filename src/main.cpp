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

// todo: create basic evaluation with piece-square tables
// todo: add transposition tables to search.


#include "ui.cpp"

int main() {
    UI interface = UI(human, bot);
    interface.board.display();
    while (interface.board.get_game_result() == UNKNOWN) {
        interface.do_turn();
        interface.board.display();
    }

    if (interface.board.get_game_result() == YELLOW) {
        std::cout << "Player 1 wins!" << std::endl;
    } else if (interface.board.get_game_result() == RED) {
        std::cout << "Player 2 wins!" << std::endl;
    } else {
        std::cout << "Draw!" << std::endl;
    }

    return 0;
}
