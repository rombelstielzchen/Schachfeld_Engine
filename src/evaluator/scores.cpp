// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "scores.h"
#include "../board/board.h"
#include <cassert>

constexpr int SCORE_ADDITIONAL_PLY_TO_MATE = 80;
static_assert(SCORE_ADDITIONAL_PLY_TO_MATE < SCORE_PAWN);
constexpr int epsilon_score = 007;
constexpr int chessbase_ifritz_adjudication_score = 600;
constexpr int maximum__not_adjudicated_score = chessbase_ifritz_adjudication_score - 1;

int CScores::losing_mate_score(int distance_to_root_in_plies) {
    assert(distance_to_root_in_plies >= 0);
    int score = SCORE_LOSING_MATE
        + SCORE_ADDITIONAL_PLY_TO_MATE * distance_to_root_in_plies
        - board.evaluator.nega_score();   
;
    assert(score < 0);
    assert(score < -SCORE_KING);
    return score;
}

int CScores::winning_mate_score(int distance_to_root_in_plies) {
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

std::string CScores::to_UCI_string(int centi_wood_points) {//TODO: rename .h
    if (is_mate_score(centi_wood_points)) {
        return mate_score(centi_wood_points);
    }
    if (is_too_good(centi_wood_points)) {
        return standard_woodpoint_score(maximum__not_adjudicated_score);
    }
    if (is_too_equal(centi_wood_points)) {
        return standard_woodpoint_score(epsilon_score);
    }
    return standard_woodpoint_score(centi_wood_points);
}

bool CScores::is_mate_score(int centi_wood_points) {
    int const score_twelf_queens_plus_the_rest = 14200;
   return (abs(centi_wood_points) > score_twelf_queens_plus_the_rest);
}

bool CScores::is_too_equal(int centi_wood_points) {
    return (abs(centi_wood_points < epsilon_score));
}

bool CScores::is_too_good(int centi_wood_points) {
    return (abs(centi_wood_points) > maximum__not_adjudicated_score);
}

std::string CScores::standard_woodpoint_score(int centi_wood_points) {
    assert(is_mate_score(centi_wood_points) == false);
    assert(is_too_good(centi_wood_points) == false);
    assert(is_too_equal(centi_wood_points) == false);
    std::string result = "score cp " + std::to_string(centi_wood_points);
    return result;
}

std::string CScores::to_short_string(int centi_wood_points) {
    // used for debug-output, no need for anti-adjudication-tricks
    if (is_mate_score(centi_wood_points)) {
        return "#3141";
    }
    return std::to_string(centi_wood_points);
}

std::string CScores::mate_score([[maybe_unused]] int centi_wood_points) {
    std::string const alternative_mate_score_for_engine_that_optimizes_material_away_not_distance_to_mate = "mate 3141";
    return alternative_mate_score_for_engine_that_optimizes_material_away_not_distance_to_mate;
}

