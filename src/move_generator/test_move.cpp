// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move.h"
#include "move.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestMove::test_everything() {
    BEGIN_TESTSUITE("CTestMove");
    EXPECT(test_text_to_basic_move());
    return true;
}

bool CTestMove::test_text_to_basic_move() {
    SMove expected_knigh_move = { G1, F3, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    EXPECT(text_to_basic_move("g1f3") == expected_knigh_move);
    return true;
}

