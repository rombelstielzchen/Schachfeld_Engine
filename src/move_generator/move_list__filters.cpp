// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "move_generator.h"
#include "../board/board.h"
#include "../board/board_logic.h"
#include "../board/square_constants.h"

void CMoveList::prune_silent_moves() {
    assert(valid_list());
    // Remember old position, even in case of repeated pruning
    next_empty_slot_before_pruning_silent_moves = std::max(next_empty_slot, next_empty_slot_before_pruning_silent_moves);
    next_empty_slot = LIST_ORIGIN;
    assert(next_empty_slot <= next_empty_slot_before_pruning_silent_moves);
    assert(valid_list());
}

void CMoveList::unprune_silent_moves() {
    assert(valid_list());
    next_empty_slot = next_empty_slot_before_pruning_silent_moves;
    assert(valid_list());
}

void CMoveList::prune_illegal_moves() {
    assert(valid_list());
    unsigned int pos = first_capture;
    while (pos < next_empty_slot) {
        assert(pos >= first_capture);
        assert(valid_list());
        SMove move = bidirectional_move_list[pos];
        if (CBoardLogic::illegal_move(move)) {
            assert(valid_list());
#ifndef NDEBUG
            int former_list_size = list_size();
#endif
            assert(pos >= first_capture);
            remove(pos);
            pos = std::max(pos, first_capture);
            assert(list_size() < former_list_size);
            assert(valid_list());
        } else {
            assert(pos >= first_capture);
            ++pos;
        }
        assert(pos >= first_capture);
    }
    assert(valid_list());
    prune_illegal_castlings();
    reuse_list();
    assert(valid_list());
}

void CMoveList::filter_captures_by_target_square(const SSquare &target_square) {
    assert(valid_list());
    // NULL_SQUARE possible in case of simple testcases without king
    assert(square_in_range(target_square) || (target_square == NULL_SQUARE));
    prune_silent_moves();
    assert(valid_list());
    unsigned int pos = LIST_ORIGIN - 1;
    // while-loop guaranteed to terminate; either pos decreases or consumer_position increases
    while (pos >= consumer_position) {
        SMove move = bidirectional_move_list[pos];
        if (move.target == target_square) {
            --pos;
        } else {
            bidirectional_move_list[pos] = get_next();
        }
    }
    assert(pos == consumer_position - 1);
    assert(consumer_position <= LIST_ORIGIN);
    first_capture = consumer_position;
    assert((bidirectional_move_list[first_capture].target == target_square) || (first_capture == LIST_ORIGIN));
    assert(valid_list());
}

void CMoveList::reuse_list() {
    // No assert(valid_list(); here, as shift_current_move_to_top() "ruins" pre-sortedness
    assert(valid_positions());
    consumer_position = first_capture;
    assert(valid_positions());
}

void CMoveList::shift_current_move_to_top() {
    // No assert(valid_list_origin());
    // and therefore no  assert(valid_list());
    // because we may shift captures into the silent part of the list.
    assert(valid_positions());
    unsigned int former_consumer_position = consumer_position - 1;
    assert(former_consumer_position >= first_capture);
    assert(former_consumer_position < next_empty_slot);
    SMove new_top_move = bidirectional_move_list[former_consumer_position];
    unsigned int secomd_position = first_capture + 1;
    for (unsigned int j = former_consumer_position; j >= secomd_position; --j) {
       bidirectional_move_list[j] = bidirectional_move_list[j - 1];;
    }
    bidirectional_move_list[first_capture] = new_top_move;
    assert(valid_positions());
}

void CMoveList::remove(const SMove move) {
    assert(valid_list());
    unsigned int position = get_index(move);
    if (position == MOVE_NOT_ON_LIST) {
        return;
    }
    assert(position >= first_capture);
    assert(position < next_empty_slot);
    remove(position);
    assert(valid_list());
}

void CMoveList::remove(unsigned int position) {
    assert(valid_list());
    assert(unused_list());
    assert(position >= first_capture);
    assert(position < next_empty_slot);
#ifndef NDEBUG
    int original_list_size = list_size();
#endif
    assert(original_list_size > 0);
    if (position < LIST_ORIGIN) {
        remove_capture(position);
        assert(original_list_size > list_size());
        ++position;
        assert(position >= first_capture);
    } else {
       remove_silent_move(position);
        assert(original_list_size > list_size());
        assert(position >= first_capture);
    }
    assert(original_list_size > list_size());
    assert(valid_list());
}

void CMoveList::remove(const std::string &move_text) {
    assert(valid_list());
    SMove move = text_to_basic_move(move_text);
    remove(move);
    assert(valid_list());
}

void CMoveList::prune_illegal_castlings() {
    assert(valid_list());
    SSquare king_square = CBoardLogic::king_square(board.get_side_to_move());
    if (king_square.file != FILE_E) {
        return;
    }
    if (king_square.rank != CBoardLogic::my_back_rank()) {
        return;
    }
    if (board.get_side_to_move() == WHITE_PLAYER) {
        if (!move_on_list("e1f1") && move_on_list("e1g1")) {
            remove("e1g1");
        }
        if (!move_on_list("e1d1") && move_on_list("e1c1")) {
            remove("e1c1");
        }
        if (CBoardLogic::piece_attacked_by_side_not_to_move(king_square)) {
            remove("e1g1");
            remove("e1c1");
        }
        // We leave attacked target-square to the search for better performance,
        // as most often we won't try castling at all
        return;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    if (!move_on_list("e8f8") && move_on_list("e8g8")) {
        remove("e8g8");
    }
    if (!move_on_list("e8d8") && move_on_list("e8c8")) {
        remove("e8c8");
    }
    if (CBoardLogic::piece_attacked_by_side_not_to_move(king_square)) {
        remove("e8g8");
        remove("e8c8");
    }
    assert(valid_list());
}

void CMoveList::remove_capture(unsigned int position) {
    assert(valid_list());
#ifndef NDEBUG
    int former_list_size = list_size();
#endif
    bidirectional_move_list[position] = bidirectional_move_list[first_capture];
    assert(consumer_position == first_capture);
    ++first_capture;
    ++consumer_position;
    assert(former_list_size > list_size());
    assert(valid_list());
}

void CMoveList::remove_silent_move(unsigned int position) {
    assert(valid_list());
#ifndef NDEBUG
    int former_list_size = list_size();
#endif
    bidirectional_move_list[position] = bidirectional_move_list[last_move_index()];
    --next_empty_slot;
    assert(former_list_size > list_size());
    assert(valid_list());
    assert(unused_list());
}

void CMoveList::prune_silent_piece_moves(const SSquare piece_location) {
    assert(square_in_range(piece_location));
    assert(is_any_piece(board.get_square(piece_location)));
    assert(valid_list());
    for (unsigned int j = LIST_ORIGIN; j <= last_move_index(); ++j) {
        assert(is_any_capture(bidirectional_move_list[j]) == false);
        if (bidirectional_move_list[j].source == piece_location) {
            remove(j);
        }
    }
    assert(valid_list());
}

