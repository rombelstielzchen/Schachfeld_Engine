// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "root_node_list.h"
#include "../evaluator/score_constants.h"
#include "../move_generator/move_generator.h"
#include "../universal_chess_interface/uci_protocol.h"

#include <sstream>
#include <iomanip>
#include <string>

constexpr SExtendedRootMove null_element = {
    NULL_MOVE,
    SCORE_DRAW,
    0,
    false
};

CRootNodeList::CRootNodeList() {
    n_moves = 0;
    data[0] = null_element;
    consumer_position = 0;
}

void CRootNodeList::generate_moves() {
    CMoveGenerator move_generator;
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
    n_moves = move_generator.move_list.list_size();
    assert(n_moves <= MAX_MOVES_IN_CHESS_POSITION);
    consumer_position = 0;
    for (size_t j = 0; j < n_moves; ++j) {
        SMove next_move = move_generator.move_list.get_next();
        assert(next_move != NULL_MOVE);
        assert(move_in_range(next_move));
        data[j].move = next_move;
        data[j].evaluation = 0;
        data[j].nodes_calculated = 0;
        data[j].is_direct_repetition = false;
    }
    assert(move_generator.move_list.get_next() == NULL_MOVE);
    data[n_moves] = null_element;
}

SMove CRootNodeList::get_next() {
    assert(consumer_position <= n_moves);
    SMove result = data[consumer_position].move;
    assert((result != NULL_MOVE) || (consumer_position == list_size()));
    assert((move_in_range(result)) || (consumer_position == list_size()));
    ++consumer_position;
    return result;
}

bool CRootNodeList::only_one_legal_move() const {
    return list_size() == 1;
}

SMove CRootNodeList::only_move() const {
    assert(only_one_legal_move());
    // Simple direct-access, not depending on consumer_position,
    // so we can easily call it more than once, if needed
    SMove result = data[0].move;
    assert(move_in_range(result));
    return result;
}

void CRootNodeList::reuse_list() {
    consumer_position = 0;
}

void CRootNodeList::shift_current_move_to_top() {
    assert(n_moves >= 1);
    assert(consumer_position <= n_moves);
    assert(consumer_position > 0);
    size_t const original_index = consumer_position - 1;
    [[maybe_unused]] SMove const new_top_move = data[original_index].move;
    assert(move_in_range(new_top_move));
    for (size_t j = original_index; j >= 1; --j) {
        swap(j, j - 1);
    }
    assert(data[0].move == new_top_move);
}

void CRootNodeList::swap(size_t index_a, size_t index_b) {
    assert(index_a < n_moves);
    assert(index_b < n_moves);
    SExtendedRootMove const temp = data[index_a];
    data[index_a] = data[index_b];
    data[index_b] = temp;
}

SExtendedRootMove CRootNodeList::back() const {
    assert (list_size() > 0);
    size_t const last_index = list_size() - 1;
    return data[last_index];
}

void CRootNodeList::remove(size_t index) {
    assert(index < n_moves);
    assert(n_moves > 0);
    shift_tail_elements_forward(index);
}

void CRootNodeList::shift_tail_elements_forward(size_t first_index_to_be_overwritten) {
    assert(first_index_to_be_overwritten < n_moves);
    assert(n_moves > 0);
    size_t const last_index = n_moves - 1;
    for (size_t j = first_index_to_be_overwritten; j <= last_index; ++j) {
        data[j] = data[j + 1];
    }
    --n_moves;
    assert(data[n_moves].move == NULL_MOVE);

}

bool CRootNodeList::move_on_list(const SMove move) const {
    assert(move_in_range(move));
    for (size_t j = 0; j < list_size(); ++j) {
        if (data[j].move == move) {
            return true;
        }
    }
    return false;
}

void CRootNodeList::prune_silent_piece_moves(SSquare location) {
    // TODO: test
    assert(square_in_range(location));
    assert(board.get_square(location) != EMPTY_SQUARE);
    assert(consumer_position == 0);
    for (size_t j = 0; j < list_size(); ++j) {
        if ((data[j].move.source == location) && is_silent_move(data[j].move)) {
            // TODO: test is_silent_move
            assert(j < n_moves);
            remove(j);
            --j;
        }
    }
    assert(data[n_moves].move == NULL_MOVE);
}

void CRootNodeList::display() const {
    CUciProtocol::log_separator();
    CUciProtocol::send_info("    move    eval       nodes    draw");
    constexpr int width = 8;
    constexpr int extended_width_for_nodes = 12;
    for (size_t j = 0; j < list_size(); ++j) {
        std::ostringstream info;
        info << std::right << std::setw(width) << data[j].move;
        info << std::right << std::setw(width) << data[j].evaluation;
        info << std::right << std::setw(extended_width_for_nodes) << data[j].nodes_calculated;
        info << std::right << std::setw(width) << data[j].is_direct_repetition;
        CUciProtocol::send_info(info.str());
    }
    CUciProtocol::log_separator();
}

void CRootNodeList::update_entry(size_t index, SMove const move_for_verification, int evaluation, size_t nodes_calculated) {
    assert(index < list_size());
    assert(move_in_range(move_for_verification));
    assert(move_on_list(move_for_verification));
    assert(data[index].move == move_for_verification);
    data[index].evaluation = evaluation;
    // TODO: add or replace
    data[index].nodes_calculated = nodes_calculated;
    data[index].is_direct_repetition = false;
}

