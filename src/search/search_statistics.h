#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class CSearchStatistics {
    friend class CTestStatistics;
  public:
    CSearchStatistics();
  public:
    void reset_all();
    void on_new_depth(int new_depth);
    void on_new_move();
  public:    
    int64_t get_nodes_total() { return nodes_total; }
    int64_t used_time_milliseconds() const;
    void set_best_move(const SMove best_move, const int score);
    void set_current_move(const SMove current_move, int score, int movenumber);
    void log_branching_factor() const;
    void log_subtree_size() const;
    void log_subtree_size_bestmove() const;
    inline void add_nodes(const int64_t nodes) {
        assert(nodes >= 0);
        nodes_total += nodes;
    }
  public:
    // TODO
    int expected_branching_factor_for_next_iteration() const;
  public:
    // Use direct access only for incrementing the couners.
    // Resets and evaluations through methods.
    int64_t killers_stored;
    int64_t killers_stored_tqual;
    int64_t killers_queried_total;
    int64_t killers_queried_legal;
  private:
    int64_t nodes_for_this_iteration() const;
    int64_t nodes_per_second() const;
  private:
    std::string node_statistics() const;
    int64_t subtree_size() const;
    static std::string anti_adjudication_score(int score);
  private:
    int64_t nodes_total;
///    int64_t nodes_this_depth;
//    int64_t nodes_this_variation;
    int64_t nodes_at_start_of_current_depth;
    int64_t nodes_at_start_of_current_move;
    int64_t subtree_size_bestmove;
    int max_depth;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

inline CSearchStatistics search_statistics;

