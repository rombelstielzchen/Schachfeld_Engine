// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_oracle.h"
#include "test_evaluator.h"
#include "piece_square_value_tables.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

CTestOracle::CTestOracle() {
}

bool CTestOracle::test_everything() {
    BEGIN_TESTSUITE("CTestOracle");
    EXPECT(test_reasonable_initialization());
    EXPECT(test_endgame_king());
    return true;
}

bool CTestOracle::test_reasonable_initialization() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(main_piece_square_value_table_set[WHITE_POWER][FILE_E][RANK_5] > 0);
    EXPECT(main_piece_square_value_table_set[WHITE_KNIGHT][FILE_E][RANK_5] > 0);
    EXPECT(main_piece_square_value_table_set[WHITE_BISHOP][FILE_E][RANK_5] > 0);
    EXPECT(main_piece_square_value_table_set[WHITE_ROOK][FILE_E][RANK_5] > 0);
    EXPECT(main_piece_square_value_table_set[WHITE_QUEEN][FILE_E][RANK_5] > 0);
    EXPECT(main_piece_square_value_table_set[WHITE_KING][FILE_E][RANK_5] > 0);
    EXPECT(main_piece_square_value_table_set[BLACK_POWER][FILE_E][RANK_5] < 0);
    EXPECT(main_piece_square_value_table_set[BLACK_KNIGHT][FILE_E][RANK_5] < 0);
    EXPECT(main_piece_square_value_table_set[BLACK_BISHOP][FILE_E][RANK_5] < 0);
    EXPECT(main_piece_square_value_table_set[BLACK_ROOK][FILE_E][RANK_5] < 0);
    EXPECT(main_piece_square_value_table_set[BLACK_QUEEN][FILE_E][RANK_5] < 0);
    EXPECT(main_piece_square_value_table_set[BLACK_KING][FILE_E][RANK_5] < 0);
    EXPECT(main_piece_square_value_table_set[EMPTY_SQUARE][FILE_E][RANK_5]==  0);
    return true;
}

bool CTestOracle::test_endgame_king() {
    TEST_FUNCTION();
    std::string middlegame_Kg1 = "4k2r/2p1p2r/1pPpPp1r/pP1P1Pp1/P5Pp/R6P/R7/R5K1 w - - 0 1";
    std::string middlegame_Ke3 = "4k2r/2p1p2r/1pPpPp1r/pP1P1Pp1/P5Pp/R3K2P/R7/R7 w - - 0 1";
    EXPECT(first_position_better(middlegame_Kg1, middlegame_Ke3));
    return true;
}

