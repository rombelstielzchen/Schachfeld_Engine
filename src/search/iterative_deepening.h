#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"
#include"../move_generator/move_generator.h"

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

constexpr int64_t INFINITE_DEPTH = INT_MAX;

class CIterativeDeepening {
  public:
    CIterativeDeepening();
  public:
    SMove search(int depth);
    SMove search_nodes(int64_t nodes);
    SMove search_movetime(const int64_t movetime_ms);
    SMove search_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t black_increment_milliseconds,
        const int64_t moves_to_go);
  private:
    void root_node_search(int depth);
    bool enough_time_left_for_one_more_iteration(const int64_t available_movetime) const;
    bool only_one_legal_move() const;
    SMove only_move();
  private:
    // Long-living move-list at the root-node for better move-ordering
    CMoveGenerator move_generator;
    SMove best_move;
};

