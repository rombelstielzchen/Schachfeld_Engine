// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_psv_modifiers.h"
#include "evaluator.h"
#include "piece_square_value_tables.h"
#include "score_constants.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestPsvModifiers::test_everything() {
    BEGIN_TESTSUITE("CTestPsvModifiers");
    EXPECT(test_square());
    EXPECT(test_area());
    EXPECT(auto_cleanup_on_new_position());
    return true;
}

bool CTestPsvModifiers::test_square() {
    TEST_FUNCTION();
    SILENT_EXPECT(CEvaluator::evaluate_white_pawn(A1) == CEvaluator::evaluate_white_pawn(H1));
    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[WHITE_POWER], A1, 1);
    SILENT_EXPECT(CEvaluator::evaluate_white_pawn(A1) == CEvaluator::evaluate_white_pawn(H1) + 1);
    return true;
}

bool CTestPsvModifiers::test_area() {
    TEST_FUNCTION();
   SILENT_EXPECT(CEvaluator::evaluate_white_pawn(A7) < CEvaluator::evaluate_white_pawn(B7));
    CPsvModifier::add_bonus_to_area(main_piece_square_value_table_set[WHITE_POWER], A3, A7, SCORE_HALF_PAWN);
   EXPECT(CEvaluator::evaluate_white_pawn(A7) > CEvaluator::evaluate_white_pawn(B7));
   EXPECT(CEvaluator::evaluate_white_pawn(A3) > CEvaluator::evaluate_white_pawn(B3));
   EXPECT(CEvaluator::evaluate_white_pawn(A3) > CEvaluator::evaluate_white_pawn(A2));
    return true;
}

bool CTestPsvModifiers::auto_cleanup_on_new_position() {
    TEST_FUNCTION();
    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[WHITE_POWER], H2, SCORE_HALF_PAWN);
   EXPECT(CEvaluator::evaluate_white_pawn(H2) > CEvaluator::evaluate_white_pawn(F2));
   board.set_start_position();
   EXPECT(CEvaluator::evaluate_white_pawn(H2) < CEvaluator::evaluate_white_pawn(F2));
    return true;
}

