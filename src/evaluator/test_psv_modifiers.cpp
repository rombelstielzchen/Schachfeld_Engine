// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_psv_modifiers.h"
#include "evaluator.h"
#include "piece_square_value_tables.h"
#include "score_constants.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestPsvModifiers::test_everything() {
    BEGIN_TESTSUITE("CTestPsvModifiers");
    EXPECT(test_square());
    EXPECT(test_area());
    EXPECT(test_make_equal());
    EXPECT(test_make_gradient());
    EXPECT(auto_cleanup_on_new_position());
    EXPECT(test_add_bonus_to_colour_complex());
    EXPECT(test_add_bonus_to_border_squares());
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

bool CTestPsvModifiers::test_make_equal() {
    TEST_FUNCTION();
    CPsvModifier::make_equal(main_piece_square_value_table_set[BLACK_KNIGHT], 3141);
    EXPECT(main_piece_square_value_table_set[BLACK_KNIGHT][FILE_A][RANK_1] == 3141);
    EXPECT(main_piece_square_value_table_set[BLACK_KNIGHT][FILE_H][RANK_8] == 3141);
    EXPECT(main_piece_square_value_table_set[BLACK_KNIGHT][FILE_F][RANK_5] == 3141);
    CPsvModifier::clear_psv_table(main_piece_square_value_table_set[BLACK_KNIGHT]);
    EXPECT(main_piece_square_value_table_set[BLACK_KNIGHT][FILE_A][RANK_8] == 0);
    return true;
}

bool CTestPsvModifiers::test_make_gradient() {
    TEST_FUNCTION();
    CPsvModifier::make_equal(main_piece_square_value_table_set[BLACK_BISHOP], 333);
    CPsvModifier::make_gradient(main_piece_square_value_table_set[BLACK_BISHOP], G7, 10);
    EXPECT(main_piece_square_value_table_set[BLACK_BISHOP][FILE_G][RANK_7] > main_piece_square_value_table_set[BLACK_BISHOP][FILE_H][RANK_6])
    EXPECT(main_piece_square_value_table_set[BLACK_BISHOP][FILE_F][RANK_6] == main_piece_square_value_table_set[BLACK_BISHOP][FILE_H][RANK_8])
    EXPECT(main_piece_square_value_table_set[BLACK_BISHOP][FILE_C][RANK_4] == 283); 
    return true;
}

bool CTestPsvModifiers::test_add_bonus_to_colour_complex() {
    TEST_FUNCTION();
    TPieceSquareValueTable &dummy_psv = main_piece_square_value_table_set[DUMMY_PIECE_FOR_TESTING];
    CPsvModifier::make_equal(dummy_psv, 0);
    EXPECT(dummy_psv[FILE_C][RANK_4] == dummy_psv[FILE_H][RANK_6]);
    CPsvModifier::add_bonus_to_colour_complex(dummy_psv, WHITE_SQUARE_COLOUR, 20);
    EXPECT(dummy_psv[FILE_C][RANK_4] > dummy_psv[FILE_H][RANK_6]);
    CPsvModifier::add_bonus_to_colour_complex(dummy_psv, BLACK_SQUARE_COLOUR, 30);
    EXPECT(dummy_psv[FILE_C][RANK_4] < dummy_psv[FILE_H][RANK_6]);
    CPsvModifier::add_bonus_to_colour_complex(dummy_psv, WHITE_SQUARE_COLOUR, 10);
    EXPECT(dummy_psv[FILE_C][RANK_4] == dummy_psv[FILE_H][RANK_6]);
    return true;
}

bool CTestPsvModifiers::test_add_bonus_to_border_squares() {
    TEST_FUNCTION();
    TPieceSquareValueTable &dummy_psv = main_piece_square_value_table_set[DUMMY_PIECE_FOR_TESTING];
    CPsvModifier::make_equal(dummy_psv, 0);
    CPsvModifier::add_bonus_to_border_squares(dummy_psv, 20);
    EXPECT(dummy_psv[FILE_A][RANK_1] == 20);
    EXPECT(dummy_psv[FILE_H][RANK_8] == 20);
    EXPECT(dummy_psv[FILE_B][RANK_7] == 0);
    EXPECT(dummy_psv[FILE_G][RANK_2] == 0);
    return true;
}

