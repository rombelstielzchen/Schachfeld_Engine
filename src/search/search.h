#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"

// We need some range here in order to distinguish different depths to mate,
// avoiding nonsense moves to longer nates or worse
constexpr int32_t WHITE_MIN_SCORE = INT32_MIN + 1000;
constexpr int32_t BLACK_MIN_SCORE = INT32_MAX - 1000;

#pragma pack(push)
#pragma pack(1)

typedef struct {
     int32_t alpha;
     int32_t beta;
} SAlphaBetaWindow;

static_assert(sizeof(SAlphaBetaWindow) <= sizeof(int64_t));

#pragma pack(pop)

constexpr SAlphaBetaWindow INFINIE_ALPHA_BETA_WINDOW = { WHITE_MIN_SCORE, BLACK_MIN_SCORE };

class CSearch {
  public:
    int alpha_beta(int remaining_depth, int distace_to_root, SAlphaBetaWindow alpha_beta_window);
  private:
    int static_exchange_evaluation(const SSquare &target_square, SAlphaBetaWindow alpha_beta_window);
  private:
    inline bool white_score_way_too_good(const int score, const SAlphaBetaWindow alpha_beta_window) const;
    inline bool black_score_way_too_good(const int score, const SAlphaBetaWindow alpha_beta_window) const;
  private:
    uint64_t nodes_calculated;
};

