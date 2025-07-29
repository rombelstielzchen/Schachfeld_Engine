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
extern TPieceSquareValueTable endgame_king_psv_table;

class CPsvModifier {
  public:
    // TODO: move this
    static void init_main_psv_set();
    // TODO: public / private?
    static void assign_psv_table(TPieceSquareValueTable &target_psv, const TPieceSquareValueTable &source_psv);
    static void assign_psv_table(char piece_type, const TPieceSquareValueTable &source_psv);
    static void flip_vertically(TPieceSquareValueTable &psv_table);
    static void negate(TPieceSquareValueTable &psv_table);
    static void clone_from_white_to_black(char black_piece_type);
    static int average(const TPieceSquareValueTable psv_table);
    static void normalize_average(TPieceSquareValueTable &psv_table, int target_psv);
};

