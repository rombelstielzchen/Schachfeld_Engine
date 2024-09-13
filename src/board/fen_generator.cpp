// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "fen_generator.h"
std::string CFenGenerator::get_fen_position()
{
    const std::string separator = " ";
    return get_piece_placement()
        + separator
        + get_side_to_move();
    // TODO: all the rest
}

std::string CFenGenerator::get_piece_placement() {
    std::string result = "";
    // 8th rank first, from a8 to h1
    for (int k = RANK_8; k >= RANK_1; --k) {
        char empty_squares = '0';
        for (int j = FILE_A; j <= FILE_H; ++j) {
            const char square = board.get_square(j, k);
            switch (square) {
                case EMPTY_SQUARE:
                    ++empty_squares;
                    break;
                default:
                    assert(isalpha(square));
                    if (empty_squares > '0') {
                        assert(isdigit(empty_squares));
                        result.push_back(empty_squares);
                        empty_squares = '0';
                    }
                    result.push_back(square);
                    break;
            }
        }
       // End of row
        if (empty_squares > '0') {
            assert(isdigit(empty_squares));
            result.push_back(empty_squares);
            empty_squares = '0';
        }
        if (k > RANK_1) {
            result.push_back('/');
        }
    }
    return result;
}

std::string CFenGenerator::get_side_to_move() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? "w" : "b";
}
