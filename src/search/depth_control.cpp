// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "depth_control.h"
#include "search_statistics.h"
#include "../technical_functions/standard_headers.h"

CDepthControl::CDepthControl() {
    clear_all();
}

void CDepthControl::clear_all() {
    dc_depth_in_plies = 0;
    dc_movetime_ms = 0;
    dc_nodes = 0;
}

void CDepthControl::set_depth(const int64_t depth) {
    assert(depth > 0);
    clear_all();
    dc_depth_in_plies = depth;
}

void CDepthControl::set_movetime_ms(const int64_t movetime_ms) {
    assert(movetime_ms > 0);
    clear_all();
    dc_movetime_ms = movetime_ms;
}

void CDepthControl::set_nodes(const int64_t nodes) {
    assert(nodes > 0);
    clear_all();
    dc_nodes = nodes;
}

bool CDepthControl::go_deeper(const int current_depth) const {
    assert((dc_depth_in_plies > 0) || (dc_movetime_ms > 0) || (dc_nodes > 0));
    assert(current_depth >= 0);
    if (current_depth < dc_depth_in_plies) {
        assert(dc_movetime_ms == 0);
        assert(dc_nodes == 0);
        return true;
    }
    if (search_statistics.get_nodes_total() < dc_nodes) {
        assert(dc_depth_in_plies == 0);
        assert(dc_movetime_ms == 0);
        return true;
    }
    if (enough_time_left_for_one_more_iteration()) {
        assert(dc_depth_in_plies == 0);
        assert(dc_nodes == 0);
        return true;
    }
    return false;
}

bool CDepthControl::enough_time_left_for_one_more_iteration() const {
   constexpr int estimated_branching_factor = 6;
    return (dc_movetime_ms > estimated_branching_factor * search_statistics.used_time_milliseconds());
}

