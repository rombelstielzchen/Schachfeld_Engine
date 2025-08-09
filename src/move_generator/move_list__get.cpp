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
     assert(valid_list());
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
      // No assert(valid_list()); as this function is used on re-ordered root-node-lists
      assert(valid_positions());
    if (consumer_position >= next_empty_slot) {
        return NULL_MOVE;
    }
    SMove result = bidirectional_move_list[consumer_position];
    ++consumer_position;
     assert(valid_positions());
    assert(move_in_range(result));
    return result;
}

SMove CMoveList::get_next__capture_killer_silent(int distance_to_root) {
    assert(valid_list());
    if (consumer_position < LIST_ORIGIN) {
        return get_next__best_capture();
    }
    if (consumer_position == LIST_ORIGIN) {
        integrate_killer(distance_to_root);
    }
    assert(valid_list());
    SMove move = get_next();
    assert(is_silent_move(move));
    // Check for null_move if the list got pruned
    assert((next_empty_slot > LIST_ORIGIN) || is_null_move(move));
    assert((next_empty_slot == LIST_ORIGIN) || move_in_range(move));
    return move;
}

unsigned int CMoveList::index_most_valuable_victim() const {
    assert(valid_list());
    unsigned int best_index = consumer_position;
    int best_score = bidirectional_move_list[best_index].potential_gain;
    for (unsigned int j = consumer_position + 1; j < LIST_ORIGIN; ++j) {
        assert(is_null_move(bidirectional_move_list[j]) == false);
        int score = bidirectional_move_list[j].potential_gain;
        assert(score > 0);
        if (score > best_score) {
            best_index = j;
            best_score = score;
        }
    }
    return best_index;
}

unsigned int CMoveList::index_least_valuable_aggressor(const unsigned int first_most_valuable_victim) const {
    assert(first_most_valuable_victim >= consumer_position);
    assert(first_most_valuable_victim < LIST_ORIGIN);
    assert(valid_list());
    unsigned int best_index = first_most_valuable_victim;
    int const best_victim_score = bidirectional_move_list[best_index].potential_gain;
    assert(best_victim_score > 0);
    SSquare aggressor_square = bidirectional_move_list[best_index].source;
    assert(square_in_range(aggressor_square));
    int least_aggressor_value = abs(board.evaluator.evaluate_square(aggressor_square));
    assert(least_aggressor_value > 0);
    for (unsigned int j = consumer_position + 1; j < LIST_ORIGIN; ++j) {
        int const victim_Score = bidirectional_move_list[j].potential_gain;
        assert(victim_Score <= best_victim_score);
        if (victim_Score !=best_victim_score) {
            continue;
        }
        aggressor_square = bidirectional_move_list[j].source;
        assert(square_in_range(aggressor_square));
       int const aggressor_value = abs(board.evaluator.evaluate_square(aggressor_square));
       assert(aggressor_value > 0);
       if (aggressor_value < least_aggressor_value) {
           least_aggressor_value = aggressor_value;
           best_index = j;
       }
    }
    return best_index;

}

SMove CMoveList::get_next__best_capture() {
    assert(valid_list());
    unsigned int const best_index = index_least_valuable_aggressor(index_most_valuable_victim());
    assert(best_index >= consumer_position);
    assert(best_index < LIST_ORIGIN);
    SMove best_move = bidirectional_move_list[best_index];
    assert(is_null_move(best_move) == false);
    assert(move_in_range(best_move));
    assert(is_any_capture(best_move));
    assert(best_move.potential_gain > 0);
    bidirectional_move_list[best_index] = bidirectional_move_list[consumer_position];
     ++consumer_position;
     assert(valid_list());
    return best_move;
}

SMove CMoveList::get_least_valuable_aggressor() const {
    assert(valid_list());
    int least_value = INT_MAX;
    SMove best_move = NULL_MOVE;
    for (unsigned int j = first_capture; j < next_empty_slot; ++j) {
        int piece_value = abs(board.evaluator.evaluate_square(bidirectional_move_list[j].source));
        if (piece_value < least_value) {
            least_value = piece_value;
            best_move = bidirectional_move_list[j];
        }
    }
    assert((move_in_range(best_move)) || is_null_move(best_move));
    return best_move;
}

void CMoveList::integrate_killer(int distance_to_root) {
    assert(distance_to_root > 0);
    assert(valid_list());
    SMove killer_move = killer_heuristic.get_killer(distance_to_root);
    assert(move_in_range(killer_move));
    // We ignore rare killer-castlings here 
    assert(killer_move.move_type == MOVE_TYPE_NORMAL);
    unsigned int position = get_index(killer_move);
    if (position == MOVE_NOT_ON_LIST) {
        return;
    }
    assert(position >=  first_capture);
    assert(position < next_empty_slot);
    if (position < LIST_ORIGIN) {
        // Silent killer-move got found as capture; already handled
        return;
    }
    assert(valid_list_origin());
    assert(consumer_position == LIST_ORIGIN);
    std::swap(bidirectional_move_list[LIST_ORIGIN], bidirectional_move_list[position]);
    assert(valid_list());
}

