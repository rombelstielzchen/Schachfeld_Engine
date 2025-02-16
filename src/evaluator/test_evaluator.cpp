// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_evaluator.h"
#include "evaluator.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseEvaluator> testcases_evaluator = {
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
    CTEST << "CTestEvaluator::test_equal_positions() ...\n";
    board.set_start_position();
    EXPECT(board.evaluator.evaluates_approximately_to(0));
    return true;
}

bool CTestEvaluator::test_decided_positions() {
    CTEST << "CTestEvaluator::test_decided_positions() ...\n";
    // TODO
    return true;
}

bool CTestEvaluator::test_move_sequence() {
    CTEST << "CTestEvaluator::test_move_sequence() ...\n";
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
    CTEST << "CTestEvaluator::test_black_advantage() ...\n";
    board.set_start_position();
    board.move_maker.play_variation("e2e4 e7e5 g1f3 g8f6 f3g1 f6e4");
    (board.evaluator.evaluate() > 100);
    return true;
}

 bool CTestEvaluator::test_positions() {
    CTEST << "CTestEvaluator::test_positions() ...\n";
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
    SILENT_EXPECT(better_Score > worse_score);
    return true;
 }

