#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class CMoveMaker {
    friend class CTestMoveMaker;
  public:
    CMoveMaker();
  public:
    bool make_move(const SMove move);
    bool make_move(const std::string &long_algebraic_uci_move);
    void unmake_move();
    void unmake_all();
    bool play_variation(const std::string &variation);
    void reset_history();
  private:
    std::vector<SMove> move_history;
    std::vector <int> former_eng_passeng_files;
};

