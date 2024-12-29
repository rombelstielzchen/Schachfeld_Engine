// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "fen_parser.h"
#include "move_maker.h"
#include "../move_generator/move_generator.h"
#include "../move_generator/move_list.h"
#include "../technical_functions/string_functions.h"
#include "../technical_functions/string_tokenizer.h"

bool CFenParser::parse(const std::string &fen_board_specification) {
    std::string cleaned_up_specification = fen_board_specification;
    remove_all_substrings(cleaned_up_specification, "[FEN]", true);
    remove_all_substrings(cleaned_up_specification, "[/FEN]", true);
    std::string extra_moves = extract_moves_from_position_command(cleaned_up_specification);
    bool lack_of_errors = true;
    CStringTokenizer tokenizer(cleaned_up_specification);
    std::string piece_placement = tokenizer.next_token();
    if ((piece_placement == "startpos") || (piece_placement == "s")) {
        // UCI may send "startpos" instead of a complicated FEN
        board.set_start_position();
        board.moves_from_startpos = extra_moves;
    } else {
        if ((piece_placement == "fen") || (piece_placement == "f")) {
        // Ignore "fen".  Position commands have this extra token, test-cases not.
        piece_placement = tokenizer.next_token();
        }
        // Standard case: full FEN, consisting of multiple tokens
        lack_of_errors &= parse_piece_placement(piece_placement);
        lack_of_errors &= parse_side_to_move(tokenizer.next_token());
        lack_of_errors &= parse_castling_rights(tokenizer.next_token());
        lack_of_errors &= parse_eng_passeng(tokenizer.next_token());
        lack_of_errors &= parse_100_ply_draw_counter(tokenizer.next_token());
        lack_of_errors &= parse_move_counter(tokenizer.next_token());
        board.moves_from_startpos = "-";
    }
    board.move_maker.reset_history();
    lack_of_errors = board.move_maker.play_variation(extra_moves);
    return lack_of_errors;
}

bool CFenParser::parse_piece_placement(const std::string &partial_input) {
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
    if (partial_input == "w") {
        board.side_to_move = WHITE_PLAYER;
        return true;
    } else if (partial_input == "b") {
        board.side_to_move = BLACK_PLAYER;
        return true;
    }
    // Unexpected character
    return false;
}

bool CFenParser::parse_castling_rights(const std::string &partial_input) {
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
    return true;
}

bool CFenParser::parse_move_counter(const std::string &partial_input) {
    // We use the old atoi instead of stoi, because it doesn't throw exceptions 
    // and returns 0 in case of bad input
    board.move_counter = std::max(1, atoi(partial_input.c_str()));
    return true;
}

std::string CFenParser::extract_moves_from_position_command(const std::string &position_command) {
    std::string result = "";
    CStringTokenizer tokenizer(position_command);
    std::string next_token = tokenizer.next_token();
   while ((next_token != "") && (next_token != "moves") && (next_token != "m")) {
       next_token = tokenizer.next_token();
   }
    result = tokenizer.get_the_rest();
    trim(result);
    return result;
}

