// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "fen_parser.h"
#include "../move_generator/move_generator.h"
#include "../move_generator/move_list.h"
#include "move_maker.h"
#include "../technical_functions/string_functions.h"

const std::string NO_MOVES_FROM_STARTPOS = "You better calculate, buddy!";

bool CFenParser::parse(const std::string &fen_board_specification) {
    DEBUG_METHOD();
    bool lack_of_errors = true;
    CStringTokenizer tokenizer(fen_board_specification);
    std::string piece_placement = tokenizer.next_token();
    if (piece_placement == "fen") {
        // Ignore "fen".  Position commands have this extra token, test-cases not.
        piece_placement = tokenizer.next_token();
    }
    if (piece_placement == "startpos") {
        // UCI may send "startpos" instead of a complicated FEN
        board.set_start_position();
    } else {
        // Standard case: full FEN, consisting of multiple tokens
        lack_of_errors &= parse_piece_placement(piece_placement);
        lack_of_errors &= parse_side_to_move(tokenizer.next_token());
        lack_of_errors &= parse_castling_rights(tokenizer.next_token());
        lack_of_errors &= parse_eng_passeng(tokenizer.next_token());
        lack_of_errors &= parse_100_ply_draw_counter(tokenizer.next_token());
        lack_of_errors &= parse_move_counter(tokenizer.next_token());
    }
    board.move_maker.reset_history();
    extract_moves_from_startpos(fen_board_specification);
    lack_of_errors = board.move_maker.play_variation(board.get_moves_from_startpos());
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
                if (x > FILE_GARDEN_FENCE_RIGHT_1) {
                    // Extra check that catches "harmless" extra empty squares,
                    // mostly detecting erroneous test-cases
                    return false;
                }
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
    DEBUG_METHOD();
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
    DEBUG_METHOD();
    board.clear_castling_rights();
    if ((partial_input == "-") || (partial_input == "")) {
        return true;
    }
    for (const char &c : partial_input) {
        switch (c) {
            case 'K':
                board.set_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING, true);
                break;
            case 'Q':
                board.set_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING, true);
                break;
            case 'k':
                board.set_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING, true);
                break;
            case 'q':
                board.set_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING, true);
                break;
            default:
                return false;
        }
    }
    return true;
}

bool CFenParser::parse_eng_passeng(const std::string &partial_input) {
    DEBUG_METHOD();
    if ((partial_input == "-") || (partial_input == "")) {
        board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
        return true;
    }
    if (partial_input.length() != 2) {
        return false;
    }
    int file = text_to_file(partial_input[0]);
    if (file_in_range(file)) {
        board.eng_passeng_file = file;
        return true;
    }
    return false;
}

bool CFenParser::parse_100_ply_draw_counter(const std::string &partial_input) {
    // We use the old atoi instead of stoi, because it doesn't throw exceptions 
    // and returns 0 in case of bad input
    board._100_ply_draw_counter = std::max(0, atoi(partial_input.c_str()));
    DEBUG_METHOD();
    return true;
}

bool CFenParser::parse_move_counter(const std::string &partial_input) {
    // We use the old atoi instead of stoi, because it doesn't throw exceptions 
    // and returns 0 in case of bad input
    board.move_counter = std::max(1, atoi(partial_input.c_str()));
    return true;
}

bool CFenParser::parse_move(std::string move_as_text) {
    DEBUG_METHOD();
    DEBUG_VALUE_OF(move_as_text);
    if (move_as_text == "moves") {
       // Token starts sequence of optional moves, Ignore it.
       return true;
    }
    return board.move_maker.make_move(move_as_text);
}

void CFenParser::extract_moves_from_startpos(const std::string &position_command) {
    board.moves_from_startpos = NO_MOVES_FROM_STARTPOS;
    CStringTokenizer tokenizer(position_command);
    std::string next_token = tokenizer.next_token();
    if (next_token != "startpos")  {
        return;
    }
    board.moves_from_startpos = "";
    next_token = tokenizer.next_token();
    if (next_token != "moves")  {
        return;
    }
    board.moves_from_startpos = tokenizer.get_the_rest();
    trim(board.moves_from_startpos);
}
