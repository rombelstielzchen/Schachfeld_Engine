// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_piece_square_value_tables.h"
#include "../technical_functions/testing.h"
          
bool CTestPieceSquareValueTables::test_everything() {
    BEGIN_TESTSUITE("CTestPieceSquareValueTables");
    EXPECT(test_plausibility());
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility() {
    CTEST << "CTestPieceSquareValueTables::test_plausibility() ...\n";
    EXPECT(test_plausibility(main_piece_square_value_table_set));
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility(const TPieceSquareValueTableSet &psv_table_set) {
    SILENT_EXPECT(test_plausibility(psv_table_set[WHITE_POWER]));
    SILENT_EXPECT(test_plausibility(psv_table_set[WHITE_KNIGHT]));
    SILENT_EXPECT(test_plausibility(psv_table_set[WHITE_BISHOP]));
    SILENT_EXPECT(test_plausibility(psv_table_set[WHITE_ROOK]));
    SILENT_EXPECT(test_plausibility(psv_table_set[WHITE_QUEEN]));
    SILENT_EXPECT(test_plausibility(psv_table_set[WHITE_KING]));
    SILENT_EXPECT(test_plausibility(psv_table_set[BLACK_POWER]));
    SILENT_EXPECT(test_plausibility(psv_table_set[BLACK_KNIGHT]));
    SILENT_EXPECT(test_plausibility(psv_table_set[BLACK_BISHOP]));
    SILENT_EXPECT(test_plausibility(psv_table_set[BLACK_ROOK]));
    SILENT_EXPECT(test_plausibility(psv_table_set[BLACK_QUEEN]));
    SILENT_EXPECT(test_plausibility(psv_table_set[BLACK_KING]));
    SILENT_EXPECT(test_plausibility(psv_table_set[EMPTY_SQUARE]));
    return true;
}

bool CTestPieceSquareValueTables::test_plausibility(const TPieceSquareValueTable &psv_table) {
    return true;
}

