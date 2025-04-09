// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "killer_heuristics.h"

CKillerHeuristic::CKillerHeuristic() {
    for (SMove &slot : killer_moves) {
        slot = DUMMY_KILLER;
    }
}

void CKillerHeuristic::store_killer(int distance_to_root, const SMove move) {
    assert(distance_to_root >= 0);
    assert(distance_to_root < MAX_KILLER_DEPTH);
    assert(move_in_range(move));
    assert(move != DUMMY_KILLER);
    assert(move != NULL_MOVE);
    if (move.move_type == MOVE_TYPE_NORMAL) {
        // Ignoring rare killer-castlings here; probably not worth the overhead
        killer_moves[distance_to_root] = move;
    }
}

SMove CKillerHeuristic::get_killer(int distance_to_root) const {
    assert(distance_to_root >= 0);
    assert(distance_to_root < MAX_KILLER_DEPTH);
    SMove killer = killer_moves[distance_to_root];
    assert(move_in_range(killer));
    return killer;
}

