#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
#include "../move_generator/move_list.h"

struct SExtendedRootMove {
    SMove move;
    int evaluation;
    size_t nodes_calculated;
    bool is_direct_repetition;
};

class CRootNodeList {
    friend class CTestRootNodeList;
  public:
    CRootNodeList();
  public:
    void generate_moves();
    SMove get_next();
    size_t list_size() const { return n_moves; }
  public:
    bool move_on_list(const SMove move) const;
    void display() const;
    bool only_one_legal_move() const;
    SMove only_move()const;
    void reuse_list();
    void shift_current_move_to_top();
    void prune_silent_piece_moves(SSquare location);
    void update_entry(size_t index, SMove const move_for_verification, int evaluation, size_t nodes_calculated);
  private:
    void remove(size_t index);
    void shift_tail_elements_forward(size_t first_index_to_be_overwritten);
  private:
    SExtendedRootMove back() const;
    void swap(size_t index_a, size_t index_b);
  private:
    size_t n_moves;
    size_t consumer_position;
    static constexpr size_t N_DATA_ELEMENTS = MAX_MOVES_IN_CHESS_POSITION + 1;
    std::array<SExtendedRootMove, N_DATA_ELEMENTS> data;
};

