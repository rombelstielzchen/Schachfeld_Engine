// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_math_functions.h"
#include "math_functions.h"
#include "testing.h"

bool CTestMathFunctions::test_everything() {
    BEGIN_TESTSUITE("CTestMathFunctions");
    EXPECT(test_approximately_equal());
    EXPECT(test_root());
    return true;
}

bool CTestMathFunctions::test_approximately_equal() {
    CTEST << "CTEST::test_approximately_equal() ...\n";
    EXPECT(approximately_equal(99, 100) == false);
    EXPECT(approximately_equal(0.1, 0.2) == false);
    EXPECT(approximately_equal(0, 0.001) == false);
    EXPECT(approximately_equal(-0.001, 0) == false);
    EXPECT(approximately_equal(99999, 100000) == true);
    EXPECT(approximately_equal(0, 0.00001) == true);
    return true;
}

bool CTestMathFunctions::test_root() {
    CTEST << "CTEST::test_root() ...\n";
    EXPECT(approximately_equal(root(64, 2) , 8));
    EXPECT(approximately_equal(root(64, 3), 4));
    EXPECT(approximately_equal(root(8, 0.5), 64));
    EXPECT(approximately_equal(root(8, 1.5), 4));
    EXPECT(approximately_equal(root(4, (2.0 / 3)), 8));
    EXPECT(approximately_equal(root(7, 1), 7));
    EXPECT(approximately_equal(root(1, 7), 1));
    EXPECT(approximately_equal(root(0, 555), 0));
    EXPECT(approximately_equal(root(1.331, 3), 1.1));
    return true;
}

