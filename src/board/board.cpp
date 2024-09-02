// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board.h"
#include "fen_parser.h"
#include "../technical_functions/standard_headers.h"

CBoard::CBoard() {
    assert(FILE_LAST == BOARDSIZE_X - 1);
    assert(RANK_NEWLINE_CHARACTER == BOARDSIZE_Y - 1);
    init_garden_fence();
    clear();
    set_start_position();
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
    const std::string START_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    set_fen_position(START_POSITION);
}

bool CBoard::set_fen_position(const std::string &position) {
    clear();
    squares[4][5] = 'A';
    return CFenParser::parse(position);
}

std::string CBoard::get_fen_position() const {
    std::string result = "TODO";
    return result;
}

const char* const CBoard::as_is() const {
    assert(squares.back().back() == '\0');
    return &squares[0][0];
}


TSquare CBoard::get_square(const int x, const int y) const {
    return squares[x][y];
}

ESideToMove CBoard::get_side_to_move() const {
    return side_to_move;
}

bool CBoard::make_move(SMove move) {
    // TODO: castling, eng-passeng, promotion
    // TODO: lots of sanity checks
    DEBUG_METHOD();
    DEBUG_VALUE_OF(move.source.file);
    assert(move_in_range(move));
    char moving_piece = squares[move.source.file][move.source.rank];
    DEBUG_VALUE_OF(moving_piece);
    squares[move.source.file][move.source.rank] = EMPTY_SQUARE;
    squares[move.target.file][move.target.rank] = moving_piece;
    return true;
}

CBoard board;
