// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include <cassert>

constexpr bool NOT_YET_IMPLEMENTED = false;

void CCommandInterface::go_depth(const int64_t depth_in_plies) {
    assert(NOT_YET_IMPLEMENTED);
}

void CCommandInterface::go_nodes(const int64_t nodes) {
    assert(NOT_YET_IMPLEMENTED);
}

void CCommandInterface::go_mate(const int64_t depth_in_moves) {
    // ATM we search "normally" with the necessary depth.
    // TODO: special mate-search 
    int64_t depth_in_plies = 2 * depth_in_moves + 1;
    constexpr int64_t extra_depth_until_king_gets_captured = 2;
    int64_t required_depth_in_plies = depth_in_plies + extra_depth_until_king_gets_captured;
    go_depth(required_depth_in_plies);
}

void CCommandInterface::go_infinite() {
    go_depth(INT64_MAX);
}
 
void CCommandInterface::go_ponder() {
    // Assume the "best" opponents move while it s his turn, then calculate.
    // TODO
    go_infinite();
}

void ponder_hit() {
    assert(NOT_YET_IMPLEMENTED);
}
  
void CCommandInterface::go_movetime(const int64_t time_milliseconds) {
    assert(NOT_YET_IMPLEMENTED);
}

void CCommandInterface::go_time(
    const int64_t white_time_milliseconds,
    const int64_t black_time_milliseconds,
    const int64_t white_increment_milliseconds,
    const int64_t blacl_increment_milliseconds,
    const int64_t moves_to_go) {
    assert(NOT_YET_IMPLEMENTED);
}
 
void CCommandInterface::stop() {
    assert(NOT_YET_IMPLEMENTED);
}
