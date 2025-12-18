// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_basic_mating.h"
#include "../../piece_square_value_tables.h"
#include "../../score_constants.h"
#include "../../../board/board_logic.h"
#include "../../../move_generator/move.h"
#include "../../../technical_functions/standard_headers.h"

// TODO: move, better func-signature
int bonus_for(bool which_player, int positive_bonus__negative_malus) {
    if (which_player == WHITE_PLAYER) {
        return positive_bonus__negative_malus;
    }
    return -positive_bonus__negative_malus;
}

bool CExpertBasicMating::is_responsible() const {
    if ((CBoardLogic::n_stones(WHITE_PLAYER) > 1) && (CBoardLogic::n_stones(BLACK_PLAYER) > 1)) {
        return false;
    }
    if (CBoardLogic::n_stones() <= 2) {
        return false;
    }
    if ((CBoardLogic::king_square(WHITE_PLAYER) == NULL_SQUARE) || (CBoardLogic::king_square(BLACK_PLAYER) == NULL_SQUARE)) {
        return false;
    }
    return true;
}

void CExpertBasicMating::apply_knowledge() {
    bool winner = winning_side();
     configure_king_tables(winner);
     configure_queen_tables(winner);
     configure_rook_tables(winner);
     configure_knight_tables(winner);
     // Nothing to be changed for bishops, they are good the way they are.
     // Even less to be done for pawns.
}

SSquare CExpertBasicMating::desired_mating_corner(const SSquare losing_king_square) const {
    // TODO: select corner for mating with bishop and knight
    assert(square_in_range(losing_king_square));
    if ((losing_king_square.file <= FILE_D) && (losing_king_square.rank <= RANK_4)) {
        return A1;
    }
    if (losing_king_square.file <= FILE_D) {
        return A8;
    }
    if (losing_king_square.rank <= RANK_4) {
        return H1;
    }
    return H8;
}

void CExpertBasicMating::configure_king_tables(bool winning_side) {
    char winning_king = WHITE_KING;
    char losing_king = BLACK_KING;
    SSquare losing_king_square = CBoardLogic::king_square(BLACK_PLAYER);
    // Positive boni from whites POV
    // Getting the losing king towards the corner is important; far higher bonus
    int bonus_winning_king = 15;
    // The bonus must be not too high, otherwise the winner is willing to sacrifice material
    // in order to lure the opponent into the corner,
    // 48 is OK, SCORE_HALF_PAWN too much.
    int bonus_losing_king = 48;
    if (winning_side == BLACK_PLAYER) {
        winning_king = BLACK_KING;
        losing_king = WHITE_KING;
        losing_king_square = CBoardLogic::king_square(WHITE_PLAYER);
        // Negative boni from blacks POV
        bonus_winning_king = -bonus_winning_king;
        bonus_losing_king = -bonus_losing_king;
    }
    assert(square_in_range(losing_king_square));
    SSquare target_corner = desired_mating_corner(losing_king_square);
    assert(square_in_range(target_corner));
    CPsvModifier::make_gradient(main_piece_square_value_table_set[losing_king], target_corner, bonus_losing_king);
    CPsvModifier::make_gradient(main_piece_square_value_table_set[winning_king], losing_king_square, bonus_winning_king);
}
void CExpertBasicMating::configure_queen_tables(bool winning_side) {
    // The standard tables are nearly good enough, 
    // except high boni for F7 / G7 / H7 / H8 and a malus for B7
    char winning_queen = (winning_side == WHITE_PLAYER) ? WHITE_QUEEN : BLACK_QUEEN;
    CPsvModifier::make_gradient(main_piece_square_value_table_set[winning_queen], E5, bonus_for(winning_side, 10));
}

void CExpertBasicMating::configure_rook_tables(bool winning_side) {
    // The standard-tables suffer from high boni at the 7th rank.
    // To be replaced by moderate boni on the a-file and h-file,
    //encouraging the rook-"ladder"
    char winning_rook = (winning_side == WHITE_PLAYER) ? WHITE_ROOK : BLACK_ROOK;
    CPsvModifier::make_equal(main_piece_square_value_table_set[winning_rook], bonus_for(winning_side, score_average_rook));
    CPsvModifier::add_bonus_to_area(main_piece_square_value_table_set[winning_rook], A1, A8, bonus_for(winning_rook, 10));
    CPsvModifier::add_bonus_to_area(main_piece_square_value_table_set[winning_rook], H1, H8, bonus_for(winning_rook, 10));
}

void CExpertBasicMating::configure_knight_tables(bool winning_side) {
    // Standard-tables are nearly OK. except that a knight in the corner is not worth enough,
    // leading to stupid losses, if it can lure the enemy into the corner.
    // Therefore we raise the value of the knight.
    char winning_knight = (winning_side == WHITE_PLAYER) ? WHITE_KNIGHT : BLACK_KNIGHT;
    int precious_knight_score = score_average_rook;
    CPsvModifier::make_equal(main_piece_square_value_table_set [winning_knight], precious_knight_score);
    CPsvModifier::make_gradient(main_piece_square_value_table_set[winning_knight],  E5, bonus_for(winning_side, 15));
    int corner_penalty = - SCORE_HALF_PAWN;
    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[winning_knight], A1, bonus_for(winning_side, corner_penalty));
    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[winning_knight], A8, bonus_for(winning_side, corner_penalty));
    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[winning_knight], H1, bonus_for(winning_side, corner_penalty));
    CPsvModifier::add_bonus_to_square(main_piece_square_value_table_set[winning_knight], H8, bonus_for(winning_side, corner_penalty));
}

bool CExpertBasicMating::winning_side() const {
    if (CBoardLogic::n_stones(WHITE_PLAYER) == 1) {
        return BLACK_PLAYER;
    }
    assert(CBoardLogic::n_stones(BLACK_PLAYER) == 1);
    return WHITE_PLAYER;
}

