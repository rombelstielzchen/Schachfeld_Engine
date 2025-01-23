// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_piece_square_value_tables.h"
#include "../technical_functions/testing.h"
          
bool CTestPieceSquareValueTables::test_everything() {
    BEGIN_TESTSUITE("CTestPieceSquareValueTables");
    EXPECT(test_plausibility());
    EXPECT(test_positions());
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility() {
    TEST_FUNCTION();
    EXPECT(test_plausibility(main_piece_square_value_table_set));
    EXPECT(test_plausibility(endgame_king_psv_table));
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
    float average = sum / 64;
    EXPECT(minimum >= 0.5 * average);
    EXPECT(maximum <= 2 * average);
    EXPECT(minimum * maximum >= 0);
    EXPECT((minimum > 0) || (maximum < 0) || (minimum == maximum));
    return true;
}

bool CTestPieceSquareValueTables::test_positions() {
    TEST_FUNCTION();
    // All tests hard-cvoded for simplicity and good error-messages.
    // First: trivial test, proof of concept
    EXPECT(first_position_better("B w", "w"));
    EXPECT(first_position_better("w", "b w"));
    // Bad exchange B + N against R + P
    EXPECT(first_position_better("BN w", "R//////P w"));
    return true;
}

bool CTestPieceSquareValueTables::first_position_better(const std::string &first_fen, const std::string &second_fen) {
    SILENT_EXPECT(board.set_fen_position(first_fen));
    int first_value = board.evaluator.evaluate();
    SILENT_EXPECT(board.set_fen_position(second_fen));
    int second_value = board.evaluator.evaluate();
    return first_value > second_value;
}

