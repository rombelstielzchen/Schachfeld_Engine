// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "killer_heuristics.h"

CKillerHeuristic::CKillerHeuristic() {
    for (SMove &slot : killer_movess) {
        slot = DUMMY_KILLER;
    }
}

void CKillerHeuristic::store_killer(int distance_to_root, const SMove move) {
    assert(distance_to_root >= 0);
    assert(distance_to_root < MAX_KILLER_DEPTH);
    killer_movess[distance_to_root] = move;
}

SMove CKillerHeuristic::get_killer(int distance_to_root) {
    assert(distance_to_root >= 0);
    assert(distance_to_root < MAX_KILLER_DEPTH);
    return killer_movess[distance_to_root];
}

