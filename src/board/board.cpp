// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board.h"
#include "fen_generator.h"
#include "fen_parser.h"
#include "../technical_functions/standard_headers.h"

CBoard::CBoard() {
    init_garden_fence();
    clear();
    set_start_position();
    assert(side_to_move == WHITE_TO_MOVE);
    assert(move_counter > 0);
}

void CBoard::init_garden_fence() {
    for (int j = 0; j < BOARDSIZE_X; ++j) {
        for (int k = 0; k < BOARDSIZE_Y; ++k) {
            squares[j][k] = GARDEN_FENCE;
        }
        squares[j][RANK_NEWLINE_CHARACTER] = '\n';
    }
    // Data ends with newline and string-termination for using as_iss()
    squares[FILE_LAST][RANK_NEWLINE_CHARACTER - 1] = '\n';
    squares[FILE_LAST][RANK_NEWLINE_CHARACTER] = '\0';
}

void CBoard::clear() {
    for (int j = FILE_A; j<= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            squares[j][k] = EMPTY_SQUARE;
        }
    }
}

void CBoard::set_start_position() {
    set_fen_position(START_POSITION);
    moves_from_startpos = "";
    assert(get_fen_position() == START_POSITION);
    assert(get_side_to_move() == WHITE_TO_MOVE);
    assert(get_eng_passeng_file() == NO_ENG_PASSENG_POSSIBLE);
}

bool CBoard::set_fen_position(const std::string &position) {
    clear();
    moves_from_startpos = "";
    bool success = CFenParser::parse(position);
    std::cerr << "New position: " << get_fen_position() << std::endl;
    return success;
}

std::string CBoard::get_fen_position() const {
    return CFenGenerator::get_fen_position(); 
}

const char*  CBoard::as_is() const {
    assert(squares.back().back() == '\0');
    return &squares[0][0];
}

TSquare CBoard::get_square(const int file, const int rank) const {
    // We might access th fence here, so no chech for in_range()
    assert(file >= 0);
    assert(file <= FILE_LAST);
    assert(rank >= 0);
    assert(rank <= RANK_NEWLINE_CHARACTER);
    return squares[file][rank];
}

bool CBoard::square_is_empty(const int file, const int rank) const {
    return (get_square(file, rank) == EMPTY_SQUARE);
}

int CBoard::get_eng_passeng_file() const {
    assert((eng_passeng_file == NO_ENG_PASSENG_POSSIBLE) || file_in_range(eng_passeng_file));
    return eng_passeng_file;
}

int CBoard::get_move_counter() const {
    assert(move_counter > 0);
    return move_counter;
}

int CBoard::get_100_ply_draw_counter() const {
    assert(_100_ply_draw_counter >= 0);
    return _100_ply_draw_counter;
}

void CBoard::clear_castling_rights() {
    set_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING, false);
    set_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING, false);
    set_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING, false);
    set_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING, false);
}

void CBoard::set_castling_rights(const char move_type, bool yes_no) {
    assert((move_type == MOVE_TYPE_WHITE_SHORT_CASTLING)
        || (move_type == MOVE_TYPE_WHITE_LONG_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_SHORT_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_LONG_CASTLING));
    castling_rights[move_type] = yes_no;
}

bool CBoard::get_castling_rights(char move_type) const {
    assert((move_type == MOVE_TYPE_WHITE_SHORT_CASTLING)
        || (move_type == MOVE_TYPE_WHITE_LONG_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_SHORT_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_LONG_CASTLING));
    return castling_rights[move_type];
}

void CBoard::clear_square(const int file, const int rank) {
    assert(file_in_range(file));
    assert(rank_in_range(rank));
    squares[file][rank] = EMPTY_SQUARE;
}

void CBoard::put_piece(const int file, const int rank, char piece) {
    assert(file_in_range(file));
    assert(rank_in_range(rank));
///    assert(is_any_piece(piece));
    squares[file][rank] = piece;
}

