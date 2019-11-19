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

    for (unsigned long long &hash : ZOBRIST) {
        hash = random_distribution(random_generator);
    }
}


int TranspositionTable::at(const Board &b) {
    size_t index = hash(b) % tt_size;
    return *(tt + index);
}

void TranspositionTable::clear() {
    memset(tt, UNFILLED_ENTRY, sizeof(*tt) * tt_size);
}

bitboard TranspositionTable::hash(const Board &b) {
    bitboard all_pieces = EMPTY_BOARD | b.yellow_bitboard | b.red_bitboard;
    all_pieces = ((all_pieces << UP) & (~all_pieces)) | b.yellow_bitboard;

    bitboard hash = 0;
    for (unsigned char position = 0; position < BOARD_SIZE; position++) {
        if ((all_pieces >> position) & 1) {
            hash ^= ZOBRIST[position];
        }
    }

    return hash;
}

void TranspositionTable::insert(const Board &b, const int v) {
    size_t index = hash(b) % tt_size;
    if (*(tt + index) == UNFILLED_ENTRY) {
        *(tt + index) = v;
    }
}
