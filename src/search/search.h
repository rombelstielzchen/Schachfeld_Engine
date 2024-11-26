#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search_statistics.h"
#include"../move_generator/move.h"

// We need some range here in order to distinguish different depths to mate,
// avoiding nonsense moves to longer nates or worse
constexpr int WHITE_MIN_SCORE = INT_MIN + 1000;
constexpr int BLACK_MIN_SCORE = INT_MAX - 1000;

class CSearch {
  public:
    SMove search(int depth);
    int alpha_beta(int remaining_depth, int alpha, int beta);
  private:
    int recapture_extension(const SSquare &target_square, int alpha, int beta);
  private:
    inline bool white_score_way_too_good(const int score, const int beta) const;
    inline bool black_score_way_too_good(const int score, const int alpha) const;
  private:
    CSearchStatistics search_statistics;
    uint64_t nodes_calculated;
};

