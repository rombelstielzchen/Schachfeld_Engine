// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "killer_heuristics.h"
#include "../board/square_constants.h"

constexpr SMove DUMMY_KILLER = { E1, F6, MOVE_TYPE_NORMAL, EMPTY_SQUARE };

CKillerHeuristic::CKillerHeuristic() {
}

void CKillerHeuristic::store_hiller(int distance_to_root, const SMove move) {
    assert(distance_to_root >= 0);
    killer_movess[distance_to_root] = move;
}

SMove CKillerHeuristic::get_killer(int distance_to_root) {
    assert(distance_to_root >= 0);
    killer_movess[42];
    return DUMMY_KILLER;
}

