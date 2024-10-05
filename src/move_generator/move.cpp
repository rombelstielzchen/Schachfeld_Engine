// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move.h"
#include "../board/board.h"
#include "../technical_functions/standard_headers.h"

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
    return ((move.source.file == NULL_MOVE.source.file)
        && (move.source.rank == NULL_MOVE.source.rank)
        && (move.target.file == NULL_MOVE.target.file)
        && (move.target.rank == NULL_MOVE.target.rank));
}

bool is_any_piece(char square_or_move_type) {
    switch (square_or_move_type) {
        case WHITE_POWER:
        case WHITE_KNIGHT:
        case WHITE_BISHOP:
        case WHITE_ROOK:
        case WHITE_QUEEN:
        case WHITE_KING:
        case BLACK_POWER:
        case BLACK_KNIGHT:
        case BLACK_BISHOP:
        case BLACK_ROOK:
        case BLACK_QUEEN:
        case BLACK_KING:
            return true;
        default:
            return false;
    }
}

char file_as_text(const int file) {
    assert(file_in_range(file));
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
    assert(rank_in_range(rank));
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
    assert(square_in_range(square));
    std::string result{
        file_as_text(square.file),
        rank_as_text(square.rank)};
    return result;
}

std::string move_as_text(const SMove move) {
    if (is_null_move(move)) {
        return NULL_MOVE_AS_TEXT;
    }
    assert(move_in_range(move));
    std::string result = square_as_text(move.source)
        + square_as_text(move.target);
    if (is_any_piece(move.move_type)) {
        result.push_back(move.move_type);
    }
    return result;
}

uint8_t text_to_file(const char file_character) {
    // No assertions here; the input comes from the outside world
    if ((file_character < 'a') || (file_character > 'h')) {
        return ERROR_INVALID_COORDINATE;
    }
     uint8_t result = FILE_A + file_character - 'a';
     assert(file_in_range(result));
    return result;
}

uint8_t text_to_rank(const char rank_character) {
    // No assertions here; the input comes from the outside world
    if ((rank_character < '1') || (rank_character > '8')) {
        return ERROR_INVALID_COORDINATE;
     }
     uint8_t result = RANK_1 + rank_character - '1';
     assert(rank_in_range(result));
     return result;
}

SMove text_to_move(const std::string &text) {
    // No assertions here; the input comes from the outside world
    if (text.length() < 4) {
       // Not long algebraic notation
        return NULL_MOVE;
    }
    SMove move = {
        text_to_file(text[0]),
        text_to_rank(text[1]),
        text_to_file(text[2]),
        text_to_rank(text[3]),
        // TODO
        MOVE_TYPE_NORMAL
    };
    if (!move_in_range(move)) {
        return NULL_MOVE;
    }
    // TODO promotion
    return move;
}
     
