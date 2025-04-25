#pragma once

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
// RANK_2
constexpr SSquare A2 =  { FILE_A, RANK_2 };
constexpr SSquare B2 =  { FILE_B, RANK_2 };
constexpr SSquare C2 =  { FILE_C, RANK_2 };
constexpr SSquare D2 =  { FILE_D, RANK_2 };
constexpr SSquare E2 = { FILE_E, RANK_2 };
constexpr SSquare F2 =  { FILE_F, RANK_2 };
constexpr SSquare G2 = { FILE_G, RANK_2 };
constexpr SSquare H2 = { FILE_H, RANK_2 };
// RANK_R3
constexpr SSquare A3 =  { FILE_A, RANK_3 };
constexpr SSquare B3 =  { FILE_B, RANK_3 };
constexpr SSquare C3 =  { FILE_C, RANK_3 };
constexpr SSquare D3 =  { FILE_D, RANK_3 };
constexpr SSquare E3 = { FILE_E, RANK_3 };
constexpr SSquare F3 =  { FILE_F, RANK_3 };
constexpr SSquare G3 = { FILE_G, RANK_3 };
constexpr SSquare H3 = { FILE_H, RANK_3 };
// RANK_4
constexpr SSquare A4 =  { FILE_A, RANK_4 };
constexpr SSquare B4 =  { FILE_B, RANK_4 };
constexpr SSquare C4 =  { FILE_C, RANK_4 };
constexpr SSquare D4 =  { FILE_D, RANK_4 };
constexpr SSquare E4 = { FILE_E, RANK_4 };
constexpr SSquare F4 =  { FILE_F, RANK_4 };
constexpr SSquare G4 = { FILE_G, RANK_4 };
constexpr SSquare H4 = { FILE_H, RANK_4 };
// RANK_5
constexpr SSquare A5 =  { FILE_A, RANK_5 };
constexpr SSquare B5 =  { FILE_B, RANK_5 };
constexpr SSquare C5 =  { FILE_C, RANK_5 };
constexpr SSquare D5 =  { FILE_D, RANK_5 };
constexpr SSquare E5 = { FILE_E, RANK_5 };
constexpr SSquare F5 =  { FILE_F, RANK_5 };
constexpr SSquare G5 = { FILE_G, RANK_5 };
constexpr SSquare H5 = { FILE_H, RANK_5 };
// RANK_6
constexpr SSquare A6 =  { FILE_A, RANK_6 };
constexpr SSquare B6 =  { FILE_B, RANK_6 };
constexpr SSquare C6 =  { FILE_C, RANK_6 };
constexpr SSquare D6 =  { FILE_D, RANK_6 };
constexpr SSquare E6 = { FILE_E, RANK_6 };
constexpr SSquare F6 =  { FILE_F, RANK_6 };
constexpr SSquare G6 = { FILE_G, RANK_6 };
constexpr SSquare H6 = { FILE_H, RANK_6 };
// RANK_7
constexpr SSquare A7 =  { FILE_A, RANK_7 };
constexpr SSquare B7 =  { FILE_B, RANK_7 };
constexpr SSquare C7 =  { FILE_C, RANK_7 };
constexpr SSquare D7 =  { FILE_D, RANK_7 };
constexpr SSquare E7 = { FILE_E, RANK_7 };
constexpr SSquare F7 =  { FILE_F, RANK_7 };
constexpr SSquare G7 = { FILE_G, RANK_7 };
constexpr SSquare H7 = { FILE_H, RANK_7 };
// RANK_8
constexpr SSquare A8 = { FILE_A, RANK_8 };
constexpr SSquare B8 = { FILE_B, RANK_8 };
constexpr SSquare C8 =  { FILE_C, RANK_8 };
constexpr SSquare D8 = { FILE_D, RANK_8 };
constexpr SSquare E8 = { FILE_E, RANK_8 };
constexpr SSquare F8 = { FILE_F, RANK_8 };
constexpr SSquare G8 =  { FILE_G, RANK_8 };
constexpr SSquare H8 = { FILE_H, RANK_8 };

