// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_killer_heuristics.h"
#include "killer_heuristics.h"
#include "../technical_functions/testing.h"

bool CTestKillerHeuristic::test_everything() {
    BEGIN_TESTSUITE("CTestKillerHeuristic");
    EXPECT(killer_heuristic.get_killer(0) == DUMMY_KILLER);
    EXPECT(killer_heuristic.get_killer(1) == DUMMY_KILLER);
    EXPECT(killer_heuristic.get_killer(MAX_KILLER_DEPTH - 1) == DUMMY_KILLER);
    SMove castling = { E1, G1, MOVE_TYPE_WHITE_SHORT_CASTLING, EMPTY_SQUARE };
    killer_heuristic.store_killer(42, castling);
    EXPECT(killer_heuristic.get_killer(42) == castling);
    return true;
}

