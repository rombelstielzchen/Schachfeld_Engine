// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_generator.h"
#include <cassert>

CMoveGenerator::CMoveGenerator() {
    number_of_moves = 0;
}

void CMoveGenerator::generate_all() {
}

TMove CMoveGenerator::get_random() const {
    if (number_of_moves <= 0) {
        constexpr TMove NULL_MOVE = 0;
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for a temp function
    int index = rand() % number_of_moves;
    return move_list[index];
}

int CMoveGenerator::list_size() const {
    assert(number_of_moves <= MAX_MOVES_IN_CHESS_POSITION);
    return number_of_moves;
}

std::string as_text(const TMove move) {
    return "a2a3";
}

