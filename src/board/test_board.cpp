// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_board.h"
#include "board.h"
#include "square_constants.h"
#include "../move_generator/move.h"
#include "../technical_functions/testing.h"

const std::string startpos_with_no_moves = "startpos";
const std::string startpos_with_moves = "startpos moves e2e4 e7e5 f2f4";
const std::string fen_with_no_moves = "4k3/4p3/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
 const std::string fen_with_moves = fen_with_no_moves + " moves e2e4 e7e5";
 const std::string fen_with_bb_tags = "[FEN]" + fen_with_no_moves + "[/FEN]";

bool CTestBoard::test_everything() {
    BEGIN_TESTSUITE("CTestBoard");
    EXPECT(test_set_start_position());
    EXPECT(test_set_fen_position());
    EXPECT(test_as_is());
    EXPECT(test_accessors());
    EXPECT(test_modifiers());
    return true;
}

bool CTestBoard::test_set_start_position() {
   TEST_FUNCTION(); 
    board.set_start_position();
    EXPECT(board.get_fen_position() == START_POSITION);
    EXPECT(test_moves_from_startpos());
    return true;
}

bool CTestBoard::test_set_fen_position() {
    TEST_FUNCTION();
    // Incorrect positions first
    EXPECT(board.set_fen_position("////////R") == false);
    EXPECT(board.set_fen_position("p") == false);
    EXPECT(board.set_fen_position("8/ppppppppp") == false);
    EXPECT(board.set_fen_position("81") == false);
    EXPECT(board.set_fen_position("qwerty") == false);
    // Valid positions below
     SILENT_EXPECT(board.set_fen_position(startpos_with_no_moves));
     EXPECT(board.get_fen_position() == START_POSITION);
     SILENT_EXPECT(board.set_fen_position(startpos_with_moves));
    EXPECT(board.get_square(FILE_E, RANK_4) == WHITE_POWER);
    EXPECT(board.get_side_to_move() == BLACK_PLAYER);
    EXPECT(board.get_eng_passeng_file() == FILE_F);
    /// Removal of phpbb-tags happens ATM in CUciProtocol
    ///SILENT_EXPECT(board.set_fen_position(fen_with_bb_tags));
   /// EXPECT(board.get_fen_position() == fen_with_no_moves);
    return true;
} 

bool CTestBoard::test_as_is() {
    TEST_FUNCTION(); 
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
   TEST_FUNCTION(); 
    board.set_start_position();
    EXPECT(board.get_side_to_move() == WHITE_PLAYER);
    EXPECT(board.get_eng_passeng_file() == NO_ENG_PASSENG_POSSIBLE);
    EXPECT(board.eng_passeng_possible() == false);
    EXPECT(board.get_square(FILE_E, RANK_8) == BLACK_KING);
    EXPECT(board.square_is_empty(FILE_E, RANK_2) == false);
    EXPECT(board.square_is_empty(FILE_E, RANK_4) == true);
    board.flip_side_to_move();
    EXPECT(board.get_side_to_move() == BLACK_PLAYER);
    return true;
}

bool CTestBoard::test_modifiers() {
   TEST_FUNCTION(); 
    board.set_start_position();
    board.clear_square(E2);
    board.put_piece(E4, WHITE_POWER);
    board.flip_side_to_move();
    EXPECT(board.square_is_empty(FILE_E, RANK_2));
    EXPECT(board.get_square(FILE_E, RANK_4) == WHITE_POWER);
    EXPECT(board.get_side_to_move() == BLACK_PLAYER);
    return true;
}

bool CTestBoard::test_moves_from_startpos() {
    TEST_FUNCTION(); 
    CTEST << "Start-position without moves ...\n";
    board.set_start_position();
    EXPECT(board.moves_from_startpos() == "");
    CTEST << "Start-position with moves ...\n";
    SILENT_EXPECT(board.set_fen_position(startpos_with_moves));
    CTEST << "moves_from_startpos(): " << board.moves_from_startpos() << "\n";
    EXPECT(board.moves_from_startpos() == "e2e4 e7e5 f2f4 ");
    CTEST << "FEN-position without moves ...\n";
    SILENT_EXPECT(board.set_fen_position(fen_with_no_moves));
    EXPECT(board.moves_from_startpos() == NO_MOVES_FROM_STARTPOS);
    CTEST << "FEN-position with moves ...\n";
    SILENT_EXPECT(board.set_fen_position(fen_with_no_moves));
    EXPECT(board.moves_from_startpos() == NO_MOVES_FROM_STARTPOS);
    return true;
}

