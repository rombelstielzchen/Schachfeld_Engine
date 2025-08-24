#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "piece_square_value_tables.h"
#include "knowledge/virtual_expert.h"
#include "../technical_functions/standard_headers.h"

class COracle {
  public:
    COracle();
  public:
    void configure_knowledge();
  private:
    std::vector<CVirtualExpert*>expert_collection;
};

