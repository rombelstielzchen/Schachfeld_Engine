#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class CMoveMaker {
  public:
    CMoveMaker();
  public:
    bool make_move(const SMove move);
    bool make_move(const std::string &long_algebraic_uci_move);
    void unmake_move();
  private:
    std::vector<SMove> move_history;
};

