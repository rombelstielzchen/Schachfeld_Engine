#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "info.h"
#include"../move_generator/move.h"

class CSearch {
  public:
    SMove search(int depth);
  private:
    int minimax(int remaining_depth);
  private:
    CInfo info;
};

