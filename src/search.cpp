#include "search.h"


int negamax(Board &current_board, const unsigned char depth, const signed char color) {
    game_const game_state = current_board.get_game_result();
    if (game_state != UNKNOWN) {
        return color * ((game_state == DRAW) ? 0
                                             : (game_state == YELLOW) ? MAX_SCORE - current_board.turn_number
                                                                      : -MAX_SCORE + current_board.turn_number);
    } else if (depth == 0) {
        return 0;  // replace with evaluation function
    }

    int score = -MAX_SCORE;
    for (bitboard &move : current_board.get_legal_moves()) {
        current_board.make_move(move);
        score = std::max(score, -negamax(current_board, depth - 1, -color));
        current_board.undo_move();
    }

    return score;
}

search_result search(Board &current_board, const unsigned char depth) {
    const signed char search_side = (current_board.side_to_move == YELLOW) ? -1 : 1;

    int current_score = -MAX_SCORE;
    bitboard best_move = 0;
    int child_score;
    for (bitboard &move : current_board.get_legal_moves()) {
        current_board.make_move(move);
        child_score = -negamax(current_board, depth - 1, search_side);
        current_board.undo_move();

        if (child_score > current_score) {
            current_score = child_score;
            best_move = move;
        }
    }

    search_result return_value{
            current_score,
            best_move
    };
    return return_value;
}
