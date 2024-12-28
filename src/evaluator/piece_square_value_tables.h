#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../board/board.h"
#include "../technical_functions/standard_headers.h"

constexpr int PSV_COLUMNS = FILE_H + 1;
constexpr int PSV_ROWS = RANK_8 + 1;

typedef std::array<std::array<int, PSV_COLUMNS>, PSV_ROWS> TPieceSquareValueTable;

// One PSV-table per piece.  ATM our set of pieces is no dense enumeration,
// so we waste some memory here and have to be careful with future changes.
constexpr int LAST_PIECE_TYPE = BLACK_ROOK;
constexpr int N_PIECE_SQUARE_VALUE_TABLES = LAST_PIECE_TYPE + 1;
static_assert(LAST_PIECE_TYPE > WHITE_ROOK);
static_assert(LAST_PIECE_TYPE > BLACK_KING);
static_assert(LAST_PIECE_TYPE > BLACK_POWER);
static_assert(LAST_PIECE_TYPE > EMPTY_SQUARE);

typedef std::array<TPieceSquareValueTable, N_PIECE_SQUARE_VALUE_TABLES> TPieceSquareValueTableSet;

inline TPieceSquareValueTableSet main_piece_square_value_table_set;
inline TPieceSquareValueTable endgame_king_psv_table;

