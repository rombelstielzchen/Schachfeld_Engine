// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_evaluator.h"
#include "evaluator.h"
#include "../board/board.h"
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
    // Pawns on 5th / 6th / 7th rank: semi-strong / monsters / potentially a bit weak
    { "8/8/PPPPPPPP w", "8/8/8/PPPPPPPP w" },
    { "8/8/PPPPPPPP w", "8/PPPPPPPP w" },
    // Pawns on 2nd / 3rd rank
    { "8/8/8/8/8/8/P w", "8/8/8/8/8/P W"},
    { "8/8/8/8/8/8/1P w", "8/8/8/8/8/1P W"},
    { "8/8/8/8/8/8/2P w", "8/8/8/8/8/2P W"},
    { "8/8/8/8/8/8/3P w", "8/8/8/8/8/3P W"},
    { "8/8/8/8/8/8/4P w", "8/8/8/8/8/4P W"},
    { "8/8/8/8/8/8/5P w", "8/8/8/8/8/5P W"},
    { "8/8/8/8/8/8/6P w", "8/8/8/8/8/6P W"},
    { "8/8/8/8/8/8/7P w", "8/8/8/8/8/7P W"},
    // Rook-Pawns: 3rd > 5th > 4th
    { "8/8/8/8/8/P w", "8/8/8/P W" },
    { "8/8/8/P w", "8/8/8/8/P W" },
    { "8/8/8/8/8/7P w", "8/8/8/7P W" },
    { "8/8/8/7P w", "8/8/8/8/7P W" },
};

bool CTestEvaluator::test_everything() {
    BEGIN_TESTSUITE("CTestEvaluator");
    EXPECT(test_equal_positions());
    EXPECT(test_decided_positions());
    EXPECT(test_move_sequence());
    EXPECT(test_black_advantage());
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

