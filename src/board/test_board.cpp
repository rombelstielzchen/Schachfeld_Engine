// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_board.h"
#include "board.h"
#include "../technical_functions/testing.h"

bool CTestBoard::test_everything() {
    // Testing "everything" except set_fen_position() which already gets used
    // in about 100 tests of the move-generator and some more tests here.
    BEGIN_TESTSUITE("CTestBoard");
    EXPECT(test_set_start_position());
    EXPECT(test_as_is());
    EXPECT(test_accessors());
    EXPECT(test_put_piece());
    return true;
}

bool CTestBoard::test_set_start_position() {
    CTEST << "CTestBoard::test_set_start_position() ..." << std::endl;
    board.set_start_position();
    EXPECT(board.get_fen_position() == START_POSITION);
    return true;
} 

bool CTestBoard::test_as_is() {
   CTEST << "CTestBoard::test_as_is() ... " << std::endl;
    const std::string expected_result = std::string("")
        + "############\n"
        + "############\n"
        + "##RP____pr##\n"
        + "##NP____pn##\n"
        + "##BP____pb##\n"
        + "##QP____pq##\n"
        + "##KP____pk##\n"
        + "##BP____pb##\n"
        + "##NP____pn##\n"
        + "##RP____pr##\n"
        + "############\n"
        + "###########\n\0";
    board.set_start_position();
    CTEST << "Expected:\n" << expected_result;
    CTEST << "Got:\n" << board.as_is();
    CTEST << "Expected length: " << expected_result.length() << std::endl;
    CTEST << "Got length: " << std::string(board.as_is()).length() << std::endl;
    EXPECT(expected_result == board.as_is());
    return true;
}

bool CTestBoard::test_accessors() {
   CTEST  << "CTestBoard::test_accessors() ..." << std::endl;
    board.set_start_position();
    EXPECT(board.get_side_to_move() == WHITE_TO_MOVE);
    EXPECT(board.get_eng_passeng_file() == NO_ENG_PASSENG_POSSIBLE);
    EXPECT(board.get_square(FILE_E, RANK_8) == BLACK_KING);
    EXPECT(board.square_is_empty(FILE_E, RANK_2) == false);
    EXPECT(board.square_is_empty(FILE_E, RANK_4) == true);
    // Another position, leading to different results
    // TODO: the other accessors
    return true;
}

bool CTestBoard::test_put_piece() {
    CTEST << "CTestBoard::test_put_piece() ...\n";
    board.set_start_position();
    board.clear_square(FILE_E, RANK_2);
    board.put_piece(FILE_E, RANK_4, WHITE_POWER);
    EXPECT(board.square_is_empty(FILE_E, RANK_2));
    EXPECT(board.get_square(FILE_E, RANK_4) == WHITE_POWER);
    return true;
}

