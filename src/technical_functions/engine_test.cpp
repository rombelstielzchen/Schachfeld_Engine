// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#include "engine_test.h"
#include "../move_generator/test_move_generator.h"
#include "../technical_functions/standard_headers.h"

void CEngineTest::test_everything() {
    bool success = CTestMoveGenerator::test_all()
        && true
        && true
        && true;
    if (!success) {
        std::cerr << "ERROR: built-in engine-test failed." << std::endl;
        exit(EXIT_FAILURE);
    }
}

