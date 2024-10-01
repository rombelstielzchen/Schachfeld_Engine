// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "engine_test.h"
#include "test_technical_functions.h"
#include "../board/test_board.h"
#include "../move_generator/test_move_generator.h"
#include "../opening_book/test_opening_book.h"
#include "standard_headers.h"

/* static */ void CEngineTest::test_everything() {
    std::cerr << "CEngineTest::test_everything() ..." << std::endl;
    bool success = true
         && CTestTechnicalFunctions::test_everything()
        && CTestBoard::test_everything()
        && CTestMoveGenerator::test_everything()
        && CTestOpeningBook::test_everything();
    if (success) {
        std::cerr << "CEngineTest::test_everything(): all tests passed with success." << std::endl;
    } else {
        std::cerr << "ERROR: built-in engine-test failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

