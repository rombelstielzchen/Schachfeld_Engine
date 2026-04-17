// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "distances.h"
#include "square_constants.h"

double CDistances::euclidian_distance(const SSquare a, const SSquare b) {
    assert(square_in_range(a));
    assert(square_in_range(b));
    int dx = a.file - b.file;
    int dy = a.rank - b.rank;
    double result = sqrt(dx * dx + dy * dy);
    constexpr double length_of_main_diagonal = 9.9;
    assert(result <= length_of_main_diagonal);
    return result;
}

SSquare CDistances::nearest_square(const SSquare target_square, TSquareList square_list) {
    assert(square_in_range(target_square));
    if (square_list.size() <= 0) {
        return NULL_SQUARE;
    }
    SSquare best_square = square_list[0];
    assert(square_in_range(best_square));
    double smallest_distance = euclidian_distance(target_square, best_square);
    assert(smallest_distance >= 0);
    for (size_t j = 1; j < square_list.size(); ++j) {
        if (euclidian_distance(target_square, square_list[j]) < smallest_distance) {
            best_square = square_list[j];
            smallest_distance = euclidian_distance(target_square, best_square);
        }
    }
    assert(square_in_range(best_square));
    assert(smallest_distance >= 0);
    assert((smallest_distance > 0) || (best_square == target_square));
    return best_square;
}

