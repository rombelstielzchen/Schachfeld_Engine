// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "piece_square_value_tables.h"

const TPieceSquareValueTable psv_white_king = { 0 };
const TPieceSquareValueTable psv_white_queen = { 0 };
const TPieceSquareValueTable psv_white_rook = { 0 };
const TPieceSquareValueTable psv_white_bishop = { 0 };
const TPieceSquareValueTable psv_white_knight = { 0 };

const TPieceSquareValueTable psv_white_power = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 }}};

// TODO: create a class, once things work

void assign_psv_table(TPieceSquareValueTable &target_psv, const TPieceSquareValueTable &source_psv) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++j) {
            target_psv[j][k] = source_psv[j][k];
        }
    }
}

void assign_psv_table(char piece_type, const TPieceSquareValueTable &source_psv) {
    assert(is_any_piece(piece_type));
    assign_psv_table(main_piece_square_value_table_set[piece_type], source_psv);
}

void flip_vertically(TPieceSquareValueTable &psv_table) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
       std::swap(psv_table[j][RANK_1], psv_table[j][RANK_8]);
       std::swap(psv_table[j][RANK_2], psv_table[j][RANK_7]);
       std::swap(psv_table[j][RANK_3], psv_table[j][RANK_6]);
       std::swap(psv_table[j][RANK_4], psv_table[j][RANK_5]);
    }
}

void clone_from_white_to_black(char black_piece_type) {
    assert(is_any_piece(black_piece_type));
    assert(isupper(black_piece_type));
    char white_piece_type = tolower(black_piece_type);
    assert(is_any_piece(white_piece_type));
    assert(white_piece_type != black_piece_type);
    assign_psv_table(main_piece_square_value_table_set[white_piece_type], main_piece_square_value_table_set[black_piece_type]);
    flip_vertically(main_piece_square_value_table_set[black_piece_type]);
}

int average(const TPieceSquareValueTable psv_table) {
    int64_t sum = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++j) {
            sum += psv_table[j][k];
        }
    }
    int64_t average = sum / N_SQUARES_ON_BOARD;
    assert(average >= INT_MIN);
    assert(average <= INT_MAX);
    return static_cast<int>(average);
}

void normalize_average(TPieceSquareValueTable &psv_table, int target_average) {
    int average_value = average(psv_table);
    int delta = target_average - average_value;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++j) {
            psv_table[j][k] += delta;
        }
    }
    constexpr int smaller_than_1_rounded_to_0 = 0;
    assert(average(psv_table) - target_average == smaller_than_1_rounded_to_0);
}

