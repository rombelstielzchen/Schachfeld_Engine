// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_statistics.h"
#include "../technical_functions/testing.h"

bool CTestStatistics::test_everything() {
    BEGIN_TESTSUITE("CTestStatistics");
    EXPECT(test_basic_stats());
    EXPECT(test_expected_branching_factor());
    return true;
}

bool CTestStatistics::test_basic_stats() {
    CTEST << "CTestStatistics::test_basic_stats() ...\n";
    return true;
}

bool CTestStatistics:: test_expected_branching_factor() {
    CTEST << "CTestStatistics::test_expected_branching_factor() ...\n";
    return true;
 }

