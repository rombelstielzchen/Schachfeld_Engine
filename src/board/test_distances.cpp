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
    EXPECT(test_nearest_square());
    TSquareList empty_list = {};
    EXPECT(CDistances::nearest_square(D5, empty_list) == NULL_SQUARE);
    TSquareList single_square_list = { H8 };
    EXPECT(CDistances::nearest_square(B1, single_square_list) == H8);
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

bool CTestDistances::test_nearest_square() {
    TEST_FUNCTION();
    EXPECT(CDistances::nearest_square(D4, CORNER_SQUARES) == A1);
    EXPECT(CDistances::nearest_square(E4, CORNER_SQUARES) == H1);
    EXPECT(CDistances::nearest_square(D5, CORNER_SQUARES) == A8);
    EXPECT(CDistances::nearest_square(E5, CORNER_SQUARES) == H8);
      return true;
}

