// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "evaluator.h"
#include "../board/board.h"

constexpr int half_pawn = 50;

int CEvaluator::evaluate() const {
    int score = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            score += evaluate_square(j, k);
        }
    }
    return score;
}

int CEvaluator::evaluate_square(const SSquare &square) const {
    return evaluate_square(square.file, square.rank);
}

int CEvaluator::evaluate_square(const int file, const int rank) const {
    char piece = board.get_square(file, rank);
    switch (piece) {
        case WHITE_KING:
            return (20000 + castling_bonus(file, rank));
        case WHITE_QUEEN:
            return (900 + central_bonus(file, rank));
        case WHITE_ROOK:
            return 500;
        case WHITE_BISHOP:
            return (310 + central_bonus(file, rank));
        case WHITE_KNIGHT:
            return (290 + central_bonus(file, rank));
        case WHITE_POWER:
            return 100;
        case BLACK_KING:
            return (-20000 - castling_bonus(file, rank));
        case BLACK_QUEEN:
            return (-900 - central_bonus(file, rank));
        case BLACK_ROOK:
            return -500;
        case BLACK_BISHOP:
            return (-310 - central_bonus(file, rank));
        case BLACK_KNIGHT:
            return (-290 - central_bonus(file, rank));
        case BLACK_POWER:
            return -100;
        default:
            assert(piece == EMPTY_SQUARE);
            return 0;
    }
}

bool CEvaluator::evaluates_approximately_to(const int score) const {
    int real_score = evaluate();
    return (abs(real_score - score) < half_pawn);
}

int CEvaluator::central_bonus(const int file, const int rank) const {
    int bonus = 0;
    bonus += (file >= FILE_C) && (file <= FILE_F) ? 15 : 0;
    bonus += (rank >= RANK_3) && (rank <= RANK_6) ? 20 : 0;
    return bonus;
}

int CEvaluator::castling_bonus(const int file, const int rank) const {
    if ((file != FILE_G) && (file != FILE_C)) {
        return 0;
    }
    if ((rank != RANK_1) && (rank != RANK_8)) {
        return 0;
    }
    return 23;
}

