// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "move_generator.h"
#include "../board/board.h"
#include "../board/board_logic.h"
#include "../board/square_constants.h"

CMoveList::CMoveList() {
    clear();
}

void CMoveList::clear() {
    first_capture = LIST_ORIGIN;
    next_empty_slot = LIST_ORIGIN;
    next_empty_slot_before_pruning_silent_moves = LIST_ORIGIN;
    consumer_position = LIST_ORIGIN;
    assert(list_size() == 0);
}

SMove CMoveList::get_random() const {
    if (list_size() <= 0) {
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for an early proof of concept
    unsigned int index = first_capture + rand() % list_size();
    assert(index >= first_capture);
    assert(index < next_empty_slot);
    return bidirectional_move_list[index];
}

SMove CMoveList::get_next() {
    assert(consumer_position >= first_capture);
    if (consumer_position >= next_empty_slot) {
        return NULL_MOVE;
    }
    SMove result = bidirectional_move_list[consumer_position];
    ++consumer_position;
    assert(move_in_range(result));
    return result;
}

unsigned int CMoveList::get_index(const SMove basic_move) const {
    assert(move_in_range(basic_move));
    assert(next_empty_slot >= first_capture);
    for (unsigned int j = first_capture; j < next_empty_slot; ++j) {
        if (move_coords_are_equal(basic_move, bidirectional_move_list[j])) {
            return j;
        }
    }
    return NOT_FOUND;
}

SMove CMoveList::lookup_move(const std::string &text_move) const {
     SMove basic_move = text_to_basic_move(text_move);
     if (basic_move == NULL_MOVE) {
         return NULL_MOVE;
     }
     // TODO: make this part of text_to_basic_move
    assert(basic_move.move_type == MOVE_TYPE_NORMAL);
    if (text_move.length() > 4) {
        basic_move.move_type = text_move[4];
        assert(is_any_piece(basic_move.move_type));
    }
    unsigned int index = get_index(basic_move);
    if (index == NOT_FOUND) {
        return NULL_MOVE;
    }
    assert(index <  LIST_SIZE);
    return bidirectional_move_list[index];
}

int CMoveList::list_size() const {
    assert(next_empty_slot >= first_capture);
    return (next_empty_slot - first_capture);
}

SMove CMoveList::get_least_valuable_aggressor() const {
    int least_value = INT_MAX;
    SMove best_move = NULL_MOVE;
    for (unsigned int j = first_capture; j < next_empty_slot; ++j) {
        int piece_value = abs(board.evaluator.evaluate_square(bidirectional_move_list[j].source));
        if (piece_value < least_value) {
            least_value = piece_value;
            best_move = bidirectional_move_list[j];
        }
    }
    return best_move;
}

std::string CMoveList::as_text() const {
    std::string info ="move_list (" + std::to_string(list_size()) + "): ";
    for (int j = 0; j < list_size(); ++j) {
        int index = first_capture + j;
        info +=move_as_text(bidirectional_move_list[index]);
        info += " ";
    }
    return info;
}

bool CMoveList::move_on_list(const std::string &text_move) const {
    SMove move = text_to_basic_move(text_move);
    return (get_index(move) != NOT_FOUND);
}

