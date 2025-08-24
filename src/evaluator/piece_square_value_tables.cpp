// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "piece_square_value_tables.h"
#include "score_constants.h"
#include "../move_generator/move.h"

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

void CPsvModifier::assign_psv_table(TPieceSquareValueTable &target_psv, const TPieceSquareValueTable &source_psv) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            target_psv[j][k] = source_psv[j][k];
        }
    }
    assert(target_psv[FILE_A][RANK_1] == source_psv[FILE_A][RANK_1]);
    assert(target_psv[FILE_H][RANK_8] == source_psv[FILE_H][RANK_8]);
}

void CPsvModifier::assign_psv_table(char piece_type, const TPieceSquareValueTable &source_psv) {
    assert(is_any_piece(piece_type));
    assign_psv_table(main_piece_square_value_table_set[piece_type], source_psv);
}

void CPsvModifier::flip_vertically(TPieceSquareValueTable &psv_table) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
       std::swap(psv_table[j][RANK_1], psv_table[j][RANK_8]);
       std::swap(psv_table[j][RANK_2], psv_table[j][RANK_7]);
       std::swap(psv_table[j][RANK_3], psv_table[j][RANK_6]);
       std::swap(psv_table[j][RANK_4], psv_table[j][RANK_5]);
    }
}

void CPsvModifier::negate(TPieceSquareValueTable &psv_table) {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            psv_table[j][k] = -psv_table[j][k];
        }
    }
}

void CPsvModifier::clone_from_white_to_black(char black_piece_type) {
    assert(is_any_piece(black_piece_type));
    assert(islower(black_piece_type));
    char white_piece_type = toupper(black_piece_type);
    assert(is_any_piece(white_piece_type));
    assert(white_piece_type != black_piece_type);
    assign_psv_table(main_piece_square_value_table_set[black_piece_type], main_piece_square_value_table_set[white_piece_type]);
    flip_vertically(main_piece_square_value_table_set[black_piece_type]);
    negate(main_piece_square_value_table_set[black_piece_type]);
}

int CPsvModifier::average(const TPieceSquareValueTable psv_table) {
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

void CPsvModifier::normalize_average(TPieceSquareValueTable &psv_table, int target_average) {
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

void CPsvModifier::clone_from_kings_to_queens_bishop(TPieceSquareValueTable &psv_table, int const positive_delta_value) {
    assert(positive_delta_value > 0);
    assert(positive_delta_value < SCORE_HALF_PAWN);
    for (int j = RANK_1; j <= RANK_7; j += 2) {
    // Always two ranks at once for easy indexing in a single loop
    psv_table[FILE_A][j] = psv_table[FILE_H][j] - positive_delta_value;
    psv_table[FILE_C][j] = psv_table[FILE_F][j] - positive_delta_value;
    psv_table[FILE_E][j] = psv_table[FILE_D][j] - positive_delta_value;
    psv_table[FILE_G][j] = psv_table[FILE_B][j] - positive_delta_value;
    int const next_rank = j + 1;
    psv_table[FILE_B][next_rank] = psv_table[FILE_G][next_rank] - positive_delta_value;
    psv_table[FILE_D][next_rank] = psv_table[FILE_E][next_rank] - positive_delta_value;
    psv_table[FILE_F][next_rank] = psv_table[FILE_C][next_rank] - positive_delta_value;
    psv_table[FILE_H][next_rank] = psv_table[FILE_A][next_rank] - positive_delta_value;
    }
    assert(psv_table[FILE_C][RANK_8] == psv_table[FILE_F][RANK_8] + positive_delta_value);
}

