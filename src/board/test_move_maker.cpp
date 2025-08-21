// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_maker.h"
#include "board.h"
#include "square_constants.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/testing.h"
#include "../technical_functions/standard_headers.h"

bool CTestMoveMaker::test_everything() {
    BEGIN_TESTSUITE("CTestMoveMaker");
    EXPECT(test_eng_passeng_rights());
    EXPECT(test_make_unmake_combinations());
    EXPECT(test_algebraic_game());
    EXPECT(test_castling_rights());
    EXPECT(test_promotions());
    EXPECT(test_repetition());
    return true;
}

bool CTestMoveMaker::test_make_unmake_combinations() {
    const std::string white_all_in_one_position = "Q3rr2/3PPP2/4B3/5ppP/6P1/2N2P2/q3P3/R3K2R w KQ g6 0 1";
    const std::string black_all_in_one_position = "r3k2r/p6R/1p6/8/5pPp/8/1p3P2/N1Nb2qn b kq g3 0 1";
    EXPECT(test_make_unmake_combinations(white_all_in_one_position));
    EXPECT(test_make_unmake_combinations(black_all_in_one_position));
    return true;
}

bool CTestMoveMaker::test_make_unmake_combinations(const std::string &position) {
    board.set_fen_position(position);
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.move_list.list_size();
    CTEST << n_moves << " moves to test" << std::endl;
   for (int j = 0; j < n_moves; ++j) {
        SMove move = move_generator.move_list.get_next();
        CTEST << "Make / unmake " << move << "...\n";
        board.move_maker.make_move(move);
        board.move_maker.unmake_move();
        SILENT_EXPECT(board.get_fen_position() == position);
   }
    return true;
}

bool CTestMoveMaker::test_algebraic_game() {
    TEST_FUNCTION(); 
    CTEST << "Move-history: " <<board.move_maker.move_history.size() << "\n";
    board.set_fen_position("startpos moves g1f3 d7d5 g2g3 c7c6 f1g2 g8f6 e1g1 e7e6 a2a4 f8e7 a4a5 b7b5 a5b6 e8g8 b6b7 b8d7 b7a8N");
    CTEST << "Move-history: " <<board.move_maker.move_history.size() << "\n";
    EXPECT(board.get_square(FILE_G, RANK_1) == WHITE_KING);
    EXPECT(board.get_square(FILE_F, RANK_1) == WHITE_ROOK);
    EXPECT(board.square_is_empty(FILE_E, RANK_1));
    EXPECT(board.square_is_empty(FILE_H, RANK_1));
    EXPECT(board.square_is_empty(FILE_B, RANK_5));
    EXPECT(board.get_square(FILE_A, RANK_8) == WHITE_KNIGHT);
   CTEST << "Now unmaking all moves ...\n";
   board.move_maker.unmake_all();
   board.set_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING, true);
   board.set_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING, true);
   board.set_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING, true);
   board.set_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING, true);
   EXPECT(board.get_fen_position() == START_POSITION);
    EXPECT(board.move_maker.move_history.size() == 0);
    return true;
}

bool CTestMoveMaker::test_eng_passeng_rights() {
   TEST_FUNCTION(); 
    board.set_start_position();
    EXPECT(board.eng_passeng_possible() == false);
    board.move_maker.make_move("a2a4");
    EXPECT(board.get_eng_passeng_file() == FILE_A);
    board.move_maker.make_move("b7b5");
    EXPECT(board.get_eng_passeng_file() == FILE_B);
    board.move_maker.make_move("c2c3");
    EXPECT(board.eng_passeng_possible() == false);
    board.move_maker.unmake_move();
    EXPECT(board.get_eng_passeng_file() == FILE_B);
    board.move_maker.unmake_move();
    EXPECT(board.get_eng_passeng_file() == FILE_A);
    board.move_maker.unmake_move();
    EXPECT(board.eng_passeng_possible() == false);
    return true;
}

bool CTestMoveMaker::test_castling_rights() {
    TEST_FUNCTION(); 
    SILENT_EXPECT(board.set_fen_position("startpos moves g2g3 g8f6 f1g2 h8g8 e1f1"));
    EXPECT(board.get_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING) == true);
    EXPECT(board.get_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING) == false);
    EXPECT(board.get_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING) == false);
    EXPECT(board.get_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING) == false);
    return true;
}

bool CTestMoveMaker::test_promotions() {
   TEST_FUNCTION();
   std::string const white_promotion = "/PK1k w - - 0 1 moves a7a8Q";
   EXPECT(board.set_fen_position(white_promotion));
   EXPECT(board.get_square(A8) == WHITE_QUEEN); 
   std::string const black_promotion = "//////pk1K b - - 0 1 moves a2a1";
   EXPECT(board.set_fen_position(black_promotion));
   EXPECT(board.get_square(A1) == BLACK_QUEEN); 
   // Some GUIs send a lower-case piece after a white promotion.
   // Unexpected, but correctly! UCI-specification "e7e8q"
   std::string const white_lowercase_promotion = "/PK1k w - - 0 1 moves a7a8q";
   EXPECT(board.set_fen_position(white_lowercase_promotion));
   EXPECT(board.get_square(A8) == WHITE_QUEEN); 
   return true;
}

bool CTestMoveMaker::test_repetition() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.move_maker.play_variation("e2e4 e7e5"));
    EXPECT(board.move_maker.move_history_contains_repetition() == false);
    EXPECT(board.move_maker.play_variation("g1f3 g8f6 f3g1"));
    EXPECT(board.move_maker.move_history_contains_repetition() == false);
    EXPECT(board.move_maker.play_variation("f6g8"));
    EXPECT(board.move_maker.move_history_contains_repetition());
    EXPECT(board.move_maker.get_repetitive_move() == "g1f3");
    EXPECT(board.move_maker.play_variation("g1f3"));
    EXPECT(board.move_maker.move_history_contains_repetition());
    EXPECT(board.move_maker.get_repetitive_move() == "g8f6");
    EXPECT(board.move_maker.play_variation("b8c6"));
    EXPECT(board.move_maker.move_history_contains_repetition() == false);
    EXPECT(board.move_maker.get_repetitive_move() == NULL_MOVE);
    return true;
}

