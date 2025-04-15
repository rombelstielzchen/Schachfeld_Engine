// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
//#include "move_generator.h"
#include "../board/board.h"
#include "../search/killer_heuristics.h"
#include "../technical_functions/standard_headers.h"

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
    if (consumer_position < LIST_ORIGIN) {
        return get_next__best_captire();
    }
    if (consumer_position == LIST_ORIGIN) {
        integrate_killer(distance_to_root);
    }
    return get_next();
}

SMove CMoveList::get_next__best_captire() {
    assert(consumer_position < LIST_ORIGIN);
    int best_index = consumer_position;
    int best_score = bidirectional_move_list[best_index].potential_gain;
    for (unsigned int j = consumer_position + 1; j < LIST_ORIGIN; ++j) {
        int score = bidirectional_move_list[j].potential_gain;
        if (score > best_score) {
            best_index = j;
        }
    }
    SMove best_move = bidirectional_move_list[best_index];
    assert(best_move.move_type != MOVE_TYPE_NORMAL);
//    assert(best_move.potential_gain > 0);
    bidirectional_move_list[best_index] = bidirectional_move_list[consumer_position];
     ++consumer_position;
    return best_move;
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
    assert(distance_to_root > 0);
    SMove killer_move = killer_heuristic.get_killer(distance_to_root);
    // We ignore rare killer-castlings here 
    assert(killer_move.move_type == MOVE_TYPE_NORMAL);
    unsigned int position = get_index(killer_move);
    if (position != MOVE_NOT_ON_LIST) {
        assert(position >=  first_capture);
        assert(position < next_empty_slot);
        std::swap(bidirectional_move_list[LIST_ORIGIN], bidirectional_move_list[position]);
    }
}

