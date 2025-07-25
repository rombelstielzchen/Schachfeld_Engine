#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../evaluator/score_constants.h"
#include"../move_generator/move.h"
#include"../move_generator/move_generator.h"

#pragma pack(push)
#pragma pack(1)

typedef struct {
     int32_t alpha;
     int32_t beta;
} SAlphaBetaWindow;

static_assert(sizeof(SAlphaBetaWindow) <= sizeof(int64_t));

#pragma pack(pop)

constexpr [[nodiscard]] bool is_valid_alpha_beta_window(const SAlphaBetaWindow alpha_beta_window) {
    return alpha_beta_window.alpha <= alpha_beta_window.beta;
}

constexpr SAlphaBetaWindow INFINITE_ALPHA_BETA_WINDOW = { SCORE_HERO_LOSES, SCORE_HERO_WINS }; 

static_assert(is_valid_alpha_beta_window(INFINITE_ALPHA_BETA_WINDOW));

constexpr int64_t INFINITE_DEPTH = INT_MAX;

class CIterativeDeepening {
  public:
    CIterativeDeepening();
  public:
    [[nodiscard]] SMove search(int depth);
    [[nodiscard]] SMove search_nodes(int64_t nodes);
    [[nodiscard]] SMove search_movetime(const int64_t movetime_ms);
    [[nodiscard]] SMove search_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t black_increment_milliseconds,
        const int64_t moves_to_go);
  private:
    void root_node_search(int depth);
    bool [[nodiscard]] enough_time_left_for_one_more_iteration(const int64_t available_movetime) const;
    bool [[nodiscard]] only_one_legal_move() const;
    [[nodiscard]] SMove only_move();
  private:
    // Long-living move-list at the root-node for better move-ordering
    CMoveGenerator move_generator;
    SMove best_move;
};

