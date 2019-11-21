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


#include "tt.h"


void initialize_zobrist() {
    std::default_random_engine random_generator(0);
    std::uniform_int_distribution<bitboard> random_distribution(1, ULLONG_MAX);

    for (bitboard * hash_pair : ZOBRIST) {
        hash_pair[0] = random_distribution(random_generator);
        hash_pair[1] = random_distribution(random_generator);
    }
}


tt_entry TranspositionTable::at(const bitboard hash_key) {
    size_t index = hash_key % tt_size;
    if ((tt + index)->hash == hash_key) {
        return *(tt + index);
    } else {
        return UNFILLED_ENTRY;
    };
}

void TranspositionTable::clear() {
    std::fill(tt, tt + tt_size, UNFILLED_ENTRY);
    entries = 0;
}

int TranspositionTable::hashfull() {
    return 1000 * entries / tt_size;
}

void TranspositionTable::insert(const bitboard hash_key, const int v, const std::array<bitboard, MAX_TURNS> pv) {
    size_t index = hash_key % tt_size;
    if (*(tt + index) == UNFILLED_ENTRY) {
        *(tt + index) = tt_entry{v, pv, hash_key};
        entries++;
    }
}

bitboard hash_board(const Board &b) {
    bitboard hash = 0;

    for (unsigned char position = 0; position < BOARD_SIZE; position++) {
        if ((b.yellow_bitboard >> position) & 1) {
            hash ^= ZOBRIST[position][0];
        } else if ((b.red_bitboard >> position) & 1) {
            hash ^= ZOBRIST[position][1];
        }
    }

    return hash;
}
