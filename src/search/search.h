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
//
// Caveat! INT32_MIN and INT32_MAX are not symmetric.
// Naively used, this causes an overflow when doing negamax.
constexpr int32_t BLACK_MIN_SCORE = INT32_MAX;
constexpr int32_t WHITE_MIN_SCORE = -BLACK_MIN_SCORE;
static_assert(-WHITE_MIN_SCORE > 0);
static_assert(-BLACK_MIN_SCORE < 0);

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

constexpr SAlphaBetaWindow INFINITE_ALPHA_BETA_WINDOW = { WHITE_MIN_SCORE, BLACK_MIN_SCORE };

static_assert(is_valid_alpha_beta_window(INFINITE_ALPHA_BETA_WINDOW));

class CSearch {
    friend class CTestSearch;
  public:
    int alpha_beta_negamax(const int remaining_depth, const int distance_to_root, int alpha, const int beta);
  private:
    int quiescence_negamax(const int remaining_depth, const int distance_to_root, int alpha, const int beta);
    int static_exchange_evaluation_negamax(const SSquare &target_square, int alpha, const int beta);
  private:
    bool score_causes_beta_cutoff(const int score, const int beta) const;
    bool no_legal_moves() const;
  private:
    // Minimax interface-functions. 
    // Used for the transition to negamax, still used for testing
  public: // TODO: remove
    int alpha_beta_minimax(const int remaining_depth, const int distance_to_root, SAlphaBetaWindow alpha_beta_window);
    int quiescence_minimax(const int remaining_depth, const int distance_to_root, SAlphaBetaWindow alpha_beta_window);
    int static_exchange_evaluation_minimax(const SSquare &target_square, SAlphaBetaWindow alpha_beta_window);
  private:
    uint64_t nodes_calculated;
};

