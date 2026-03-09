#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CTestHashFunction {
  public:
    static bool test_everything();
  private:
    // TODO: consistency
    // TODO: after set_fen
    // TODO: after moves
  private:
    static size_t hash_position(const std::string fen_position);
};

