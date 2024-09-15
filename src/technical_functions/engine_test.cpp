// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "engine_test.h"
#include "../board/test_board.h"
#include "../move_generator/test_move_generator.h"
#include "../technical_functions/standard_headers.h"

/* static */ void CEngineTest::test_everything() {
    std::cerr << "CEngineTest::test_everything() ..." << std::endl;
    bool success = CTestMoveGenerator::test_all()
        && CTestBoard::test_everything()
        && true
        && true;
    if (success) {
        std::cerr << "CEngineTest::test_everything(): all tests passed with success." << std::endl;
    } else {
        std::cerr << "ERROR: built-in engine-test failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

