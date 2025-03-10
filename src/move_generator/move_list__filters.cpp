// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "move_generator.h"
#include "../board/board.h"
#include "../board/board_logic.h"
#include "../board/square_constants.h"

// TODO: move this 
bool square_attacked_by_side_to_move(const SSquare square) {
       CMoveGenerator response_generator;
       response_generator.generate_all();
        response_generator.move_list.prune_silent_moves();
        response_generator.move_list.filter_captures_by_target_square(square);
    return (response_generator.move_list.list_size() > 0);
}

bool square_attacked_by_side_not_to_move(const SSquare square) {
    board.move_maker.make_null_move();
    bool result = square_attacked_by_side_to_move(square);
    board.move_maker.unmake_null_move();
    return result;
}

void CMoveList::prune_silent_moves() {
    assert(first_capture <= LIST_ORIGIN);
    assert(next_empty_slot >= LIST_ORIGIN);
    next_empty_slot_before_pruning_silent_moves = std::max(next_empty_slot, next_empty_slot_before_pruning_silent_moves);
    next_empty_slot = LIST_ORIGIN;
}

void CMoveList::unprune_silent_moves() {
    next_empty_slot = next_empty_slot_before_pruning_silent_moves;
}

void CMoveList::prune_illegal_moves() {
    bool my_colour = board.get_side_to_move();
    SMove move = get_next();
    while (move != NULL_MOVE) {
        board.move_maker.make_move(move);
        SSquare my_king_square = CBoardLogic::king_square(my_colour);
        if (square_attacked_by_side_to_move(my_king_square)) {
            SMove illegal_move = move;
            remove(illegal_move);
        }
        board.move_maker.unmake_move();
        move = get_next();
    }
    prune_illegal_castlings();
    reuse_list();
}

void CMoveList::filter_captures_by_target_square(const SSquare &target_square) {
    prune_silent_moves();
    for (unsigned int j = first_capture; j < LIST_ORIGIN; ++j) {
        SMove move = bidirectional_move_list[j];
        if ((move.target.file == target_square.file) && (move.target.rank == target_square.rank)) {
            store_silent_move(move);
        }
    }
    first_capture = LIST_ORIGIN;
}

void CMoveList::reuse_list() {
     assert(consumer_position >= first_capture);
    consumer_position = first_capture;
}

void CMoveList::shift_current_move_to_top() {
    unsigned int former_consumer_position = consumer_position - 1;
    assert(former_consumer_position >= first_capture);
    assert(former_consumer_position < next_empty_slot);
    SMove new_top_move = bidirectional_move_list[former_consumer_position];
    unsigned int secomd_position = first_capture + 1;
    for (unsigned int j = former_consumer_position; j >= secomd_position; --j) {
       bidirectional_move_list[j] = bidirectional_move_list[j - 1];;
    }
    bidirectional_move_list[first_capture] = new_top_move;
}

void CMoveList::remove(const SMove move) {
    unsigned int position = get_index(move);
    if (position == NOT_FOUND) {
        return;
    }
    assert(position >= first_capture);
    assert(position < next_empty_slot);
    if (position < LIST_ORIGIN) {
        bidirectional_move_list[position] = bidirectional_move_list[first_capture];
        ++first_capture;
    } else {
        bidirectional_move_list[position] = bidirectional_move_list[last_move_index()];
        --next_empty_slot;
        consumer_position = position;
    }
}

void CMoveList::remove(const std::string &move_text) {
    SMove move = text_to_basic_move(move_text);
    remove(move);
}

void CMoveList::prune_illegal_castlings() {
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
        if (square_attacked_by_side_not_to_move(king_square)) {
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
        if (square_attacked_by_side_not_to_move(king_square)) {
            remove("e8g8");
            remove("e8c8");
        }
}

