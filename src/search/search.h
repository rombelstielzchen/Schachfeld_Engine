#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"

// TODO: use constants from evaluator.h
// TODO: stalemate, proper distance to mate
// We need some range here in order to distinguish different depths to mate,
// avoiding nonsense moves to longer nates or worse
///constexpr int32_t WHITE_MIN_SCORE = INT32_MIN + 1000;
///constexpr int32_t BLACK_MIN_SCORE = INT32_MAX - 1000;
constexpr int32_t WHITE_MIN_SCORE = INT32_MIN; 
constexpr int32_t BLACK_MIN_SCORE = INT32_MAX;

#pragma pack(push)
#pragma pack(1)

typedef struct {
     int32_t alpha;
     int32_t beta;
} SAlphaBetaWindow;

static_assert(sizeof(SAlphaBetaWindow) <= sizeof(int64_t));

#pragma pack(pop)

constexpr bool is_valid_alpha_beta_window(const SAlphaBetaWindow alpha_beta_window) {
    return alpha_beta_window.alpha <= alpha_beta_window.beta;
}

constexpr SAlphaBetaWindow INFINIE_ALPHA_BETA_WINDOW = { WHITE_MIN_SCORE, BLACK_MIN_SCORE };

static_assert(is_valid_alpha_beta_window(INFINIE_ALPHA_BETA_WINDOW));

class CSearch {
    friend class CTestSearch;
  public:
    int alpha_beta(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window);
  private:
    int quiescence(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window);
    int static_exchange_evaluation(const SSquare &target_square, SAlphaBetaWindow alpha_beta_window);
  private:
    inline bool white_score_way_too_good(const int score, const SAlphaBetaWindow alpha_beta_window) const;
    inline bool black_score_way_too_good(const int score, const SAlphaBetaWindow alpha_beta_window) const;
    inline int losing_score(bool losing_side);
    bool no_legal_moves();
  private:
    uint64_t nodes_calculated;
};

