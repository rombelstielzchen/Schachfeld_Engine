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
    const std::string START_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    set_fen_position(START_POSITION);
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

bool CBoard::set_fen_position(const std::string &position) {
    clear();
    squares[4][5] = 'A';
    return CFenParser::parse(position);
}

const std::string CBoard::get_fen_position() {
    std::string result = "TODO";
    return result;
}

const char* const CBoard::as_is() const {
    assert(squares.back().back() == '\0');
    return &squares[0][0];
}


const TSquare CBoard::get_square(const int x, const int y) {
    return squares[x][y];
}

CBoard board;
