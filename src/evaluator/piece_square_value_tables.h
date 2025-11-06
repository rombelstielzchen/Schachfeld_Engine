#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../board/board_constants.h"
#include "../move_generator/move.h"
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

class CPsvModifier {
  public:
    // TODO
    static void clear_psv_table(TPieceSquareValueTable &psv_rable);
    static void assign_psv_table(TPieceSquareValueTable &target_psv, const TPieceSquareValueTable &source_psv);
    static void assign_psv_table(char piece_type, const TPieceSquareValueTable &source_psv);
    static void flip_vertically(TPieceSquareValueTable &psv_table);
    static void negate(TPieceSquareValueTable &psv_table);
    static void clone_from_white_to_black(char black_piece_type);
  public:
    static int average(const TPieceSquareValueTable &psv_table);
    static void normalize_average(TPieceSquareValueTable &psv_table, int target_psv);
    static void clone_from_kings_to_queens_bishop(TPieceSquareValueTable &psv_table, int const positive_delta_value);
  public:
    // TODO
    static void add_bonus_to_square(SSquare square, int bonus);
    void add_bonus_to_area(SSquare bottom_left, SSquare top_right, int bonus);
    void add_bonus_to_diagonal(SSquare left_most_square, int bonus);
    void add_bonus_to_anti_diagonal(SSquare left_most_square, int bonus);
  public:
    // TODO:
    void add_bonus_to_center(int bonus);
    void add_bonus_to_extended_center(int bonus);
    void add_bonus_to_kindside(int bonus);
    void add_bonus_to_queenside(int bonus);
  public:
    static void show_psv_table(char piece_type);
    static void show_main_psv_tables();
};

