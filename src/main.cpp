// todo: create basic evaluation with piece-square tables
// todo: add alpha-beta pruning to search.
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
