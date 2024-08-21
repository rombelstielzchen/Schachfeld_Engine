// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move.h"
#include "../board/board.h"
#include <cassert>

bool file_in_range(const int file) {
    return ((file >= FILE_A) && (file <= FILE_H));
}

bool rank_in_range(const int rank) {
    return ((rank >= RANK_1) && (rank <= RANK_8));
}

bool square_in_range(const SSquare square) {
    return (file_in_range(square.file) && rank_in_range(square.rank));
}

bool move_in_range(const SMove move) {
    return (square_in_range(move.source) && square_in_range(move.target));
}

bool is_null_move(const SMove move) {
    // TODO: replace by ssomething simple and eficient
    return ((move.source.file == NULL_MOVE.source.file)
        && (move.source.rank == NULL_MOVE.source.rank)
        && (move.target.file == NULL_MOVE.target.file)
        && (move.target.rank == NULL_MOVE.target.rank));
}

char file_as_text(const int file) {
    switch (file) {
        case FILE_A:
            return 'a';
        case FILE_B:
            return 'b';
        case FILE_C:
            return 'c';
        case FILE_D:
            return 'd';
        case FILE_E:
            return 'e';
        case FILE_F:
            return 'f';
        case FILE_G:
            return 'g';
        case FILE_H:
            return 'h';
        default:
            assert(false);
            return '-';
    }
}

char rank_as_text(const int rank) {
    switch (rank) {
        case RANK_1:
            return '1';
        case RANK_2:
            return '2';
        case RANK_3:
            return '3';
        case RANK_4:
            return '4';
        case RANK_5:
            return '5';
        case RANK_6:
            return '6';
        case RANK_7:
            return '7';
        case RANK_8:
            return '8';
        default:
            assert(false);
            return '-';
    }
}

std::string square_as_text(const SSquare square) {
    std::string result{file_as_text(square.file), rank_as_text(square.rank)};
    return result;
}

std::string move_as_text(const SMove move) {
    return (square_as_text(move.source) + square_as_text(move.target));
}
