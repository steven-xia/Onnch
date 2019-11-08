#ifndef CONNECT4_UI_H
#define CONNECT4_UI_H

#include <iostream>
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
