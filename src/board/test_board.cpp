// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_board.h"
#include "../board/board.h"

bool CTestBoard::test_everything() {
    // Testing "everything" except set_fen_position() which already gets used
    // in about 100 tests of the move-generator and some more tests here.
    std::cerr << "CTestBoard::test_everything() ..." << std::endl;
    bool result = test_set_start_position()
        && test_as_is()
       && test_accessors();
    if (result) {
        std::cerr << "CTestBoard::test_everything() OK" << std::endl;
    } else {
        std::cerr << "ERROR: CTestBoard::test_everything() failed" << std::endl;
    }
    return result;
    // TODO: make_move (2x)
    // TODO: unmake_move
}

bool CTestBoard::test_set_start_position() {
    std::cerr << "CTestBoard::test_set_start_position() ..." << std::endl;
    board.set_start_position();
    return (board.get_fen_position() == START_POSITION);
} 

bool CTestBoard::test_as_is() {
    std::cerr << "CTestBoard::test_as_is() ... " << std::endl;
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
    std::cerr << "Expected:\n" << expected_result;
    std::cerr << "Got:\n" << board.as_is();
    std::cerr << "Expected length: " << expected_result.length() << std::endl;
    std::cerr << "Got length: " << std::string(board.as_is()).length() << std::endl;
    return (expected_result == board.as_is());
}

bool CTestBoard::test_accessors() {
    std::cerr << "CTestBoard::test_accessors() ..." << std::endl;
    bool result = true;
    board.set_start_position();
    result &= (board.get_side_to_move() == WHITE_TO_MOVE);
    result &= (board.get_eng_passeng_file() == NO_ENG_PASSENG_POSSIBLE);
    result &= (board.get_square(FILE_E, RANK_8) == BLACK_KING);
    result &= (board.square_is_empty(FILE_E, RANK_2) == false);
    result &= (board.square_is_empty(FILE_E, RANK_4) == true);
    // Another position, leading to different results
    // TODO: the other accessors
    return result;
}

