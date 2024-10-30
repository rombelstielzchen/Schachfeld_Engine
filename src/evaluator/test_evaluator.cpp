// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_evaluator.h"
#include "evaluator.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

bool CTestEvaluator::test_everything() {
    BEGIN_TESTSUITE("CTestEvaluator");
  board.set_start_position();
  EXPECT(board.evaluator.evaluates_approximately_to(0));
    return true;
}

