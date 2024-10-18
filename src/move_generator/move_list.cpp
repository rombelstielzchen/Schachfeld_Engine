// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "../board/board.h"

CMoveList::CMoveList() {
    number_of_moves = 0;
    consumer_counter = 0;
}

SMove CMoveList::get_random() const {
    if (number_of_moves <= 0) {
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for an early proof of concept
    int index = rand() % number_of_moves;
    return move_list[index];
}

SMove CMoveList::get_next() {
    if (consumer_counter >= number_of_moves) {
        return NULL_MOVE;
    }
    SMove result = move_list[consumer_counter];
    ++consumer_counter;
    assert(move_in_range(result));
    return result;
}

int CMoveList::list_size() const {
    assert(number_of_moves <= MAX_MOVES_IN_CHESS_POSITION);
    return number_of_moves;
}

void CMoveList::store_move(const SMove &move) {
    assert(move_in_range(move));
//    std::cerr << int(source_file) << ", " << int(source_rank) << " -> " << int(target_file) << ", " << int(target_rank) << std::endl;
    assert(number_of_moves < MAX_MOVES_IN_CHESS_POSITION);
    move_list[number_of_moves] = move;
    ++number_of_moves;
}

void CMoveList::store_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = move_type;
    store_move(new_move);
}

void CMoveList::store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    if (target_rank == RANK_8) {
        // Promotions in the order of likelihood
        new_move.move_type = WHITE_QUEEN;
        store_move(new_move);
        new_move.move_type = WHITE_KNIGHT;
        store_move(new_move);
        new_move.move_type = WHITE_ROOK;
        store_move(new_move);
        new_move.move_type = WHITE_BISHOP;
        store_move(new_move);
    } else if (target_rank == RANK_1) {
        new_move.move_type = BLACK_QUEEN;
        store_move(new_move);
        new_move.move_type = BLACK_KNIGHT;
        store_move(new_move);
        new_move.move_type = BLACK_ROOK;
        store_move(new_move);
        new_move.move_type = BLACK_BISHOP;
        store_move(new_move);
    } else { 
        new_move.move_type = MOVE_TYPE_NORMAL;
        store_move(new_move);
    }
}


