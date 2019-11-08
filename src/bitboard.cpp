#include "bitboard.h"


std::vector<bitboard> split_bitboard(const bitboard &bb) {
    /*
     * summary: split a bitboard into individual bits.
     *
     * return: vector of all the individual bits in bitboards.
     *
     * implementation: iterates through all the possible bits and checks if
     * they exist in the input bitboard. if they do, add them to the return
     * vector.
     */

    std::vector<bitboard> bit_list;

    bitboard possible_bit;
    for (unsigned char s = 0; s < BOARD_SIZE; s++) {
        possible_bit = bb & ((bitboard) 1 << s);
        if (possible_bit)
            bit_list.push_back(possible_bit);
    }

    return bit_list;
}

std::vector<bitboard> split_bitboard_columns(const bitboard &bb) {
    /*
     * summary: split a bitboard into individual columns.
     *
     * return: vector of all the bits in each column in bitboards.
     *
     * implementation: iterates through all the (already calculated) board
     * column bitboards and checks the overlap with the input bitboard. if
     * there is overlap, add the overlap to the return vector.
     */

    std::vector<bitboard> bit_list;

    bitboard possible_bit;
    for (bitboard column_bitboard : COLUMN_ARRAY) {
        possible_bit = bb & column_bitboard;
        if (possible_bit)
            bit_list.push_back(possible_bit);
    }

    return bit_list;
};


game_const Board::get_game_result() {
    /*
     * summary: get the current game result.
     *
     * return: the current game state as one of {RED, YELLOW, DRAW, UNKNOWN}.
     *
     * implementation: first determines which side to check; only cares about
     * the side that has just moved because they are the only one that could
     * have won last move. then, checks whether the side has 4 pieces in a
     * row. if they do, respond with their side. otherwise if the game is at
     * the maximum amount of moves, it is a `DRAW`. otherwise, `UNKNOWN`.
     */

    // determine the side to check for a win.
    game_const win_result;
    bitboard active_pieces;
    if (side_to_move == YELLOW) {
        win_result = RED;
        active_pieces = red_bitboard;
    } else {
        win_result = YELLOW;
        active_pieces = yellow_bitboard;
    }

    // determine whether the side has won.
    if ((active_pieces & (active_pieces << UP)
         & (active_pieces << (2 * UP)) & (active_pieces << (3 * UP)))
        || (active_pieces & (active_pieces << UP_RIGHT)
            & (active_pieces << (2 * UP_RIGHT)) & (active_pieces << (3 * UP_RIGHT)))
        || (active_pieces & (active_pieces << RIGHT)
            & (active_pieces << (2 * RIGHT)) & (active_pieces << (3 * RIGHT)))
        || (active_pieces & (active_pieces << DOWN_RIGHT)
            & (active_pieces << (2 * DOWN_RIGHT)) & (active_pieces << (3 * DOWN_RIGHT)))) {
        return win_result;
    }

    // return `DRAW` if game is over.
    if (turn_number == MAX_TURNS)
        return DRAW;

    // otherwise, result is still unknown.
    return UNKNOWN;
}

std::vector<bitboard> Board::get_legal_moves() {
    /*
     * summary: get a vector of legal moves.
     *
     * return: a vector of all the legal move bits as bitboards.
     *
     * implementation: finds the bitboard of all legal moves and splits it by
     * the columns (there is only one move per column).
     */

    bitboard all_pieces = EMPTY_BOARD | yellow_bitboard | red_bitboard;
    return split_bitboard_columns((all_pieces << UP) & (~all_pieces));
}

void Board::make_move(const bitboard &bb) {
    /*
     * summary: make a new move.
     *
     * return: void.
     *
     * implementation: first determines which side to move, then adds the move
     * bitboard to the side's bitboard and change the side to move. then,
     * add the move to the array of past moves and increment the move number.
     */

    if (side_to_move == YELLOW) {
        yellow_bitboard += bb;
        side_to_move = RED;
    } else {
        red_bitboard += bb;
        side_to_move = YELLOW;
    }

    past_moves[turn_number] = bb;
    turn_number++;
}

void Board::undo_move() {
    /*
     * summary: undo the last move.
     *
     * return: void.
     *
     * implementation: first decrements the turn number. then, removes the
     * last move from the proper piece bitboard.
     */

    turn_number--;

    if (side_to_move == YELLOW) {
        red_bitboard -= past_moves[turn_number];
        side_to_move = RED;
    } else {
        yellow_bitboard -= past_moves[turn_number];
        side_to_move = YELLOW;
    }
}

void Board::display() {
    /*
     * summary: display the current board.
     *
     * return: void.
     *
     * implementation: first processes the piece bitboards into a 6x7 array
     * with piece locations. then, displays the board based on the array.
     */

    game_const rows_representation[6][7];
    for (unsigned char s = 0; s < BOARD_SIZE; s++) {
        if (s % 7 == 0)
            continue;

        if (yellow_bitboard & ((bitboard) 1 << s)) {
            rows_representation[6 - (s % 7)][s / 7] = YELLOW;
        } else if (red_bitboard & ((bitboard) 1 << s)) {
            rows_representation[6 - (s % 7)][s / 7] = RED;
        } else {
            rows_representation[6 - (s % 7)][s / 7] = UNKNOWN;
        }
    }

    for (auto &row : rows_representation) {
        std::cout << "|";
        for (auto &piece : row) {
            if (piece == YELLOW)
                std::cout << " " << "@" << " |";
            else if (piece == RED)
                std::cout << " " << "-" << " |";
            else
                std::cout << " " << " " << " |";
        }
        std::cout << std::endl;
    }
    std::cout << "  1   2   3   4   5   6   7" << std::endl;
}
