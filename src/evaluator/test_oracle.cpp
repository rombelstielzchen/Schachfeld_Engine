// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_oracle.h"
#include "../technical_functions/testing.h"

CTestOracle::CTestOracle() {
}

bool CTestOracle::test_everything() {
    BEGIN_TESTSUITE("CTestOracle");
    EXPECT(test_basic_initialization());
    EXPECT(test_endgame_king());
    return true;
}

bool CTestOracle::test_basic_initialization() {
    TEST_FUNCTION();
    return true;
}

bool CTestOracle::test_endgame_king() {
    TEST_FUNCTION();
    return true;
}

