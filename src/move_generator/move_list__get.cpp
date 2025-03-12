// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
//#include "move_generator.h"
#include "../board/board.h"
#include "../search/killer_heuristics.h"

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

SMove CMoveList::get_next__capture_killer_silent(int distance_to_root) {
    if (consumer_position == LIST_ORIGIN) {
        integrate_killer(distance_to_root);
    }
    return get_next();
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

void CMoveList::integrate_killer(int distance_to_root) {

}

