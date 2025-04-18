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
    EXPECT(test_square_attack());
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

bool CTestBoardLogic::test_square_attack() {
    TEST_FUNCTION();
    board.set_start_position();
    board.move_maker.play_variation("e2e4");
    EXPECT(CBoardLogic::square_attacked_by_side_to_move(D5) == false);
    EXPECT(CBoardLogic::square_attacked_by_side_to_move(E4) == false);
    board.move_maker.play_variation("d7d5");
    EXPECT(CBoardLogic::square_attacked_by_side_not_to_move(E4) == true);
    EXPECT(CBoardLogic::square_attacked_by_side_to_move(F7) == false);
    EXPECT(CBoardLogic::square_attacked_by_side_to_move(H7) == false);
    board.move_maker.play_variation("d1h5");
    EXPECT(CBoardLogic::square_attacked_by_side_not_to_move(F7) == true);
    EXPECT(CBoardLogic::square_attacked_by_side_not_to_move(H7) == true);
    return true;
}

