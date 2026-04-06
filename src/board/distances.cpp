// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "distances.h"

double CDistances::euclidian_distance(const SSquare a, const SSquare b) {
    assert(square_in_range(a));
    assert(square_in_range(b));
    int dx = a.file - b.file;
    int dy = a.rank - b.rank;
    double result = sqrt(dx * dx + dy * dy);
    constexpr int length_of_main_diagonal = 9.9;
    assert(result <= length_of_main_diagonal);
    return result;
}

