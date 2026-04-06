// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_distances.h"
#include "distances.h"
#include "square_constants.h"
#include "../technical_functions/testing.h"

bool CTestDistances::test_everything() {
    BEGIN_TESTSUITE("CTestDistances");
    EXPECT(test_euclidian_distance());
    return true;
}

bool CTestDistances::test_euclidian_distance() {
    TEST_FUNCTION();
    EXPECT(CDistances::euclidian_distance(E5, E5) == 0);
    EXPECT(CDistances::euclidian_distance(H2, F7) == CDistances::euclidian_distance(F7, H2));
    EXPECT(CDistances::euclidian_distance(A1, D5) <= CDistances::euclidian_distance(A1, C2) + CDistances::euclidian_distance(C2, D5));
    EXPECT(CDistances::euclidian_distance(G3, G7) == 4);
    EXPECT(CDistances::euclidian_distance(B4, E4) == 3);
    EXPECT(CDistances::euclidian_distance(F3, B6) == 5);
    return true;
}

