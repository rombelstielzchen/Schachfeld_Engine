// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_math_functions.h"
#include "testing.h"

bool CTestMathFunctions::test_everything() {
    BEGIN_TESTSUITE("CTestMathFunctions");
    EXPECT(test_approximately_equal());
    EXPECT(test_root());
    return true;
}

bool CTestMathFunctions::test_approximately_equal() {
    CTEST << "CTEST::test_approximately_equal() ...\n";
    return true;
}

bool CTestMathFunctions::test_root() {
    CTEST << "CTEST::test_root() ...\n";
    return true;
}

