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

// TODO: rename index_of
unsigned int CMoveList::get_index(const SMove basic_move) const {
    assert(move_in_range(basic_move));
    assert(next_empty_slot >= first_capture);
    for (unsigned int j = first_capture; j < next_empty_slot; ++j) {
        if (move_coords_are_equal(basic_move, bidirectional_move_list[j])) {
            return j;
        }
    }
    return MOVE_NOT_ON_LIST;
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
    if (index == MOVE_NOT_ON_LIST) {
        return NULL_MOVE;
    }
    assert(index <  LIST_SIZE);
    return bidirectional_move_list[index];
}

int CMoveList::list_size() const {
    assert(next_empty_slot >= first_capture);
    return (next_empty_slot - first_capture);
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
    return (get_index(move) != MOVE_NOT_ON_LIST);
}

bool CMoveList::valid_list_origin() const {
    bool is_valid = true;
    is_valid &= (is_any_capture(bidirectional_move_list[LIST_ORIGIN - 1]) || (first_capture == LIST_ORIGIN));
    is_valid &= (is_silent_move(bidirectional_move_list[LIST_ORIGIN]) || (next_empty_slot == LIST_ORIGIN));
    return is_valid;
}

bool CMoveList::valid_consumer_position() const {
    return ((consumer_position >= first_capture) && (consumer_position <= next_empty_slot));
}

bool CMoveList::valid_list() const {
    return (valid_list_origin() && valid_consumer_position() && (first_capture <= LIST_ORIGIN));
}

bool CMoveList::unused_list() const {
    return (consumer_position == first_capture);
}

