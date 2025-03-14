// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_evaluator.h"
#include "evaluator.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseEvaluator> testcases_evaluator = {
   // Caveat! All evaluations are from whites point of view!
   // First: kingside-structure, inspired vy V_beinahe_9
    {"k/////5PP/5P/6K w", "k/////5P/5P1P/6K w"},
    { "6k/5p1p/5p////K b", "6k/5p/5pp////K b"},
    // Central pawn structure: e4 + f4 / e5 + d6
    { "8/8/3p/4p/4PP w", "8/8/8/4p/4P w" },
    { "8/8/3p/8/4P w", "8/8/8/4p/4P w" },
    { "8/8/8/4p/4P w", "8/8/3p/4pP/4P w" },
    // Central pawn structure: e4 + d4 / e5 + d6
    { "8/8/3p/4p/3PP w", "8/8/8/4p/4P w" },
    { "8/8/8/4p/4P w", "8/8/3p/3Pp/4P w" },
    // Central pawn structure: e4 + d4 / d5 + e6
    { "8/8/4p/3p/3PP w", "8/8/8/3p/3P w" },
    { "8/8/3p/8/4P w", "8/8/8/4p/4P w" },
    { "8/8/4p/8/3P w", "8/8/4p/3pP/5P w" },
    // Central pawn structure: e4 + d4 / d5 + c6
    { "8/8/4p/2p/3PP w", "8/8/8/2p/3P w" },
    { "8/8/2p/8/3P w", "8/8/8/4p/4P w" },
    // Central pawn structure: c4 + d4 / d5 + c6
    { "8/8/2p/3p/2PP w", "8/8/8/3p/3P w" },
    { "8/8/2p/8/3P w", "8/8/2p/3p/2PP w" },
    // Central pawn structure: c4 + d4 / d5 + e6
    { "8/8/2p/3p/2PP w", "8/8/8/3p/3P w" },
    { "8/8/2p/8/3P w", "8/8/2p/3p/2PP w" },
    // Central pawn structure: c4 + d4 + c3 / c5 + d5 + e6
    { "8/8/4p/2ppP/3P/2P w", "8/8/4p/3pP/8/2P w" },
    { "8/8/4p/3pP/3P w", "8/8/4p/2ppP/3P/2P w" },
    // Central pawn structure: e4 / e5 + f5 + g6 (KID)
    { "8/8/6p/4pp/4P w", "8/8/8/4pp w" },
    // Central pawn structure: b4 + c5 + d5 / d6 (KID)
    { "8/8/8/2PP w", "8/8/3p/1pp w" },
    // Central pawn structure: c4 + d5 / d6+ e6 (Benoni)
    { "8/8/3pp/3P/2P w", "8/8/3p/3P w" },
    { "8/8/3p/3P w", "8/8/3p/8/2P w" },
    // Central pawn structure c3 or c2 / e5 (Ruy Lopez, Italian)
{ "8/8/8/8/3PP w", "8/8/8/4p/3PP/2P w" },
{ "8/8/8/8/3PP w", "8/8/8/4p/3PP/8/2P w" },
    // Pawns on 5th / 6th / 7th rank: semi-strong / monsters / potentially a bit weak
    { "8/8/PPPPPPPP w", "8/8/8/PPPPPPPP w" },
    { "8/8/PPPPPPPP w", "8/PPPPPPPP w" },
    // Pawns on 2nd / 3rd rank
    // 2nd rank is usuaööy better -- except d abd e file where they hinder development
    { "8/8/8/8/8/8/P w", "8/8/8/8/8/P W"},
    { "8/8/8/8/8/8/1P w", "8/8/8/8/8/1P W"},
    { "8/8/8/8/8/8/2P w", "8/8/8/8/8/2P W"},
    { "8/8/8/8/8/8/5P w", "8/8/8/8/8/5P W"},
    { "8/8/8/8/8/8/6P w", "8/8/8/8/8/6P W"},
    { "8/8/8/8/8/8/7P w", "8/8/8/8/8/7P W"},
    // Pawns on 2nd / 3rd rank, d and e file
    { "8/8/8/8/8/3P w", "8/8/8/8/8/8/3P W"},
    { "8/8/8/8/8/4P w", "8/8/8/8/8/8/4P W"},
    // Rook-Pawns: 3rd > 5th > 4th
    { "8/8/8/8/8/P w", "8/8/8/P W" },
    { "8/8/8/P w", "8/8/8/8/P W" },
    { "8/8/8/8/8/7P w", "8/8/8/7P W" },
    { "8/8/8/7P w", "8/8/8/8/7P W" },
    // Fianchetto
    { "8/8/8/8/8/5NP/5PKP w", "8/8/8/8/8/5NP/5P1P/6K w" },
    { "8/8/8/8/8/8/5PPP/6K w", "8/8/8/8/8/6P/5P1P/6K w" },
    { "8/8/8/8/8/6P/5PBP/6K w", "8/8/8/8/2B/8/6P/5PKP w" },
    { "8/8/8/8/2B/8/5PPP/6K w", "8/8/8/8/8/8/6P/5PBP/6K w" },
    // Bad exchange, protecting Bc4 by b3 instead of playing Bb3
    // TODO
    { "8/8/8/8/8/1P/1PP w", "8/8/8/8/2P/8/P1P w "},
    // Bad exchange, protecting Bf4 by g3 instead of playing Bg3
    { "8/8/8/8/8/6P/5PP w", "8/8/8/8/5P/8/5P1P w "},
};

bool CTestEvaluator::test_everything() {
    BEGIN_TESTSUITE("CTestEvaluator");
    EXPECT(test_equal_positions());
    EXPECT(test_decided_positions());
    EXPECT(test_move_sequence());
    EXPECT(test_black_advantage());
    EXPECT(test_pawn_values());
    EXPECT(test_positions());
    return true;
}
bool CTestEvaluator::test_equal_positions() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.evaluator.evaluates_approximately_to(0));
    return true;
}

bool CTestEvaluator::test_decided_positions() {
    TEST_FUNCTION();
    // TODO
    return true;
}

bool CTestEvaluator::test_move_sequence() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.play_variation("e2e4 e7e5 g1f3");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("b8c6");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.play_variation("b1c3 g8f6 f1b5");
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
    (board.evaluator.evaluate() > 100);
    return true;
}

bool CTestEvaluator::test_pawn_values() {
    TEST_FUNCTION();
    // Logical consequences from more comples tests
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
    EXPECT(first_pawn_better(E4, D4)); // TODO ???
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
    return true;
}

 bool CTestEvaluator::test_positions() {
    TEST_FUNCTION();
    for (const STestcaseEvaluator &testcase : testcases_evaluator) {
        SILENT_EXPECT(first_position_better(testcase));
    }
    return true;
}

bool CTestEvaluator::first_position_better(const STestcaseEvaluator &testcase) {
    CTEST << "testcase: [\"" << testcase.better_position << "\", \"" << testcase.worse_position << "\"]\n";
    SILENT_EXPECT(board.set_fen_position(testcase.better_position));
    int better_Score = board.evaluator.evaluate();
    SILENT_EXPECT(board.set_fen_position(testcase.worse_position));
    int worse_score = board.evaluator.evaluate();
    std::cout << better_Score << " >? " << worse_score << "\n";
    SILENT_EXPECT(better_Score > worse_score);
    return true;
 }

bool CTestEvaluator::first_pawn_better(const SSquare first, const SSquare second) {
    int first_value = CEvaluator::evaluate_white_pawn(first);
    int second_value = CEvaluator::evaluate_white_pawn(second);
    return (first_value > second_value);
}

