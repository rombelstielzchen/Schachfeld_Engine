// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_rooks.h"
#include "../../../board/board_logic.h"


/*#include "../../piece_square_value_tables.h"
#include "../../score_constants.h"
#include "../../../board/board.h"
#include "../../../board/distances.h"
#include "../../../move_generator/move.h"
#include "../../../technical_functions/standard_headers.h"
*/
// Positive boni from whites POV.

typedef char TPiece;

// TODO: move to CGeometry
TFile king_file(TPiece which_king) {
   /// assert()
    TFile result = CBoardLogic::king_square(which_king).file;
    assert(file_in_range(result));
    return result;
}

bool CExpertRooks::is_responsible() const {
     // TODO: colour_in_range
    // TODO: more precise is_responsible()
    return (!CBoardLogic::is_simplified_testcase() && !CBoardLogic::one_king_missing());
}

void CExpertRooks::apply_knowledge() {
    add_to_king_files();
    add_bonus_to_half_open_files();
    add_bonuS_to_pawn_lever_files();
    add_bonus_to_passed_pawn_files();
}

void CExpertRooks::add_to_king_files() {
    // TODO: bonus for whole file or only for the first 4 ranks?
    CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[WHITE_ROOK], king_file(BLACK_KING), 10);
    CPsvModifier::add_bonus_to_file(main_piece_square_value_table_set[BLACK_ROOK], king_file(WHITE_KING), -10);
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
}

