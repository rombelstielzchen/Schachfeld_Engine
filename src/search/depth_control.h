#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <climits>
#include <cstdint>

constexpr int64_t INFINITE_DEPTH = INT_MAX;

class CDepthControl {
  public:
    CDepthControl();
  public:
    bool go_deeper(const int current_depth) const;
    bool infinite_depth() const { return (dc_depth_in_plies == INFINITE_DEPTH); };
  public:
    void set_depth(const int64_t depth);
    void set_movetime_ms(const int64_t movetime_ms);
    void set_nodes(const int64_t nodes);
  private:
    void clear_all();
    bool enough_time_left_for_one_more_iteration() const;
  private:
    int64_t dc_depth_in_plies;
    int64_t dc_movetime_ms;
    int64_t dc_nodes;
};

