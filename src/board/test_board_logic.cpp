// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_board_logic.h"
#include "board.h"
#include "board_logic.h"
#include "square_constants.h"
#include "../technical_functions/testing.h"
#include "../technical_functions/standard_headers.h"

bool CTestBoardLogic::test_everything() {
    BEGIN_TESTSUITE("CTestBoardLogic");
    EXPECT(test_king_squares());
    return true;
}

bool CTestBoardLogic::test_king_squares() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(CBoardLogic::king_square(WHITE_PLAYER) == E1);
    EXPECT(CBoardLogic::king_square(BLACK_PLAYER) == E8);
    const std::string empty_board = "w";
    SILENT_EXPECT(board.set_fen_position(empty_board));
    EXPECT(CBoardLogic::king_square(WHITE_PLAYER) == NULL_SQUARE);
    return true;
}

