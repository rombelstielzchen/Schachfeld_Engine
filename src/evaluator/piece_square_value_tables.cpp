// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "piece_square_value_tables.h"
#include "score_constants.h"
#include "../board/distances.h"
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
    for (const SSquare s: ALL_SQUARES) {
        target_psv[s.file][s.rank] = source_psv[s.file][s.rank];
    }
    assert(target_psv[FILE_A][RANK_1] == source_psv[FILE_A][RANK_1]);
    assert(target_psv[FILE_H][RANK_8] == source_psv[FILE_H][RANK_8]);
}

void CPsvModifier::assign_psv_table(char piece_type, const TPieceSquareValueTable &source_psv) {
    assert(is_any_piece(piece_type));
    assign_psv_table(main_piece_square_value_table_set[piece_type], source_psv);
}

void CPsvModifier::flip_vertically(TPieceSquareValueTable &psv_table) {
    for (TFile j = FILE_A; j <= FILE_H; ++j) {
       std::swap(psv_table[j][RANK_1], psv_table[j][RANK_8]);
       std::swap(psv_table[j][RANK_2], psv_table[j][RANK_7]);
       std::swap(psv_table[j][RANK_3], psv_table[j][RANK_6]);
       std::swap(psv_table[j][RANK_4], psv_table[j][RANK_5]);
    }
}

void CPsvModifier::negate(TPieceSquareValueTable &psv_table) {
    for (const SSquare s: ALL_SQUARES) {
        psv_table[s.file][s.rank] = -psv_table[s.file][s.rank];
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

int CPsvModifier::average(const TPieceSquareValueTable &psv_table) {
    int64_t sum = 0;
    for (const SSquare s: ALL_SQUARES) {
        sum += psv_table[s.file][s.rank];
    }
    int64_t average = sum / N_SQUARES_ON_BOARD;
    assert(average >= INT_MIN);
    assert(average <= INT_MAX);
    return static_cast<int>(average);
}

void CPsvModifier::normalize_average(TPieceSquareValueTable &psv_table, int target_average) {
    int average_value = average(psv_table);
    int delta = target_average - average_value;
    for (const SSquare s: ALL_SQUARES) {
        psv_table[s.file][s.rank] += delta;
    }
#ifndef NDEBUG
    constexpr int smaller_than_1_rounded_to_0 = 0;
#endif
    assert(average(psv_table) - target_average == smaller_than_1_rounded_to_0);
}

void CPsvModifier::clone_from_kings_to_queens_bishop(TPieceSquareValueTable &psv_table, int const positive_delta_value) {
    assert(positive_delta_value > 0);
    assert(positive_delta_value < SCORE_HALF_PAWN);
    for (TRank j = RANK_1; j <= RANK_7; j += 2) {
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

void CPsvModifier::show_psv_table(char piece_type) {
    assert(is_any_piece(piece_type));
    std::cout << "*** " <<piece_type << " **************\n";
    for (TFile j = FILE_A; j <= FILE_H; ++j) {
        std::cout << file_as_text(j) << ": ";
        for (TRank k = RANK_1; k <= RANK_8; ++k) {
            std::cout << main_piece_square_value_table_set[piece_type][j][k] << " ";
        }
        std::cout << "\n"; 
    }
    std::cout << "avg: " << average(main_piece_square_value_table_set[piece_type]) << "\n";
}

void CPsvModifier::show_main_psv_tables() {
    show_psv_table(WHITE_POWER);
    show_psv_table(WHITE_KNIGHT);
    show_psv_table(WHITE_BISHOP);
    show_psv_table(WHITE_ROOK);
    show_psv_table(WHITE_QUEEN);
    show_psv_table(WHITE_KING);
    show_psv_table(BLACK_POWER);
    show_psv_table(BLACK_KNIGHT);
    show_psv_table(BLACK_BISHOP);
    show_psv_table(BLACK_ROOK);
    show_psv_table(BLACK_QUEEN);
    show_psv_table(BLACK_KING);
}

void CPsvModifier::set_psv_row(TPieceSquareValueTable &psv_table, const TRank rank, const int value) {
    assert(rank_in_range(rank));
    assert(abs(value) <= SCORE_KING);
    for (TFile j = FILE_A; j<= FILE_H; ++j) {
        psv_table[j][rank] = value;
    }
}

void CPsvModifier::set_psv_row(char piece_type, const TRank rank, const int value) {
    assert(is_any_piece(piece_type));
    assert(rank_in_range(rank));
    assert(abs(value) <= SCORE_KING);
    set_psv_row(main_piece_square_value_table_set[piece_type], rank, value);
}

void CPsvModifier::add_bonus_to_square(TPieceSquareValueTable &psv_table, SSquare square, int bonus) {
    assert(square_in_range(square));
    assert(abs(bonus) <= SCORE_KING);
    psv_table[square.file][square.rank] += bonus;
}

void CPsvModifier::add_bonus_to_area(TPieceSquareValueTable &psv_table, SSquare bottom_left, SSquare top_right, int bonus) {
    assert(square_in_range(bottom_left));
    assert(square_in_range(top_right));
    assert(abs(bonus) <= SCORE_KING);
    TFile left = std::min(bottom_left.file, top_right.file);
   TFile  right = std::max(bottom_left.file, top_right.file);
    TRank bottom = std::min(bottom_left.rank, top_right.rank);
    TRank top = std::max(bottom_left.rank, top_right.rank);
    for  (TFile j = left; j <= right; ++j) {
        for (TRank k = bottom; k <= top; ++k) {
            SSquare to_be_modified = {j, k};
            add_bonus_to_square(psv_table, to_be_modified, bonus);
        }
    }
}

void CPsvModifier::clear_psv_table(TPieceSquareValueTable &psv_table) {
    make_equal(psv_table, 0);
}

void CPsvModifier::make_equal(TPieceSquareValueTable &table, int value) {
    assert(abs(value) <= SCORE_KING);
    for (const SSquare s: ALL_SQUARES) {
        table[s.file][s.rank] = value;
    }
}

void CPsvModifier::make_gradient(TPieceSquareValueTable &table, const SSquare target_square, int bonus_per_step) {
    assert(abs(bonus_per_step) <= SCORE_HALF_PAWN);
    assert(square_in_range(target_square));
    int base_value = table[target_square.file][target_square.rank];
    // We use Euclidean metric here, 
    // as both Manhattan-metric and maximum(dx, dy) look inappropriate.
    for (const SSquare s: ALL_SQUARES) {
        double  distance = CDistances::euclidian_distance(target_square, s);
        assert(distance < 10);
        double evaluation_difference = distance * bonus_per_step;
        // TODO: correct cast?
        int square_value = base_value - static_cast<int>(evaluation_difference);
        table[s.file][s.rank] = square_value;
    }
}

void CPsvModifier::add_bonus_to_colour_complex(TPieceSquareValueTable &table, TSquareColour colour, int bonus) {
    for (const SSquare s: ALL_SQUARES) {
        if (board.square_colour(s) == colour) {
            add_bonus_to_square(table, s, bonus);
            // TODO: bonus_for???
        }
    }
}

