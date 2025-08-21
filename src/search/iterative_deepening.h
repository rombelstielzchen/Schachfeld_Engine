#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "depth_control.h"
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

constexpr bool is_valid_alpha_beta_window(const SAlphaBetaWindow alpha_beta_window) {
    return alpha_beta_window.alpha <= alpha_beta_window.beta;
}

constexpr SAlphaBetaWindow INFINITE_ALPHA_BETA_WINDOW = { SCORE_HERO_LOSES, SCORE_HERO_WINS }; 

static_assert(is_valid_alpha_beta_window(INFINITE_ALPHA_BETA_WINDOW));

class CIterativeDeepening {
  public:
    CIterativeDeepening();
  public:
    // Public interface to be used by CCommandInterface
    // Do not confuse the external "depth"-function with the internal ones!
    SMove search_depth(int depth);
    SMove search_nodes(const int64_t nodes);
    SMove search_movetime(const int64_t movetime_ms);
    SMove search_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t black_increment_milliseconds,
        const int64_t moves_to_go);
  private:
    // The functions call each other in the following order:
    SMove search_common_entry_point();
    SMove search_anti_repetition();
    SMove search_iterative();
    SMove search_fixed_depth(const int depth);
  private:
    bool only_one_legal_move() const;
    SMove only_move();
  private:
    bool mate_found;
    CDepthControl depth_control;
    // Long-living move-list at the root-node for better move-ordering
    CMoveGenerator move_generator;
};

