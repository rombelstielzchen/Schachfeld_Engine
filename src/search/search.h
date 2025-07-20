#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "iterative_deepening.h"

class CSearch {
    friend class CTestSearch;
  public:
    int alpha_beta_negamax(const int remaining_depth, const int distance_to_root, int alpha, const int beta);
  private:
    int quiescence_negamax(const int remaining_depth, const int distance_to_root, int alpha, const int beta);
    int static_exchange_evaluation_negamax(const SSquare &target_square, int alpha, const int beta);
  private:
    bool score_causes_beta_cutoff(const int score, const int beta) const;
    bool one_king_missing(const int score) const;
    bool no_legal_moves() const;
  private:
    // Minimax interface-functions. 
    // Used for the transition to negamax, still used for testing
    int alpha_beta_minimax(const int remaining_depth, const int distance_to_root, SAlphaBetaWindow alpha_beta_window);
    int quiescence_minimax(const int remaining_depth, const int distance_to_root, SAlphaBetaWindow alpha_beta_window);
    int static_exchange_evaluation_minimax(const SSquare &target_square, SAlphaBetaWindow alpha_beta_window);
  private:
    uint64_t nodes_calculated;
};

