#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

// TODO: distance to mate
//
// Caveat! INT32_MIN and INT32_MAX are not symmetric.
// Naively used, this causes an overflow when doing negamax.
constexpr int32_t SCORE_HERO_WINS = INT32_MAX;
constexpr int32_t SCORE_HERO_LOSES = -SCORE_HERO_WINS;
static_assert(SCORE_HERO_LOSES < 0);
static_assert(-SCORE_HERO_LOSES > 0);

constexpr int32_t SCORE_DRAW = 0;

constexpr int32_t SCORE_HALF_PAWN  = 50;
constexpr int32_t SCORE_KING = 20000;
constexpr int32_t SCORE_HALF_KING = SCORE_KING / 2;

// A captured king (illegal) might be caused by either mate or stalemate.
// The score must be positive, but worse than a mate.
constexpr int32_t SCORE_KING_CAPTURED = SCORE_HERO_WINS - 1000;
static_assert(SCORE_KING_CAPTURED > 0);
constexpr int32_t SCORE_OWN_KING_WILL_GET_CAPTURED = -SCORE_KING_CAPTURED;
static_assert(SCORE_OWN_KING_WILL_GET_CAPTURED > SCORE_HERO_LOSES);

