// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "fen_parser.h"
#include "../technical_functions/string_functions.h"

bool CFenParser::parse(const std::string &fen_board_specification) {
    DEBUG_METHOD();
    bool lack_of_errors = true;
    CStringTokenizer tokenizer(fen_board_specification);
    std::string piece_placement = tokenizer.next_token();
    if (piece_placement == "startpos") {
        // UCI may send "startpos" instead of a complicated FEN
        board.set_start_position();
    } else {
        // Standard case: full FEN, consisting of multiple tokens
        lack_of_errors &= parse_piece_placement(piece_placement);
        // TODO: functions below
        lack_of_errors &= parse_side_to_move(tokenizer.next_token());
        lack_of_errors &= parse_castling_rights(tokenizer.next_token());
        lack_of_errors &= parse_eng_passeng(tokenizer.next_token());
        lack_of_errors &= parse_100_ply_draw_counter(tokenizer.next_token());
        lack_of_errors &= parse_move_counter(tokenizer.next_token());
    }
    std::string optional_move = tokenizer.next_token();
    while (optional_move != "") {
        lack_of_errors &= parse_move(optional_move);
        optional_move = tokenizer.next_token();
    }
    return lack_of_errors;
}

bool CFenParser::parse_piece_placement(const std::string &partial_input) {
    DEBUG_METHOD();
    board.clear();
    // FEN traverses the board row by row from A8 to H1
    int x = FILE_A;
    int y = RANK_8;
    for (const char& c : partial_input) {
         if (c == '/') {
            x = FILE_A;
            --y;
            continue;
         }
        if (x > FILE_H) {
            // Non-recoverable error, bad input from the outside world
            return false;
        }
        if (y < RANK_1) {
            return false;
        }
        switch (c) {
                case WHITE_KING:
                case WHITE_QUEEN:
    case WHITE_ROOK:
    case WHITE_BISHOP:
    case WHITE_KNIGHT:
    case WHITE_POWER:
    case BLACK_KING:
    case BLACK_QUEEN:
    case BLACK_ROOK:
    case BLACK_BISHOP:
    case BLACK_KNIGHT:
    case BLACK_POWER:
            board.squares[x][y] = c;
            ++x;
            break;
    case '1' : 
    case '2' : 
    case '3' : 
    case '4' : 
    case '5' : 
    case '6' : 
    case '7' : 
    case '8' : {
            int gap = c - '0';
            x += gap;
            }
            break;
     default:
            // Unexpected character, non recoverable
            return false;
        }
    }
///    std::cout << board.as_is();
     return true;
}

bool CFenParser::parse_side_to_move(const std::string &partial_input) {
    if (partial_input == "w") {
        board.side_to_move = WHITE_TO_MOVE;
        return true;
    } else if (partial_input == "b") {
        board.side_to_move = BLACK_TO_MOVEE;
        return true;
    }
    // Unexpected character
    return false;
}

bool CFenParser::parse_castling_rights(const std::string &partial_input) {
    return true;
}

bool CFenParser::parse_eng_passeng(const std::string &partial_input) {
    return true;
}

bool CFenParser::parse_100_ply_draw_counter(const std::string &partial_input) {
    return true;
}
bool CFenParser::parse_move_counter(const std::string &partial_input) {
    return true;
}

bool CFenParser::parse_move(std::string move_as_text) {
    DEBUG_METHOD();
    DEBUG_VALUE_OF(move_as_text);
    SMove move = text_to_move(move_as_text);
    board.make_move(move);
    return true;
}

