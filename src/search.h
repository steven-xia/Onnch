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
