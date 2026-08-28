// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_evaluator.h"
#include "evaluator.h"
#include "score_constants.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestEvaluator::test_everything() {
    BEGIN_TESTSUITE("CTestEvaluator");
    EXPECT(test_equal_positions());
    EXPECT(test_decided_positions());
    EXPECT(test_move_sequence());
///    EXPECT(test_black_advantage());
    EXPECT(test_pawn_values());
    // *** Testcase-sets ***
    EXPECT(test_positions(testcase_set_material_count));
    EXPECT(test_positions(testcase_set_endgame_king));
    EXPECT(test_positions(testcase_set_endgame_pawn_advance));
    EXPECT(test_positions(testcase_set_mating));
    EXPECT(test_positions(testcase_set_pawn_placement));
    EXPECT(test_positions(testcase_set_pawn_structure));
    EXPECT(test_positions(testcase_set_piece_placement));
    EXPECT(test_positions(testcase_set_fianchetto));
    EXPECT(test_positions(testcase_set_castling_direction));
    EXPECT(test_wood_points());
    return true;
}
bool CTestEvaluator::test_equal_positions() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(evaluates_approximately_to(0));
    return true;
}

bool CTestEvaluator::test_decided_positions() {
    TEST_FUNCTION();
    std::string decided_position = "1K/3q/1k b";
    EXPECT(board.set_fen_position(decided_position));
    EXPECT(board.evaluator.evaluate() < -500);
    return true;
}

bool CTestEvaluator::test_move_sequence() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.play_variation("e2e4 e7e5 g1f3");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("b8c6");
    EXPECT(board.evaluator.evaluate() >= 0);
    board.move_maker.play_variation("b1c3 g8f6");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.play_variation("f1b5");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("f8b4");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.make_move("e1g1");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("e8g8");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.unmake_all();
    EXPECT(board.evaluator.evaluate() == 0);
    return true;
}

bool CTestEvaluator::test_black_advantage() {
    TEST_FUNCTION();
    board.set_start_position();
    board.move_maker.play_variation("e2e4 e7e5 g1f3 g8f6 f3g1 f6e4");
    EXPECT(board.evaluator.evaluate() < -100);
    return true;
}

bool CTestEvaluator::test_pawn_values() {
    TEST_FUNCTION();
    // Logical consequences from more complex tests
    // 1) avoid bad central advances
    EXPECT(first_pawn_better(C4, C5));
    EXPECT(first_pawn_better(D4, D5));
    EXPECT(first_pawn_better(E4, E5));
    EXPECT(first_pawn_better(F4, F5));
    // Avoid bad exchanges of central pawn (for white)
    // Slav
    EXPECT(first_pawn_better(C4, C3));
    EXPECT(first_pawn_better(D4, C4));
    // Queens Gambit
    EXPECT(first_pawn_better(C4, E3));
    EXPECT(first_pawn_better(D4, C4));
    // Caro-Kann
    EXPECT(first_pawn_better(E4, C3));
    EXPECT(first_pawn_better(E4, D4));
    // French
    EXPECT(first_pawn_better(E4, E3));
    EXPECT(first_pawn_better(E4, D4)); 
    //  Scotch
    EXPECT(first_pawn_better(D4, D3));
    EXPECT(first_pawn_better(E4, D4));
    // Kings Gambit
    EXPECT(first_pawn_better(F4, D3));
    EXPECT(first_pawn_better(E4, F4));
    // Kings Indian (1)
    EXPECT(first_pawn_better(E4, F4));
    EXPECT(first_pawn_better(E4, G3));
    // Kings Indian (2)
    EXPECT(first_pawn_better(D3, B4));
    // Conflict: c2 > c4 > c5 > black c7 = c2
    //    EXPECT(first_pawn_better(C5, C2));
    EXPECT(first_pawn_better(C2, C5));
    // Benoni
    EXPECT(first_pawn_better(D5, E3));
    EXPECT(first_pawn_better(C4, E3));
    // Ruy Lopez / Italian
    EXPECT(first_pawn_better(E4, C3));
    EXPECT(first_pawn_better(E4, C2));
    // King-safety, actually testing F2/F3/G3 vs F2/G3/H2
    EXPECT(first_pawn_better(F3, H2));
    return true;
}

 bool CTestEvaluator::test_positions(const TTestcaseSetEvaluator &testcase_set) {
    TEST_FUNCTION();
    for (const STestcaseEvaluator &testcase : testcase_set) {
        SILENT_EXPECT(first_position_better(testcase));
    }
    return true;
}

bool CTestEvaluator::first_position_better(const std::string &first_fen, const std::string &second_fen) {
    SILENT_EXPECT(board.set_fen_position(first_fen));
    int first_value = board.evaluator.evaluate();
    board.evaluator.log_board_evaluation();
    CTEST << first_fen<< "    " << first_value << "\n";
    SILENT_EXPECT(board.set_fen_position(second_fen));
    int second_value = board.evaluator.evaluate();
    board.evaluator.log_board_evaluation();
    CTEST << second_fen << "    " << second_value << "\n";
    return first_value > second_value;
}

bool CTestEvaluator::first_position_better(const STestcaseEvaluator &testcase) {
    return first_position_better(testcase.better_position, testcase.worse_position);
}

bool CTestEvaluator::first_square_better(char piece, const SSquare first, const SSquare second) {
    assert(is_any_piece(piece));
    assert(square_in_range(first));
    assert(square_in_range(second));
    int first_value = CEvaluator::evaluate_piece(piece, first);
    int second_value = CEvaluator::evaluate_piece(piece, second); 
    return (first_value > second_value);
}

bool CTestEvaluator::first_pawn_better(const SSquare first, const SSquare second) {
    return first_square_better(WHITE_POWER, first, second);
}

bool CTestEvaluator::evaluates_approximately_to(const int score) {
    int real_score = board.evaluator.evaluate();
    return (abs(real_score - score) < SCORE_HALF_PAWN);
}

bool CTestEvaluator::test_wood_points() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.evaluator.wood_points(WHITE_PLAYER) == 39);
    EXPECT(board.evaluator.wood_points(BLACK_PLAYER) == 39);
    EXPECT(board.evaluator.wood_points() == 0);
    return true;
}

