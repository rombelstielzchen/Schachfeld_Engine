// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board_geometry.h"
#include "../move_generator/move.h"

bool CBoardGeometry::on_same_diagonal(const SSquare a, const SSquare b) {
    assert(square_in_range(a));
    assert(square_in_range(b));
    return ((a.file +b.rank) == (b.file + a.rank));
}

bool CBoardGeometry::on_same_anti_diagonal(const SSquare a, const SSquare b) {
    return ((a.file + a.rank) == (b.file + b.rank));
}

TFile CBoardGeometry::excentric_neighbour_file(TFile file) {
    assert(file_in_range(file));
    return (file <= FILE_D) ? (file - 1) : (file + 1);
}

TFile CBoardGeometry::central_neighbour_file(TFile file) {
    assert(file_in_range(file));
    return (file <= FILE_D) ? (file + 1) : (file - 1);
}

