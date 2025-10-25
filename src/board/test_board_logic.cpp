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
    EXPECT(test_piece_attack());
    EXPECT(test_is_endgame());
    EXPECT(test_is_pawn_at());
    EXPECT(test_is_pawn_anywhere());
    EXPECT(test_is_pawn_structure());
    EXPECT(test_is_simplified_testcase());
    return true;
}

bool CTestBoardLogic::test_king_squares() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(CBoardLogic::king_square(WHITE_PLAYER) == E1);
    EXPECT(CBoardLogic::king_square(BLACK_PLAYER) == E8);
    const std::string empty_board = "/ w";
    SILENT_EXPECT(board.set_fen_position(empty_board));
    EXPECT(CBoardLogic::king_square(WHITE_PLAYER) == NULL_SQUARE);
    return true;
}

bool CTestBoardLogic::test_piece_attack() {
    TEST_FUNCTION();
    board.set_start_position();
    board.move_maker.play_variation("e2e4");
    EXPECT(CBoardLogic::piece_attacked_by_side_to_move(D5) == false);
    EXPECT(CBoardLogic::piece_attacked_by_side_to_move(E4) == false);
    board.move_maker.play_variation("d7d5");
    EXPECT(CBoardLogic::piece_attacked_by_side_not_to_move(E4) == true);
    EXPECT(CBoardLogic::piece_attacked_by_side_to_move(F7) == false);
    EXPECT(CBoardLogic::piece_attacked_by_side_to_move(H7) == false);
    board.move_maker.play_variation("d1h5");
    EXPECT(CBoardLogic::piece_attacked_by_side_not_to_move(F7) == true);
    EXPECT(CBoardLogic::piece_attacked_by_side_not_to_move(H7) == true);
    return true;
}

bool CTestBoardLogic::test_is_endgame() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(CBoardLogic::is_endgame() == false);
   EXPECT(board.set_fen_position("kqqqQQK w"));
    EXPECT(CBoardLogic::is_endgame() == false);
   EXPECT(board.set_fen_position("kqqQQK w"));
    EXPECT(CBoardLogic::is_endgame());
   EXPECT(board.set_fen_position("4k/pppppppp/////PPPPPPPP/RNBQK w"));
    EXPECT(CBoardLogic::is_endgame());
    return true;
}

bool CTestBoardLogic::test_is_pawn_at() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(CBoardLogic::is_pawn_at(WHITE_POWER, E2));
    EXPECT(CBoardLogic::is_pawn_at(WHITE_POWER, E3) == false);
    EXPECT(CBoardLogic::is_pawn_at(WHITE_POWER, E7) == false);
    EXPECT(CBoardLogic::is_pawn_at(BLACK_POWER, A7));
    EXPECT(CBoardLogic::is_pawn_at(BLACK_POWER, B5) == false);
    EXPECT(CBoardLogic::is_pawn_at(BLACK_POWER, H2) == false);
    return true;
}

bool CTestBoardLogic::test_is_pawn_anywhere() {
    TEST_FUNCTION();
    board.set_start_position();
    SILENT_EXPECT(board.move_maker.make_move("e2e4"));
    EXPECT(CBoardLogic::is_pawn_anywhere(WHITE_POWER, A5, B3, D4) == false);
    EXPECT(CBoardLogic::is_pawn_anywhere(WHITE_POWER, A5, B3, D4, G7, H8) == false);
    EXPECT(CBoardLogic::is_pawn_anywhere(WHITE_POWER, A5, B3, D4, G7, H8, E4));
    EXPECT(CBoardLogic::is_pawn_anywhere(BLACK_POWER, E5, H2) == false);
    EXPECT(CBoardLogic::is_pawn_anywhere(BLACK_POWER, E5, H7));
    return true;
}

bool CTestBoardLogic::test_is_pawn_structure() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(CBoardLogic::is_pawn_structure(WHITE_POWER, F2, G3, H2) == false);
    SILENT_EXPECT(board.move_maker.make_move("g2g3"));
    EXPECT(CBoardLogic::is_pawn_structure(WHITE_POWER, F2, G3, H2));
    return true;
}

bool CTestBoardLogic::test_is_simplified_testcase() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(CBoardLogic::is_simplified_testcase() == false);
    EXPECT(board.set_fen_position("K1k w"));
    EXPECT(CBoardLogic::is_simplified_testcase() == false);
    EXPECT(board.set_fen_position("KBk w"));
    EXPECT(CBoardLogic::is_simplified_testcase() == false);
    EXPECT(board.set_fen_position("Bb b"));
    EXPECT(CBoardLogic::is_simplified_testcase() == true);
    return true;
}

