// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move.h"
#include "move.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestMove::test_everything() {
    BEGIN_TESTSUITE("CTestMove");
    EXPECT(test_text_to_basic_move());
    EXPECT(test_reversed_move());
    return true;
}

bool CTestMove::test_text_to_basic_move() {
    SMove expected_knigh_move = { G1, F3, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    EXPECT(text_to_basic_move("g1f3") == expected_knigh_move);
    SMove expected_promotion = { B7, B8, WHITE_KNIGHT,EMPTY_SQUARE, 0 };
    SMove converted_move = text_to_basic_move("b7b8N");
    EXPECT(converted_move.source == B7);
    EXPECT(converted_move.target == B8);
    EXPECT(converted_move.move_type == WHITE_KNIGHT);
    EXPECT(text_to_basic_move("b7b8N") == expected_promotion);
    return true;
}

bool CTestMove::test_reversed_move() {
    TEST_FUNCTION();
    SMove f3g5 = { F3, G5, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    SMove f3xg5 = { F3, G5, MOVE_TYPE_CAPTURE, BLACK_QUEEN, 900 };
    SMove g5f3 = { G5, F3, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    SMove e2e4 = { E2, E4, MOVE_TYPE_DOUBLE_JUMP, EMPTY_SQUARE, 0 };
    EXPECT(is_reversed_move(f3g5, g5f3) == true);
    EXPECT(is_reversed_move(g5f3, f3g5) == true);
    EXPECT(is_reversed_move(f3xg5, g5f3) == false);
    EXPECT(is_reversed_move(f3g5, e2e4) == false);
    return true;
}

