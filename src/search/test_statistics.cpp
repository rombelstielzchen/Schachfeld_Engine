// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_statistics.h"
#include "search_statistics.h"
#include "../technical_functions/testing.h"

bool CTestStatistics::test_everything() {
    BEGIN_TESTSUITE("CTestStatistics");
    EXPECT(test_basic_stats());
    EXPECT(test_anti_adjudication_score());
    EXPECT(test_expected_branching_factor());
    search_statistics.reset_all();
    return true;
}

bool CTestStatistics::test_basic_stats() {
   TEST_FUNCTION(); 
    EXPECT(CSearchStatistics::anti_adjudication_score(600) == " score cp 599 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(598) == " score cp 598 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(12) == " score cp 12 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(3) == " score cp 7 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-600) == " score cp -599 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-598) == " score cp -598 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-12) == " score cp -12 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-3) == " score cp 7 ");
    return true;
}

bool CTestStatistics::test_anti_adjudication_score() {
   TEST_FUNCTION(); 
    return true;
}

bool CTestStatistics:: test_expected_branching_factor() {
   TEST_FUNCTION(); 
    return true;
 }

