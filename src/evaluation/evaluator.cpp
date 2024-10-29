// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "evaluator.h"
#include "../board/board.h"

int CEvaluator::evaluate() {
    int score = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            char piece = board.get_square(j, k);
            switch (piece) {
                case WHITE_KING:
                    score += 20000;
                    break;
                case WHITE_QUEEN:
                    score += 900;
                    break;
                case WHITE_ROOK:
                    score += 500;
                    break;
                case WHITE_BISHOP:
                    score += 310;
                    break;
                case WHITE_KNIGHT:
                    score += 290;
                    break;
                case WHITE_POWER:
                    score += 100;
                    break;
                case BLACK_KING:
                    score -= 20000;
                    break;
                case BLACK_QUEEN:
                    score -= 900;
                    break;
                case BLACK_ROOK:
                    score -= 500;
                    break;
                case BLACK_BISHOP:
                    score -= 310;
                    break;
                case BLACK_KNIGHT:
                    score -= 290;
                    break;
                case BLACK_POWER:
                    score -= 100;
                    break;
            }
        }
    }
    return score;
}

