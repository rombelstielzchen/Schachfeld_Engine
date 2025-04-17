// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_maker.h"
#include "board.h"
#include "board_logic.h"
#include "square_constants.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/string_functions.h"
#include "../technical_functions/string_tokenizer.h"

CMoveMaker::CMoveMaker() {
    reset_history();
}

bool CMoveMaker::make_move(SMove move) {
    assert(move_in_range(move));
    char moving_piece = board.squares[move.source.file][move.source.rank];
    assert(is_any_piece(moving_piece));
    board.clear_square(move.source);
    move.captured_piece = board.get_square(move.target.file, move.target.rank);
    board.put_piece(move.target, moving_piece);
    former_eng_passeng_files.push_back(board.get_eng_passeng_file());
    switch (move.move_type) {
        case MOVE_TYPE_NORMAL:
        case MOVE_TYPE_CAPTURE:
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            break;
        case MOVE_TYPE_DOUBLE_JUMP:
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            board.eng_passeng_file = move.source.file;
            break;
        case MOVE_TYPE_WHITE_SHORT_CASTLING:
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            assert(moving_piece == WHITE_KING);
            board.clear_square(H1);
            board.put_piece(F1, WHITE_ROOK);
            break;
        case MOVE_TYPE_WHITE_LONG_CASTLING:
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            assert(moving_piece == WHITE_KING);
            board.clear_square(A1);
            board.put_piece(D1, WHITE_ROOK);
            break;
        case MOVE_TYPE_BLACK_SHORT_CASTLING:
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            assert(moving_piece == BLACK_KING);
            board.clear_square(H8);
            board.put_piece(F8, BLACK_ROOK);
            break;
        case MOVE_TYPE_BLACK_LONG_CASTLING:
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            assert(moving_piece == BLACK_KING);
            board.clear_square(A8);
            board.put_piece(D8, BLACK_ROOK);
            break;
        case MOVE_TYPE_ENG_PASSENG:
            assert(toupper(moving_piece) == WHITE_POWER);
            // TODO: proper initialization
           SSquare eng_passeng_square;
           eng_passeng_square.file = board.get_eng_passeng_file();
           eng_passeng_square.rank = CBoardLogic::eng_passeng_pawn_rank();
           board.clear_square(eng_passeng_square);
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            break;
        case WHITE_QUEEN:
        case WHITE_KNIGHT:
        case WHITE_ROOK:
        case WHITE_BISHOP:
        case BLACK_QUEEN:
        case BLACK_KNIGHT:
        case BLACK_ROOK:
        case BLACK_BISHOP:
            assert(toupper(moving_piece) == WHITE_POWER);
            board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
            board.put_piece(move.target, move.move_type);
            break;
        default:
            assert(THIS_MUST_NOT_HAPPEN);
            break;
    }
    assert(board.square_is_empty(move.target.file, move.target.rank) == false);
    board.flip_side_to_move();
    move_history.push_back(move);
    return true;
}

void CMoveMaker::make_null_move() {
    board.flip_side_to_move();
    former_eng_passeng_files.push_back(board.get_eng_passeng_file());
    board.eng_passeng_file = NO_ENG_PASSENG_POSSIBLE;
}

bool CMoveMaker::make_move(const std::string &long_algebraic_uci_move) {
    CMoveGenerator move_generator;
    move_generator.generate_all();
    SMove move = move_generator.move_list.lookup_move(long_algebraic_uci_move);
    if (is_null_move(move)) {
            std::cerr << "ERROR: invalid move " << long_algebraic_uci_move << "\n";
        return false;
    }
    return make_move(move);
}

void CMoveMaker::unmake_null_move() {
    board.flip_side_to_move();
    assert(former_eng_passeng_files.size() > 0);
    board.eng_passeng_file = former_eng_passeng_files.back();
    former_eng_passeng_files.pop_back();
}

void CMoveMaker::unmake_move() {
    board.flip_side_to_move();
    assert(former_eng_passeng_files.size() > 0);
    board.eng_passeng_file = former_eng_passeng_files.back();
    former_eng_passeng_files.pop_back();
    assert(move_history.size() > 0);
    SMove move = move_history.back();
    DEBUG_MESSAGE(move_as_text(move));
    move_history.pop_back();
    assert(move_in_range(move));
    char moving_piece = board.get_square(move.target.file, move.target.rank);
    assert(moving_piece != EMPTY_SQUARE);
    assert(is_any_piece(moving_piece));
    board.put_piece(move.target, move.captured_piece);
    switch (move.move_type) {
        case MOVE_TYPE_NORMAL:
        case MOVE_TYPE_CAPTURE:
        case MOVE_TYPE_DOUBLE_JUMP:
            break;
        case MOVE_TYPE_WHITE_SHORT_CASTLING:
            board.clear_square(F1);
            board.put_piece(H1, WHITE_ROOK);
            break;
        case MOVE_TYPE_WHITE_LONG_CASTLING:
            board.clear_square(D1);
            board.put_piece(A1, WHITE_ROOK);
            break;
        case MOVE_TYPE_BLACK_SHORT_CASTLING:
            board.clear_square(F8);
            board.put_piece(H8, BLACK_ROOK);
            break;
        case MOVE_TYPE_BLACK_LONG_CASTLING:
            board.clear_square(D8);
            board.put_piece(A8, BLACK_ROOK);
            break;
        case MOVE_TYPE_ENG_PASSENG:
            {
                char opponent_pawn = (move.target.rank == RANK_6) ? BLACK_POWER : WHITE_POWER;
                board.put_piece(move.target, opponent_pawn);
            }
            break;
        case WHITE_QUEEN:
        case WHITE_KNIGHT:
        case WHITE_ROOK:
        case WHITE_BISHOP:
            moving_piece = WHITE_POWER;
            break;
        case BLACK_QUEEN:
        case BLACK_KNIGHT:
        case BLACK_ROOK:
        case BLACK_BISHOP:
            moving_piece = BLACK_POWER;
            break;
        default:
            assert(THIS_MUST_NOT_HAPPEN);
            break;
    }
    board.put_piece(move.source, moving_piece);
}

void CMoveMaker::unmake_all() {
    while (move_history.size() > 0) {
        unmake_move();
    }
}

bool CMoveMaker::play_variation(const std::string &variation) {
    CStringTokenizer tokenizer(variation);
    std::string next_move = tokenizer.next_token();
    while (next_move != "") {
        if (!make_move(next_move)) {
            return false;
        }
        update_castling_rights(next_move);
        next_move = tokenizer.next_token();
    }
    return true;
}

void CMoveMaker::reset_history() {
    move_history.clear();
    former_eng_passeng_files.clear();
}

void CMoveMaker::update_castling_rights(const std::string &textual_move) const {
    SMove move = text_to_basic_move(textual_move);
    update_castling_rights(move.source);
    update_castling_rights(move.target);
}

void CMoveMaker::update_castling_rights(const SSquare source_or_target_square) const {
   if (source_or_target_square == A1) {
        board.set_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING, false);
    } else if (source_or_target_square == E1) {
        board.set_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING, false);
        board.set_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING, false);
    } else if (source_or_target_square == H1) {
        board.set_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING, false);
    } else if (source_or_target_square == A8) {
        board.set_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING, false);
    } else if (source_or_target_square == E8) {
        board.set_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING, false);
        board.set_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING, false);
    } else if (source_or_target_square == H8) {
        board.set_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING, false);
    }
}

