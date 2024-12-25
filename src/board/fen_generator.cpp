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
        + get_side_to_move()
        + separator
        + get_castling_rights()
        + separator
        + get_eng_passeng()
        + separator
        + get_100_ply_draw_counter()
        + separator
        + get_move_counter();
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
    return (board.get_side_to_move() == WHITE_PLAYER) ? "w" : "b";
}

std::string CFenGenerator::get_eng_passeng() {
    char eng_passeng_file = board.get_eng_passeng_file();
    if (eng_passeng_file == NO_ENG_PASSENG_POSSIBLE)  {
        return "-";
    }
    assert(file_in_range(eng_passeng_file));
    std::string result{file_as_text(eng_passeng_file)};
    if (board.get_side_to_move() == WHITE_PLAYER) {
       result.push_back('6');
    } else {
        result.push_back('3');
    }
    return result;
}

std::string CFenGenerator::get_move_counter() {
    assert(board.get_move_counter() > 0);
    return std::to_string(board.get_move_counter());
}

std::string CFenGenerator::get_100_ply_draw_counter() {
    std::string result = std::to_string(board.get_100_ply_draw_counter());
    return std::to_string(board.get_100_ply_draw_counter());
}

std::string CFenGenerator::get_castling_rights() {
    std::string result = "";
    result += board.get_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING) ? "K" : "";
    result += board.get_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING) ? "Q" : "";
    result += board.get_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING) ? "k" : "";
    result += board.get_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING) ? "q" : "";
    if (result == "") {
        return "-";
    }
    return result;
}
