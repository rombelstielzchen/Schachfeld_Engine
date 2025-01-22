// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board.h"
#include "../move_generator/move.h"

constexpr SSquare NULL_SQUARE = {0, 0};
static_assert(0 < FILE_A);
static_assert(0 < RANK_1);

// RANK_1
constexpr SSquare A1 =  { FILE_A, RANK_1 };
constexpr SSquare B1 =  { FILE_B, RANK_1 };
constexpr SSquare C1 =  { FILE_C, RANK_1 };
constexpr SSquare D1 =  { FILE_D, RANK_1 };
constexpr SSquare E1 = { FILE_E, RANK_1 };
constexpr SSquare F1 =  { FILE_F, RANK_1 };
constexpr SSquare G1 = { FILE_G, RANK_1 };
constexpr SSquare H1 = { FILE_H, RANK_1 };
// RANK_8
constexpr SSquare A8 = { FILE_A, RANK_8 };
constexpr SSquare B8 = { FILE_B, RANK_8 };
constexpr SSquare C8 =  { FILE_C, RANK_8 };
constexpr SSquare D8 = { FILE_D, RANK_8 };
constexpr SSquare E8 = { FILE_E, RANK_8 };
constexpr SSquare F8 = { FILE_F, RANK_8 };
constexpr SSquare G8 =  { FILE_G, RANK_8 };
constexpr SSquare H8 = { FILE_H, RANK_8 };

