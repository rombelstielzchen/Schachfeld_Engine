// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_maker.h"
#include "../technical_functions/standard_headers.h"

bool CTestMoveMaker::test_everything() {
    std::cerr << "CTestMoveMaker::test_everything() ..."<< std::endl;
    bool result = test_make_unmake_combinations()
        && test_algebraic_game();
    if (result) {
        std::cerr << "CTestMoveMaker::test_everything() successful" << std::endl;
    } else {
        std::cerr << "ERROR: CTestMoveMaker::test_everything() failed" << std::endl;
    }
    return result;

}

bool CTestMoveMaker::test_make_unmake_combinations() {
    return true;
}

bool CTestMoveMaker::test_algebraic_game() {
    // TODO
    return true;
}

