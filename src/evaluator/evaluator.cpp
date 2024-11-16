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
            char piece = board.get_square(j, k);
            switch (piece) {
                case WHITE_KING:
                    score += 20000;
                    score += castling_bonus(j, k);
                    break;
                case WHITE_QUEEN:
                    score += 900;
                    score += central_bonus(j, k);
                    break;
                case WHITE_ROOK:
                    score += 500;
                    break;
                case WHITE_BISHOP:
                    score += 310;
                    score += central_bonus(j, k);
                    break;
                case WHITE_KNIGHT:
                    score += 290;
                    score += central_bonus(j, k);
                    break;
                case WHITE_POWER:
                    score += 100;
                    break;
                case BLACK_KING:
                    score -= 20000;
                    score -= castling_bonus(j, k);
                    break;
                case BLACK_QUEEN:
                    score -= 900;
                    score -= central_bonus(j, k);
                    break;
                case BLACK_ROOK:
                    score -= 500;
                    break;
                case BLACK_BISHOP:
                    score -= 310;
                    score -= central_bonus(j, k);
                    break;
                case BLACK_KNIGHT:
                    score -= 290;
                    score -= central_bonus(j, k);
                    break;
                case BLACK_POWER:
                    score -= 100;
                    break;
            }
        }
    }
    return score;
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

