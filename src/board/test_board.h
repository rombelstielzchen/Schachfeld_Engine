#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CTestBoard {
  public:
    static bool test_everything();
  private:
    static bool test_set_start_position();
    static bool test_set_fen_position();
    static bool test_as_is();
    static bool test_accessors();
    static bool test_modifiers();
    static bool test_moves_from_startpos();
    static bool test_castling_rights();
};

