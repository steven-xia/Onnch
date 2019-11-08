// todo: create basic evaluation with piece-square tables
// todo: add alpha-beta pruning to search.
// todo: add transposition tables to search.


#include "ui.cpp"

int main() {
    UI interface = UI(human, bot);
    interface.board.display();
    std::cout << std::endl;
    while (interface.board.get_game_result() == UNKNOWN) {
        interface.do_turn();
        interface.board.display();
        std::cout << std::endl;
    }

    if (interface.board.get_game_result() == YELLOW) {
        std::cout << "Player 1 wins!" << std::endl;
    } else {
        std::cout << "Player 2 wins!" << std::endl;
    }

    return 0;
}
