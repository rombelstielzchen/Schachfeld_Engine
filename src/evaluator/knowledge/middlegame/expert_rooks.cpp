// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_rooks.h"
#include "../../../board/board.h"
#include "../../../board/board_geometry.h"
#include "../../../board/board_logic.h"
#include "../../../board/distances.h"
#include "../../scores.h"
#include "../../../move_generator/move.h"
#include "../../../technical_functions/standard_headers.h"

typedef char TPiece;

// TODO: move to CGeometry)
TFile king_file(TPiece which_king) {
    assert((which_king == WHITE_KING) || (which_king == BLACK_KING));
    SSquare const location = CBoardLogic::king_square(which_king);
    if (!square_in_range(location)) {
        return FILE_GARDEN_FENCE_LEFT_1;
    }
    assert(board.get_square(location) == which_king);
    TFile result = location.file;
    assert(file_in_range(result));
    return result;
}

bool CExpertRooks::is_responsible() const {
     // TODO: colour_in_range
    // TODO: more precise is_responsible()
    return (!CBoardLogic::is_simplified_testcase() && !CBoardLogic::one_king_missing());
}

void CExpertRooks::apply_knowledge() {
    add_bonus_to_king_files();
    add_bonus_to_half_open_files();
    add_bonuS_to_pawn_lever_files();
    add_bonus_to_passed_pawn_files();
    add_micro_bonus_to_open_files();
}

void CExpertRooks::add_bonus_to_king_files() {
    // TODO: bonus for whole file or only for the first 4 ranks?
    constexpr int bonus_king_file = 11;
    constexpr int bonus_neighbour_file = bonus_king_file * 2 / 3;
    static_assert(bonus_neighbour_file > 0);
    TFile const black_king_file = king_file(BLACK_KING);
    if (!file_in_range(black_king_file)) {
        return;
    }
    CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[WHITE_ROOK], black_king_file, bonus_king_file);
    TFile neighbour_file = CBoardGeometry::excentric_neighbour_file(black_king_file);
    if (file_in_range(neighbour_file)) {
        CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[WHITE_ROOK], neighbour_file, bonus_neighbour_file);
    }
    TFile const white_king_file = king_file(WHITE_KING);
    CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[BLACK_ROOK], white_king_file, bonus_king_file);
     neighbour_file = CBoardGeometry::excentric_neighbour_file(white_king_file);
    if (file_in_range(neighbour_file)) {
        CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[BLACK_ROOK], neighbour_file, bonus_neighbour_file);
    }
}

void CExpertRooks::add_bonus_to_half_open_files() {
    constexpr int bonus_half_open_file = 11;
    for (const TFile f: ALL_FILES) {
        if (CBoardLogic::is_half_open_file(f, WHITE_PLAYER)) {
            assert(!CBoardLogic::is_half_open_file(f, BLACK_PLAYER));
            CPsvModifier::add_bonus_to_file(psv_white_rook, f, bonus_half_open_file);
        } else if (CBoardLogic::is_half_open_file(f, BLACK_PLAYER)) {
            CPsvModifier::add_bonus_to_file(psv_black_rook, f, -bonus_half_open_file);
        }
    }
}

void CExpertRooks::add_bonuS_to_pawn_lever_files() {
}

void CExpertRooks::add_bonus_to_passed_pawn_files() {
    // TODO: expert_pawn_endgame: bonus for enemy king near pawn
    // TODO: bonus for king cutoff higher than bonus for rook behind pawn, test
    for (const SSquare s: ALL_SQUARES) {
        // TODO: avoid double boni for doubled pawns, but both W and B can have passers on the same file!       
        if (!CBoardLogic::is_passed_pawn(s)) {
            continue;
        }
        char pawn = board.get_square(s);
        assert((pawn == WHITE_POWER) || (pawn == BLACK_POWER));
        // TODO: bonus only for squares behind the pawn, remove bonus for 7th and 8th rank 
        char supporting_rook = (pawn == WHITE_POWER) ? WHITE_ROOK : BLACK_ROOK;
        CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[supporting_rook], s.file, 11);
    }
}

void CExpertRooks::add_micro_bonus_to_open_files() {
    constexpr int micro_bonus = 3;
    for (const TFile f: ALL_FILES) {
        if (CBoardLogic::is_open_file(f)) {
            CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[WHITE_ROOK], f, micro_bonus);
            CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[BLACK_ROOK], f, micro_bonus);
        }
    }
}

