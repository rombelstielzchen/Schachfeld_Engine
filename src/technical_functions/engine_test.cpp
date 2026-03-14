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
#include "../board/test_distances.h"
#include "../board/test_hash_function.h"
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
#include "../search/test_hash_table.h"
#include "../search/test_killer_heuristics.h"
#include "../search/test_search.h"
#include "../search/test_statistics.h"
#include "../universal_chess_interface/uci_protocol.h"
#include "standard_headers.h"

bool CEngineTest::testing = false;

void CEngineTest::test() {
    // Mutex-protected in CCommandInterface, therefore ... 
    assert(testing == false);
    // Blocking call to the test-function
    // in order to ease the interaction of selftest and external tests,
    // no longer using a separate thread
    test_thread_function();
}

void CEngineTest::test_thread_function() {
    BEGIN_TESTSUITE("CEngineTest");
    assert(testing == false);
    if (!test_everything()) {
        CTEST << "[ERROR] CEngineTest::test_everything() failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    board.set_start_position();
    CTEST << "[OK] CEngineTest::test_everything(): all " << testcase_counter  << " checks passed with success." << std::endl;
    // CTEST writes to cerr; UCI and test-scripts use STDIO. So...
    CUciProtocol::send_info("CEngineTest finished. Ready for play, analysis or external testing.");
    testing = false;
}

bool CEngineTest::test_everything() {
    TEST_FUNCTION();
    EXPECT(CTestMathFunctions::test_everything());
    EXPECT(CTestTechnicalFunctions::test_everything());
    EXPECT(CTestBoard::test_everything());
    EXPECT(CTestBoardLogic::test_everything());
    EXPECT(CTestDistances::test_everything());
    EXPECT(CTestMove::test_everything());
    EXPECT(CTestMoveList::test_everything());
    EXPECT(CTestMoveGenerator::test_everything());
    EXPECT(CTestPerft::test_everything());
    EXPECT(CTestMoveMaker::test_everything());
    EXPECT(CTestHashFunction::test_everything());
    EXPECT(CTestPieceSquareValueTables::test_everything());
    EXPECT(CTestPsvModifiers::test_everything());
    EXPECT(CTestOracle::test_everything());
    EXPECT(CTestEvaluator::test_everything());
    EXPECT(CTestSafetyEvaluator::test_everything());
    EXPECT(CTestExpertBasicMating::test_everything());
    EXPECT(CTestStatistics::test_everything());
    EXPECT(CTestDepthControl::test_everything());
    EXPECT(CTestHashTable::test_everything());
    EXPECT(CTestKillerHeuristic::test_everything());
    EXPECT(CTestSearch::test_everything());
    EXPECT(CTestOpeningBook::test_everything());
    return true;
}

