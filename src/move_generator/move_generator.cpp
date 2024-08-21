// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_generator.h"
#include "../board/board.h"
#include <cassert>

CMoveGenerator::CMoveGenerator() {
    number_of_moves = 0;
}

void CMoveGenerator::generate_all() {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            switch (board.get_square(j, k)) {
                case WHITE_POWER:
                    generate_white_pawn_moves(j, k);
                    break;
            }
        }
    }
}

void CMoveGenerator::generate_white_pawn_moves(const int file, const int rank) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    const int next_rank = rank + 1;
    if (board.get_square(file, next_rank) == EMPTY_SQUARE) {
        store_move(file, rank, file, next_rank);
    }
}

SMove CMoveGenerator::get_random() const {
    if (number_of_moves <= 0) {
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for a temp function
    int index = rand() % number_of_moves;
    return move_list[index];
}

int CMoveGenerator::list_size() const {
    assert(number_of_moves <= MAX_MOVES_IN_CHESS_POSITION);
    return number_of_moves;
}

void CMoveGenerator::store_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    assert(source_file >= FILE_A);
    assert(source_file <= FILE_H);
    assert(source_rank >= RANK_1);
    assert(source_rank <= RANK_8);
    assert(target_file >= FILE_A);
    assert(target_file <= FILE_H);
    assert(target_rank >= RANK_1);
    assert(target_rank <= RANK_8);
    assert(number_of_moves < MAX_MOVES_IN_CHESS_POSITION);
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    move_list[number_of_moves] = new_move;
    number_of_moves++;
}
