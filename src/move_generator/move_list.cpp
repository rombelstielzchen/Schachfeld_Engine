// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "../board/board.h"

CMoveList::CMoveList() {
    first_capture = LIST_ORIGIN;
    last_silent_move = LIST_ORIGIN;
    consumer_position = LIST_ORIGIN;
}

SMove CMoveList::get_random() const {
    if (list_size() <= 0) {
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for an early proof of concept
    unsigned int index = first_capture + rand() % list_size();
    assert(index >= first_capture);
    assert(index < last_silent_move);
    return bidirectional_move_list[index];
}

SMove CMoveList::get_next() {
    assert(consumer_position >= first_capture);
    if (consumer_position >= last_silent_move) {
        return NULL_MOVE;
    }
    SMove result = bidirectional_move_list[consumer_position];
    ++consumer_position;
    assert(move_in_range(result));
    return result;
}

SMove CMoveList::lookup_move(const std::string &text_move) const {
    const SMove basic_move = text_to_basic_move(text_move);
    assert(last_silent_move >= first_capture);
    for (int j = first_capture; j < last_silent_move; ++j) {
        if (move_coords_are_equal(basic_move, bidirectional_move_list[j])) {
            // TODO: possible under-promotions
            return bidirectional_move_list[j];
        }
    }
    return NULL_MOVE;
}

int CMoveList::list_size() const {
    assert(last_silent_move >= first_capture);
    return (last_silent_move - first_capture);
}

void CMoveList::store_move(const SMove &move) {
    assert(move_in_range(move));
//    std::cerr << int(source_file) << ", " << int(source_rank) << " -> " << int(target_file) << ", " << int(target_rank) << std::endl;
    bidirectional_move_list[last_silent_move] = move;
    ++last_silent_move;
}

void CMoveList::store_silent_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = move_type;
    store_move(new_move);
}

void CMoveList::store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    if (target_rank == RANK_8) {
        store_white_promotions(source_file, RANK_7, target_file, RANK_8);
    } else if (target_rank == RANK_1) {
        store_black_promotions(source_file, RANK_2, target_file, RANK_1);
    } else if (source_file != target_file) {
        store_capture(source_file, source_rank, target_file, target_rank);
    } else { 
        store_silent_move(source_file, source_rank, target_file, target_rank);
    }
}


void CMoveList::store_capture(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    // Temp
    store_silent_move(source_file, source_rank, target_file, target_rank);
}

void CMoveList::store_pawn_capture(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    // TODO: promo
    store_capture(source_file, source_rank, target_file, target_rank);
}

void CMoveList::store_eng_passeng(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = MOVE_TYPE_ENG_PASSENG;
    store_capture(new_move);
}

void CMoveList::store_white_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    // Promotions in the order of likelihood.
    // Promotions get treated as "captures", they chamge the material balance
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = WHITE_QUEEN;
    store_capture(new_move);
    new_move.move_type = WHITE_KNIGHT;
    store_capture(new_move);
    new_move.move_type = WHITE_ROOK;
    store_capture(new_move);
    new_move.move_type = WHITE_BISHOP;
    store_capture(new_move);
}

void CMoveList::store_black_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = BLACK_QUEEN;
    store_capture(new_move);
    new_move.move_type = BLACK_KNIGHT;
    store_capture(new_move);
    new_move.move_type = BLACK_ROOK;
    store_capture(new_move);
    new_move.move_type = BLACK_BISHOP;
    store_capture(new_move);
}

void CMoveList::store_silent_move(const SMove &move) {
    store_move(move);
}

void CMoveList::store_capture(const SMove &move) {
    store_move(move);
 }
