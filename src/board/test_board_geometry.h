#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestBoardGeometry {
  public:
    static bool test_everything();
  private:
    static bool test_on_same_diagonal();
    static bool test_on_same_anti_diagonal();
    static bool test_excentric_neighbour_file();
    static bool test_central_neighbour_file();
};

