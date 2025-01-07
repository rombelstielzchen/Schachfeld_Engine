// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "engine_test.h"
#include "testing.h"
#include "test_technical_functions.h"
#include "../board/test_board.h"
#include "../board/test_move_maker.h"
#include "../evaluator/test_evaluator.h"
#include "../move_generator/test_move_generator.h"
#include "../opening_book/test_opening_book.h"
#include "../search/test_search.h"
#include "../search/test_statistics.h"
#include "standard_headers.h"
/* static */ bool CEngineTest::test_everything() {
    BEGIN_TESTSUITE("CEngineTest");
     EXPECT(CTestTechnicalFunctions::test_everything());
    EXPECT(CTestBoard::test_everything());
    EXPECT(CTestMoveGenerator::test_everything());
    EXPECT(CTestMoveMaker::test_everything());
    EXPECT(CTestEvaluator::test_everything());
    EXPECT(CTestStatistics::test_everything());
    EXPECT(CTestSearch::test_everything());
    EXPECT(CTestOpeningBook::test_everything());
    CTEST << "[OK] CEngineTest::test_everything(): all tests passed with success." << std::endl;
    board.set_start_position();
    return true;
}

