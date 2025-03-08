// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_killer_heuristics.h"
#include "killer_heuristics.h"
#include "../technical_functions/testing.h"

bool CTestKillerHeuristic::test_everything() {
    BEGIN_TESTSUITE("CTestKillerHeuristic");
    CKillerHeuristic killer_heuristics;
    EXPECT(killer_heuristics.get_killer(0) == DUMMY_KILLER);
    EXPECT(killer_heuristics.get_killer(1) == DUMMY_KILLER);
    EXPECT(killer_heuristics.get_killer(MAX_KILLER_DEPTH - 1) == DUMMY_KILLER);
    killer_heuristics.store_killer(42, NULL_MOVE);
    EXPECT(killer_heuristics.get_killer(42) == NULL_MOVE);
    return true;
}

