// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_board_geometry.h"
#include "board_geometry.h"
#include "square_constants.h"
#include "../technical_functions/testing.h"

bool CTestBoardGeometry::test_everything() {
    TEST_FUNCTION();
    EXPECT(test_on_same_diagonal());
    EXPECT(test_on_same_anti_diagonal());
    EXPECT(test_excentric_neighbour_file());
    EXPECT(test_excentric_neighbour_file());
    EXPECT(test_central_neighbour_file());
    return true;
}

bool CTestBoardGeometry::test_on_same_diagonal() {
    TEST_FUNCTION();
    EXPECT(CBoardGeometry::on_same_diagonal(A1, E5));
    EXPECT(CBoardGeometry::on_same_diagonal(E5, E5));
    EXPECT(CBoardGeometry::on_same_diagonal(G3, E5) == false);
    EXPECT(CBoardGeometry::on_same_diagonal(B4, E5) == false);
    return true;
}

bool CTestBoardGeometry::test_on_same_anti_diagonal() {
    TEST_FUNCTION();
    EXPECT(CBoardGeometry::on_same_anti_diagonal(C4, C4));
    EXPECT(CBoardGeometry::on_same_anti_diagonal(C4, F1));
    EXPECT(CBoardGeometry::on_same_anti_diagonal(C4, E8) == false);
    EXPECT(CBoardGeometry::on_same_anti_diagonal(C4, G2) == false);
    return true;
}

bool CTestBoardGeometry::test_excentric_neighbour_file() {
    TEST_FUNCTION();
    EXPECT(CBoardGeometry::excentric_neighbour_file(FILE_D) == FILE_C);
    EXPECT(CBoardGeometry::excentric_neighbour_file(FILE_E) == FILE_F);
    return true;
}

bool CTestBoardGeometry::test_central_neighbour_file() {
    TEST_FUNCTION();
    EXPECT(CBoardGeometry::central_neighbour_file(FILE_D) == FILE_E);
    EXPECT(CBoardGeometry::central_neighbour_file(FILE_E) == FILE_D);
    return true;
}

