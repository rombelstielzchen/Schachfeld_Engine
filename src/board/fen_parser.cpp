#include <iostream>
#include <string>

#include "board.h"

class CFenParser {
  public:
    static bool parse(CBoard &board_to_be_setup, const std::string &fen_board_specification);
  private:
    static bool parse_piece_placement(CBoard &board, const std::string &partial_input);
    static bool parse_side_to_move(CBoard &board, const std::string &partial_input);
    static bool parse_castling_rights(CBoard &board, const std::string &partial_input);
    static bool parse_eng_passeng(CBoard &board, const std::string &partial_input);
    static bool parse_100_ply_draw_counter(CBoard &board, const std::string &partial_input);
    bool parse_move_counter(CBoard &board, const std::string &partial_input);
};






// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

///#include "fen_parser.h"
#include "board.h"
#include "../technical_functions/string_functions.h"

bool CFenParser::parse(CBoard &board_to_be_setup, const std::string &fen_board_specification) {
    
    bool lack_of_errors = true;
    CStringTokenizer tokenizer(fen_board_specification);
    lack_of_errors &= parse_piece_placement(board_to_be_setup, tokenizer.next_token());
    // TODO: functions below
    lack_of_errors &= parse_side_to_move(board_to_be_setup, tokenizer.next_token());
    lack_of_errors &= parse_castling_rights(board_to_be_setup, tokenizer.next_token());
    lack_of_errors &= parse_eng_passeng(board_to_be_setup, tokenizer.next_token());
    lack_of_errors &= parse_100_ply_draw_counter(board_to_be_setup, tokenizer.next_token());
//    lack_of_errors &= parse_move_counter(board_to_be_setup, tokenizer.next_token());
    return lack_of_errors;
}

bool CFenParser::parse_piece_placement(CBoard &board, const std::string &partial_input) {
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
    case '1' ... '8': {
            int gap = c - '0';
            x += gap;
            }
            break;
     default:
            // Unexpected character, non recoverable
            return false;
        }
    }
    std::cout << board.as_is();
     return true;
}

bool CFenParser::parse_side_to_move(CBoard &board, const std::string &partial_input) {
    return true;
}

bool CFenParser::parse_castling_rights(CBoard &board, const std::string &partial_input) {
    return true;
}

bool CFenParser::parse_eng_passeng(CBoard &board, const std::string &partial_input) {
    return true;
}

bool CFenParser::parse_100_ply_draw_counter(CBoard &board, const std::string &partial_input) {
    return true;
}
bool CFenParser::parse_move_counter(CBoard &board, const std::string &partial_input) {
    return true;
}

