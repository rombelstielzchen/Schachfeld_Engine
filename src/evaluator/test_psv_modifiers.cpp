// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_psv_modifiers.h"
#include "evaluator.h"
#include "piece_square_value_tables.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestPsvModifiers::test_everything() {
    BEGIN_TESTSUITE("CTestPsvModifiers");
    EXPECT(test_square());
    return true;
}

bool CTestPsvModifiers::test_square() {
    TEST_FUNCTION();
    SILENT_EXPECT(CEvaluator::evaluate_white_pawn(A1) == CEvaluator::evaluate_white_pawn(H1));
///    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[WHITE_POWER], A1, 1);
///    SILENT_EXPECT(CEvaluator::evaluate_white_pawn(A1) == CEvaluator::evaluate_white_pawn(H1) + 1);
    return true;
}

