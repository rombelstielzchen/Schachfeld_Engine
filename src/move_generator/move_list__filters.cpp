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
    DEBUG_METHOD();
    assert(valid_list());
    assert(next_empty_slot >= LIST_ORIGIN);
    next_empty_slot_before_pruning_silent_moves = std::max(next_empty_slot, next_empty_slot_before_pruning_silent_moves);
    next_empty_slot = LIST_ORIGIN;
    assert(valid_list());
}

void CMoveList::unprune_silent_moves() {
    DEBUG_METHOD();
    assert(valid_list());
    next_empty_slot = next_empty_slot_before_pruning_silent_moves;
    assert(valid_list());
}

bool king_in_check() {
    // TODO: move to CBoardLogic
    bool my_colour = !board.get_side_to_move();
    SSquare my_king_square = CBoardLogic::king_square(my_colour);
    if (my_king_square == NULL_SQUARE) {
        // No king, probably simplified test-case
        return false;
    }
    assert(square_in_range(my_king_square));
    return (CBoardLogic::piece_attacked_by_side_to_move(my_king_square));
}

bool illegal_move(SMove move) {
    // TODO: move to CBoardLogic
    assert(move_in_range(move));
    board.move_maker.make_move(move);
    bool result = king_in_check();
    board.move_maker.unmake_move();
    return result;
}

void CMoveList::prune_illegal_moves() {
    DEBUG_METHOD();
    assert(valid_list());
    std::cerr << "List size: " << list_size() << "\n";
    unsigned int pos = first_capture;
    while (pos < next_empty_slot) {
        assert(pos >= first_capture);
        std::cerr << "pos: " << pos << "\n";
        std::cerr << "next_empty_slot: " << next_empty_slot << "\n";
        assert(valid_list());
        SMove move = bidirectional_move_list[pos];
        std::cerr  << move << "\n";
        if (illegal_move(move)) {
            std::cerr << "Removing illegal\n";
            std::cerr << "List size: " << list_size() << "\n";
            assert(valid_list());
            int former_list_size = list_size();
            assert(pos >= first_capture);
            remove(pos);
            pos = std::max(pos, first_capture);
            std::cerr << "List size: " << list_size() << "\n";
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
    DEBUG_METHOD();
    assert(valid_list());
    // NULL_SQUARE possible in case of simple testcases without king
    assert(square_in_range(target_square) || (target_square == NULL_SQUARE));
    assert(valid_list_origin());
    assert(consumer_position <= LIST_ORIGIN);
    prune_silent_moves();
    assert(valid_list_origin());
    assert(consumer_position <= LIST_ORIGIN);
    int pos = LIST_ORIGIN - 1;
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
    if (bidirectional_move_list[pos].target != target_square) {
        ++pos;
    }
    consumer_position == pos;
    // TODO: revisit consumer_position in case of no captures, LIST_ORIGIN + 1?
    consumer_position = std::min(consumer_position, LIST_ORIGIN);
    first_capture = consumer_position;
    assert(valid_list_origin());
    assert(valid_list());
}

void CMoveList::reuse_list() {
    DEBUG_METHOD();
    assert(valid_list());
     assert(consumer_position >= first_capture);
    consumer_position = first_capture;
    assert(valid_list());
}

void CMoveList::shift_current_move_to_top() {
    DEBUG_METHOD();
    assert(valid_list());
    unsigned int former_consumer_position = consumer_position - 1;
    assert(former_consumer_position >= first_capture);
    assert(former_consumer_position < next_empty_slot);
    SMove new_top_move = bidirectional_move_list[former_consumer_position];
    unsigned int secomd_position = first_capture + 1;
    for (unsigned int j = former_consumer_position; j >= secomd_position; --j) {
       bidirectional_move_list[j] = bidirectional_move_list[j - 1];;
    }
    bidirectional_move_list[first_capture] = new_top_move;
    assert(valid_list());
}

void CMoveList::remove(const SMove move) {
    DEBUG_METHOD();
    assert(valid_list());
    assert(valid_list_origin());
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
    DEBUG_METHOD();
    std::cerr << "position: " << position << "\n";
    std::cerr << "first_capture: " << first_capture << "\n";
    assert(valid_list());
    assert(unused_list());
    assert(position >= first_capture);
    assert(position < next_empty_slot);
    int original_list_size = list_size();
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
    DEBUG_METHOD();
    assert(valid_list());
    SMove move = text_to_basic_move(move_text);
    remove(move);
    assert(valid_list());
}

void CMoveList::prune_illegal_castlings() {
    DEBUG_METHOD();
    assert(valid_list());
    // TODO: refactoring
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
        return;
    }
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
    DEBUG_METHOD();
    assert(valid_list());
    int former_list_size = list_size();
    bidirectional_move_list[position] = bidirectional_move_list[first_capture];
    assert(consumer_position == first_capture);
        ++first_capture;
        ++consumer_position;
        assert(valid_list_origin());
        assert(valid_consumer_position());
        assert(valid_list());
    assert(former_list_size > list_size());
}

void CMoveList::remove_silent_move(unsigned int position) {
    DEBUG_METHOD();
    assert(valid_list());
    int former_list_size = list_size();
    bidirectional_move_list[position] = bidirectional_move_list[last_move_index()];
    --next_empty_slot;
    assert(valid_list());
    assert(unused_list());
    assert(former_list_size > list_size());
}

