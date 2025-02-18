// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "piece_square_value_tables.h"

TPieceSquareValueTable psv_white_king = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 130, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 130, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 }}};
TPieceSquareValueTable psv_white_queen = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100,  70, 100 },
    { 0,   0, 100, 100,  90, 120, 120, 120, 100, 100 },
    { 0,   0, 100, 100, 120, 130, 130, 120, 100, 100 },
    { 0,   0, 100, 100, 120, 130, 130, 120, 100, 100 },
    { 0,   0, 100, 100, 120, 120, 120, 120, 110, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 110, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 110, 110 }}};

TPieceSquareValueTable psv_white_rook = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 150, 120 }}};

TPieceSquareValueTable psv_white_bishop = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 120, 120, 120, 120, 120, 120, 100 },
    { 0,   0, 100, 100, 130, 130, 130, 130, 100, 100 },
    { 0,   0, 100, 100, 130, 150, 150, 140, 100, 100 },
    { 0,   0, 100, 100, 130, 150, 150, 140, 100, 100 },
    { 0,   0, 100, 100, 130, 130, 130, 130, 100, 100 },
    { 0,   0, 100, 120, 120, 120, 120, 120, 120, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 }}};
TPieceSquareValueTable psv_white_knight = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 130, 130, 130, 130, 100, 100 },
    { 0,   0, 100, 100, 130, 150, 150, 140, 100, 100 },
    { 0,   0, 100, 100, 130, 150, 150, 140, 100, 100 },
    { 0,   0, 100, 100, 130, 130, 130, 130, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 }}};

TPieceSquareValueTable psv_white_power = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 130, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 120, 115, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 110, 100, 100, 100, 100, 100, 100 }}};

TPieceSquareValueTable psv_dummy = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 },
    { 0,   0, 3141, 3141, 3141, 3141, 3141, 3141, 3141, 3141 }}};

// TODO: create a class, once things work

void assign_psv_table(TPieceSquareValueTable &target_psv, const TPieceSquareValueTable &source_psv) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            target_psv[j][k] = source_psv[j][k];
        }
    }
    assert(target_psv[FILE_A][RANK_1] == source_psv[FILE_A][RANK_1]);
    assert(target_psv[FILE_H][RANK_8] == source_psv[FILE_H][RANK_8]);
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

void negate(TPieceSquareValueTable &psv_table) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            psv_table[j][k] = -psv_table[j][k];
        }
    }
}

void clone_from_white_to_black(char black_piece_type) {
    assert(is_any_piece(black_piece_type));
    assert(islower(black_piece_type));
    char white_piece_type = toupper(black_piece_type);
    assert(is_any_piece(white_piece_type));
    assert(white_piece_type != black_piece_type);
    assign_psv_table(main_piece_square_value_table_set[black_piece_type], main_piece_square_value_table_set[white_piece_type]);
    flip_vertically(main_piece_square_value_table_set[black_piece_type]);
    negate(main_piece_square_value_table_set[black_piece_type]);
}

int average(const TPieceSquareValueTable psv_table) {
        DEBUG_METHOD();
    int64_t sum = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            sum += psv_table[j][k];
        }
    }
    int64_t average = sum / N_SQUARES_ON_BOARD;
    assert(average >= INT_MIN);
    assert(average <= INT_MAX);
    return static_cast<int>(average);
}

void normalize_average(TPieceSquareValueTable &psv_table, int target_average) {
    DEBUG_METHOD();
    int average_value = average(psv_table);
    int delta = target_average - average_value;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            psv_table[j][k] += delta;
        }
    }
    constexpr int smaller_than_1_rounded_to_0 = 0;
    assert(average(psv_table) - target_average == smaller_than_1_rounded_to_0);
}

void init_main_psv_set() {
    normalize_average(psv_white_power, 100);
    assign_psv_table(WHITE_POWER, psv_white_power);
    normalize_average(psv_white_knight, 290);
    assign_psv_table(WHITE_KNIGHT, psv_white_knight);
    normalize_average(psv_white_bishop, 320);
    assign_psv_table(WHITE_BISHOP, psv_white_bishop);
    normalize_average(psv_white_rook, 470);
    assign_psv_table(WHITE_ROOK, psv_white_rook);
    normalize_average(psv_white_queen, 890);
    assign_psv_table(WHITE_QUEEN, psv_white_queen);
    normalize_average(psv_white_king, 20000);
    assign_psv_table(WHITE_KING, psv_white_king);
    clone_from_white_to_black(BLACK_POWER);
    clone_from_white_to_black(BLACK_KNIGHT);
    clone_from_white_to_black(BLACK_BISHOP);
    clone_from_white_to_black(BLACK_ROOK);
    clone_from_white_to_black(BLACK_QUEEN);
    clone_from_white_to_black(BLACK_KING);
}

