#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search_statistics.h"
#include"../move_generator/move.h"

class CSearch {
  public:
    SMove search(int depth);
  private:
    int alpha_beta(int remaining_depth, int alpha, int beta);
  private:
    inline bool white_scpre_way_too_good(const int score, const int beta) const;
    inline bool black_scpre_way_too_good(const int score, const int alpha) const;
  private:
    CSearchStatistics search_statistics;
};

