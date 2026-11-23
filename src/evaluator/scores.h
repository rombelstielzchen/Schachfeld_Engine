#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <cstdint>
#include <string>

// Caveat! INT32_MIN and INT32_MAX are not symmetric.
// Naively used, this causes an overflow when doing negamax.
constexpr int32_t SCORE_TECHNICAL_MAX = INT32_MAX;
constexpr int32_t SCORE_TECHNICAL_MIN = -SCORE_TECHNICAL_MAX;
static_assert(SCORE_TECHNICAL_MIN < 0);
static_assert(-SCORE_TECHNICAL_MIN > 0);

// TODO: contempt factor
constexpr int32_t SCORE_DRAW = 0;
constexpr int32_t SCORE_STALEMATE = SCORE_DRAW;

constexpr int32_t SCORE_PAWN  = 100;
constexpr int32_t SCORE_HALF_PAWN  = SCORE_PAWN / 2;
constexpr int32_t SCORE_KING = 20000;
constexpr int32_t SCORE_HALF_KING = SCORE_KING / 2;

// A captured king (illegal) might be caused by either mate or stalemate or illegal moves.
// Its losing score must be:
//    * distinguishable from the technical minimum
//    * worse than any real mate-score,
//      so the ambiguity resolves automagically, stalemate no longer possible.
constexpr int32_t SCORE_OWN_KING_WILL_GET_CAPTURED = SCORE_TECHNICAL_MIN + 1;
constexpr int32_t SCORE_ENEMY_KING_CAPTURED = -SCORE_OWN_KING_WILL_GET_CAPTURED;
static_assert(SCORE_ENEMY_KING_CAPTURED > 0);
static_assert(SCORE_ENEMY_KING_CAPTURED < SCORE_TECHNICAL_MAX);

// We need so,e room to adapt mate scores, by distance-to-mate and material,
// therefore / 2
constexpr int32_t SCORE_LOSING_MATE = SCORE_OWN_KING_WILL_GET_CAPTURED / 2;
static_assert(SCORE_LOSING_MATE < 0);
static_assert(SCORE_LOSING_MATE < -SCORE_KING);
static_assert(SCORE_LOSING_MATE > SCORE_OWN_KING_WILL_GET_CAPTURED);
constexpr int32_t SCORE_WINNING_MATE = -SCORE_LOSING_MATE;

constexpr int score_average_power = 100;
constexpr int score_average_knight = 290;
constexpr int score_average_bishop = 320;
constexpr int score_average_rook = 470;
constexpr int score_average_queen = 890;
constexpr int delta_score_kings_and_queens_bishop = 15;

class CScores {
  public:
    static std::string to_UCI_string(int centi_wood_points);
    static std::string to_short_string(int centi_wood_points);
  public:
    static int losing_mate_score(int distance_to_root_in_plies);
    static int winning_mate_score(int distance_to_root_in_plies);
  private:
    static bool is_mate_score(int centi_wood_points);
    static bool is_too_equal(int centi_wood_points);
    static bool is_too_good(int centi_wood_points);
  private:
    static std::string standard_woodpoint_score(int centi_wood_points);
    static std::string mate_score([[maybe_unused]] int centi_wood_points);
};

