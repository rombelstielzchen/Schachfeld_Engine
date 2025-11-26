// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_piece_square_value_tables.h"
#include "score_constants.h"
#include "test_evaluator.h"
#include "knowledge/endgame/expert_endgame_king_activity.h"
#include "knowledge/endgame/expert_endgame_pawn.h"
#include "../technical_functions/testing.h"
          
bool CTestPieceSquareValueTables::test_everything() {
    BEGIN_TESTSUITE("CTestPieceSquareValueTables");
    EXPECT(test_plausibility());
    EXPECT(test_positions());
    EXPECT(test_modifiers());
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility() {
    TEST_FUNCTION();
    EXPECT(test_plausibility(main_piece_square_value_table_set));
    EXPECT(test_plausibility(endgame_king_psv_table));
    EXPECT(test_plausibility(endgame_pawn_psv_table));
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility(const TPieceSquareValueTableSet &psv_table_set) {
    EXPECT(test_plausibility(psv_table_set[WHITE_POWER]));
    EXPECT(test_plausibility(psv_table_set[WHITE_KNIGHT]));
    EXPECT(test_plausibility(psv_table_set[WHITE_BISHOP]));
    EXPECT(test_plausibility(psv_table_set[WHITE_ROOK]));
    EXPECT(test_plausibility(psv_table_set[WHITE_QUEEN]));
    EXPECT(test_plausibility(psv_table_set[WHITE_KING]));
    EXPECT(test_plausibility(psv_table_set[BLACK_POWER]));
    EXPECT(test_plausibility(psv_table_set[BLACK_KNIGHT]));
    EXPECT(test_plausibility(psv_table_set[BLACK_BISHOP]));
    EXPECT(test_plausibility(psv_table_set[BLACK_ROOK]));
    EXPECT(test_plausibility(psv_table_set[BLACK_QUEEN]));
    EXPECT(test_plausibility(psv_table_set[BLACK_KING]));
    EXPECT(test_plausibility(psv_table_set[EMPTY_SQUARE]));
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility(const TPieceSquareValueTable &psv_table) {
    for (int j = 0; j <= FILE_H; ++j) {
        SILENT_EXPECT(psv_table[j][RANK_GARDEN_FENCE_BOTTOM_1] == 0);
        SILENT_EXPECT(psv_table[j][RANK_GARDEN_FENCE_BOTTOM_2] == 0);
    }
    for (int j = 0; j <= RANK_8; ++j) {
        SILENT_EXPECT(psv_table[FILE_GARDEN_FENCE_LEFT_1][j] == 0);
        SILENT_EXPECT(psv_table[FILE_GARDEN_FENCE_LEFT_2][j] == 0);
    }
    int minimum = INT_MAX;
    int maximum = INT_MIN;
    float sum = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1;  k <= RANK_8; ++k) {
            int value = psv_table[j][k];
            minimum = std::min(minimum, value);
            maximum = std::max(maximum, value);
            sum += value;
        }
    }
    float average = sum / N_SQUARES_ON_BOARD;
    EXPECT(abs(minimum) >= 0.5 * abs(average));
    EXPECT(abs(maximum) <= 2 *abs( average));
    EXPECT(minimum * maximum >= 0);
    EXPECT((minimum > 0) || (maximum < 0) || (minimum == maximum));
    return true;
}

bool CTestPieceSquareValueTables::test_positions() {
    TEST_FUNCTION();
    // All tests hard-coded for simplicity and good error-messages.
    // First: trivial test, proof of concept
    EXPECT(first_position_better("B w", "/ w"));
    EXPECT(first_position_better("/ w", "b w"));
    // Reasonable relation between different pieces
    EXPECT(first_position_better("3K w", "3Q  w"));
    EXPECT(first_position_better("3Q w", "3R w"));
    EXPECT(first_position_better("3R w", "3B w"));
    EXPECT(first_position_better("3B w", "3N w"));
    EXPECT(first_position_better("3N w", "/P w"));
    EXPECT(first_position_better("/P w", "/p w"));
    EXPECT(first_position_better("/p w", "3n w"));
    EXPECT(first_position_better("3n w", "3b w"));
    EXPECT(first_position_better("3b w", "3r w"));
    EXPECT(first_position_better("3r w", "3q w"));
    EXPECT(first_position_better("3q w", "3k w"));
    // Bad exchange B + N against R + P
    // Over-confident exchange-sacrifice due to formerly zoo large 7th-rank-bonus
    EXPECT(first_position_better("8/ppp/2n////R/R w", "8/Rpp b"));
    EXPECT(first_position_better("8/5ppp/5n////7R/7R w", "8/5ppR b"));
    return true;
}

bool CTestPieceSquareValueTables::test_modifiers() {
    TEST_FUNCTION();
    EXPECT(main_piece_square_value_table_set[WHITE_KING][FILE_E][RANK_5] > SCORE_HALF_PAWN);
    CPsvModifier::set_psv_row(WHITE_KING, RANK_5, 0);
    EXPECT(main_piece_square_value_table_set[WHITE_KING][FILE_D][RANK_5] == 0);
    EXPECT(main_piece_square_value_table_set[WHITE_KING][FILE_E][RANK_5] == 0);
    return true;
}

