// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "mate_score.h"
#include "../board/board.h"
#include "../evaluator/score_constants.h"
#include <cassert>

constexpr int SCORE_ADDITIONAL_PLY_TO_MATE = 80;

int CMateScore::losing_mate_score(int distance_to_root_in_plies) {
    assert(distance_to_root_in_plies >= 0);
    int score = SCORE_LOSING_MATE
        + SCORE_ADDITIONAL_PLY_TO_MATE * distance_to_root_in_plies
        - board.evaluator.nega_score();   
;
    assert(score < 0);
    assert(score < -SCORE_KING);
    return score;
}

int CMateScore::winning_mate_score(int distance_to_root_in_plies) {
    assert(distance_to_root_in_plies >= 0);
    int score = SCORE_WINNING_MATE
        - SCORE_ADDITIONAL_PLY_TO_MATE * distance_to_root_in_plies
        - board.evaluator.nega_score();   
    assert(score > 0);
    assert(score > SCORE_KING);
    return score;
}

// TODO: maximize material, when losing.
// losing_mate_score != - winning_mate_score
// due to different side to move and nega_score!

bool CMateScore::is_mate_score(int score__centi_wood_points) {
    static_assert(SCORE_WINNING_MATE > 0);
    static_assert(SCORE_WINNING_MATE > 4 * SCORE_KING);
    return (abs(score__centi_wood_points) > (SCORE_WINNING_MATE / 2));
}

