// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "engine_test.h"
#include "testing.h"
#include "test_math_functions.h"
#include "test_technical_functions.h"
#include "../board/test_board.h"
#include "../board/test_board_logic.h"
#include "../board/test_move_maker.h"
#include "../evaluator/test_evaluator.h"
#include "../evaluator/knowledge/mating/test_expert_basic_mating.h"
#include "../evaluator/test_oracle.h"
#include "../evaluator/test_piece_square_value_tables.h"
#include "../evaluator/test_psv_modifiers.h"
#include "../evaluator/knowledge/opening/castling_direction/test_safety_evaluator.h"
#include "../move_generator/test_move.h"
#include "../move_generator/test_move_list.h"
#include "../move_generator/test_move_generator.h"
#include "../move_generator/test_perft.h"
#include "../opening_book/test_opening_book.h"
#include "../search/test_depth_control.h"
#include "../search/test_killer_heuristics.h"
#include "../search/test_search.h"
#include "../search/test_statistics.h"
#include "standard_headers.h"

bool CEngineTest::testing = false;

void CEngineTest::test_everything() {
    // TODO: maybe replace by a mutex to be extra-safe
    if (testing) {
        return;
    }
    std::thread worker_thread(test_thread_function);
    worker_thread.detach();
}

void CEngineTest::test_thread_function() {
    BEGIN_TESTSUITE("CEngineTest");
    assert(testing == false);
    testing = true;
    bool success = CTestMathFunctions::test_everything()
        &&CTestTechnicalFunctions::test_everything()
        && CTestBoard::test_everything()
        && CTestBoardLogic::test_everything()
        && CTestMove::test_everything()
        && CTestMoveList::test_everything()
        && CTestMoveGenerator::test_everything()
        && CTestPerft::test_everything()
        && CTestMoveMaker::test_everything()
        && CTestPieceSquareValueTables::test_everything()
        && CTestPsvModifiers::test_everything()
        && CTestOracle::test_everything()
        && CTestEvaluator::test_everything()
        && CTestSafetyEvaluator::test_everything()
        && CTestExpertBasicMating::test_everything()
        && CTestStatistics::test_everything()
        && CTestDepthControl::test_everything()
        && CTestKillerHeuristic::test_everything()
        && CTestSearch::test_everything()
        && CTestOpeningBook::test_everything();
    if (!success) {
        CTEST << "[ERROR] CEngineTest::test_everything() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    CTEST << "[OK] CEngineTest::test_everything(): all " << testcase_counter  << " checks passed with success." << std::endl;
    board.set_start_position();
    testing = false;
}

