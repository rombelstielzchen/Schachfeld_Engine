#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CTestBoardLogic {
  public:
    static bool test_everything();
  private:
    static bool test_king_squares();
    static bool test_piece_attack();
    static bool test_is_endgame();
    static bool test_is_pawn_at();
    static bool test_is_pawn_anywhere();
    static bool test_is_pawn_structure();
};

