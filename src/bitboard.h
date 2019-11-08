#ifndef CONNECT4_BITBOARD_H
#define CONNECT4_BITBOARD_H

#include <vector>

//#define bitboard unsigned long long
typedef unsigned long long bitboard;

enum game_const : unsigned char {
    YELLOW, RED, DRAW, UNKNOWN,
    MAX_TURNS = 42,
    BOARD_SIZE = 49
};

enum direction : signed char {
    UP = 1,
    RIGHT = 7,
    DOWN = -UP,
    LEFT = -RIGHT,

    UP_RIGHT = UP + RIGHT,
    UP_LEFT = UP + LEFT,
    DOWN_RIGHT = DOWN + RIGHT,
    DOWN_LEFT = DOWN + LEFT
};

constexpr bitboard EMPTY_BOARD = 4432676798593;
constexpr bitboard FULL_BOARD = 18446739641032753022;

constexpr bitboard COLUMN_ARRAY[7] = {
        127, 16256, 2080768, 266338304, 34091302912, 4363686772736, 558551906910208
};


// split a bitboard into individual bits.
std::vector<bitboard> split_bitboard(const bitboard &bb);

// split a bitboard into individual columns.
std::vector<bitboard> split_bitboard_columns(const bitboard &bb);


class Board {
public:
    bitboard red_bitboard = 0;
    bitboard yellow_bitboard = 0;
    game_const side_to_move = YELLOW;
    unsigned char turn_number = 0;
    bitboard past_moves[MAX_TURNS] = {0};

    // initialise an empty board object.
    Board() = default;

    // get the current game result.
    game_const get_game_result();

    // get a vector of legal moves.
    std::vector<bitboard> get_legal_moves();

    // make a new move.
    void make_move(const bitboard &bb);

    // undo the last move.
    void undo_move();

    // display the current board.
    void display();
};


#endif  // CONNECT4_BITBOARD_H
