// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_killer_heuristics.h"
#include "killer_heuristics.h"
#include "../technical_functions/testing.h"

bool CTestKillerHeuristic::test_everything() {
    BEGIN_TESTSUITE("CTestKillerHeuristic");
    killer_heuristic.init();
    EXPECT(killer_heuristic.get_killer(0) == DUMMY_KILLER);
    EXPECT(killer_heuristic.get_killer(1) == DUMMY_KILLER);
    EXPECT(killer_heuristic.get_killer(MAX_KILLER_DEPTH - 1) == DUMMY_KILLER);
    SMove best_of_all = { G1, H3, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    killer_heuristic.store_killer(42, best_of_all);
    EXPECT(killer_heuristic.get_killer(42) == best_of_all);
    return true;
}

