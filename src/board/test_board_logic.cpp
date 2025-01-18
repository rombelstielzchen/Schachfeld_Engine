#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board_logic.h"
#include "test_board_logic.h"
#include "../technical_functions/testing.h"
#include "../technical_functions/standard_headers.h"

bool CTestBoardLogic::test_everything() {
    BEGIN_TESTSUITE("CTestBoardLogic");
    EXPECT(test_king_squares());
    return true;
}

bool CTestBoardLogic::test_king_squares() {
    TEST_FUNCTION();
    return false;
}

