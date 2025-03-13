#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"
#include"../move_generator/move_generator.h"

constexpr int64_t INFINITE_DEPTH = INT_MAX;

class CIterativeDeepening {
  public:
    CIterativeDeepening();
  public:
    SMove search(int depth);
    SMove search_nodes(int64_t nodes);
    SMove search_movetime(const int64_t movetime_ms);
    SMove search_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t blacl_increment_milliseconds,
        const int64_t moves_to_go);
  private:
    void root_node_search(int depth);
    bool enough_time_left_for_one_more_iteration(const int64_t available_movetime) const;
    bool only_one_legal_move() const;
    SMove only_move();
  private:
    // Long-living move-list at the root-node for better move-ordering
    CMoveGenerator move_generator;
    SMove best_move;
};

