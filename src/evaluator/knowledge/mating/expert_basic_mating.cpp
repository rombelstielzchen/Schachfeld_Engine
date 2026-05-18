// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_basic_mating.h"
#include "../../piece_square_value_tables.h"
#include "../../score_constants.h"
#include "../../../board/board_logic.h"
#include "../../../board/distances.h"
#include "../../../move_generator/move.h"
#include "../../../technical_functions/standard_headers.h"

// Positive boni from whites POV.
// Getting the losing king towards the corner is most important; far higher bonus.
// But not too high, otherwise the winner is willing to sacrifice material
// in order to lure the opponent into the corner,
// 48 is OK, SCORE_HALF_PAWN already too much.
constexpr int bonus_losing_king = 48;
constexpr int bonus_winning_king = 15;
// Standard-tables are nearly OK. except that a knight in the corner is not worth enough,
// leading to stupid losses, if it can lure the enemy into the corner.
// Therefore we raise the value of the knight.
constexpr int precious_knight_score = score_average_rook;

// TODO: move, better func-signature
int bonus_for(bool which_player, int positive_bonus__negative_malus) {
    if (which_player == WHITE_PLAYER) {
        return positive_bonus__negative_malus;
    }
    assert(which_player == BLACK_PLAYER);
    return -positive_bonus__negative_malus;
}

bool CExpertBasicMating::is_responsible() const {
    // TODO: disable for pawn-endgames! test!
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
    TPlayerColour winner = winning_side();
    char winning_king = (winner == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    TPlayerColour losing_side = !winner;
    char losing_king = (losing_side == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    assert(winning_king != losing_king);
    SSquare losing_king_square = CBoardLogic::king_square(losing_side);
    assert(square_in_range(losing_king_square));
    SSquare target_corner = desired_mating_corner(losing_king_square);
    assert(square_in_range(target_corner));
     configure_king_tables(winner, target_corner);
     configure_queen_tables(winner);
     configure_rook_tables(winner, target_corner);
     configure_bishop_tables(winner);
     configure_knight_tables(winner, target_corner);
     // Nothing to be changed for pawns
}

void CExpertBasicMating::configure_king_tables(TPlayerColour winning_side, const SSquare target_corner) {
    // TODO: s this cloned code? make it class-members?
    TPlayerColour losing_side = !winning_side;
    char winning_king = (winning_side == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    char losing_king = (losing_side == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    assert(winning_king != losing_king);
    SSquare losing_king_square = CBoardLogic::king_square(losing_side);
    assert(square_in_range(losing_king_square));
    TPieceSquareValueTable &losing_king_table = main_piece_square_value_table_set[losing_king];
    CPsvModifier::make_equal(losing_king_table, bonus_for(losing_side, SCORE_KING));
    CPsvModifier::make_gradient(main_piece_square_value_table_set[losing_king], target_corner, bonus_for(winning_side, bonus_losing_king));
    TPieceSquareValueTable &winning_king_table = main_piece_square_value_table_set[winning_king];
    CPsvModifier::make_equal(winning_king_table, bonus_for(winning_side, SCORE_KING));
    CPsvModifier::make_gradient(winning_king_table, losing_king_square, bonus_for(winning_side, bonus_winning_king));
    // We want the winning king to march towards the loser,
    // but not to the extreme, that we occupy his border-square.
    // Especially in KBNk-endgames we need the winner more centralized.
    // TODO: bonus too high? especially with a trapped knihgt?
    constexpr int bonus_extended_center = 99;
    CPsvModifier::add_bonus_to_extended_center(winning_king_table, bonus_for(winning_side, bonus_extended_center));
    TSquareList mate_support_squares = {};
    if (target_corner == A1) {
        mate_support_squares = { C2, B3 };
    } else if (target_corner == H1) {
        mate_support_squares = { F2, G3 };
    } else if (target_corner == A8) {
        mate_support_squares = { C7, B6 };
    } else {
        assert(target_corner == H8);
        mate_support_squares = { F7, G6 };
    } 
    assert(mate_support_squares.size() == 2);
    constexpr int bonus_mate_support_squares = bonus_extended_center + bonus_winning_king;
    CPsvModifier::add_bonus_to_squares(winning_king_table, mate_support_squares, bonus_for(winning_side, bonus_mate_support_squares));
}

void CExpertBasicMating::configure_queen_tables(TPlayerColour winning_side) {
    // The standard tables are nearly good enough, 
    // except high boni for F7 / G7 / H7 / H8 and a malus for B7 / C3
    char winning_queen = (winning_side == WHITE_PLAYER) ? WHITE_QUEEN : BLACK_QUEEN;
    TPieceSquareValueTable &queen_table = main_piece_square_value_table_set[winning_queen];
    CPsvModifier::make_gradient(queen_table, E5, bonus_for(winning_side, 10));
    const TSquareList good_pre_mating_squares = { D2, E2, B4, B5, D7, E7, G4, G5 };
    constexpr int bonus_mate_support_squares = 15;
    CPsvModifier::add_bonus_to_squares(queen_table, good_pre_mating_squares, bonus_for(winning_side, bonus_mate_support_squares));
}

void CExpertBasicMating::configure_rook_tables(TPlayerColour winning_side, const SSquare target_square) {
    char winning_rook = (winning_side == WHITE_PLAYER) ? WHITE_ROOK : BLACK_ROOK;
    if (CBoardLogic::n_pieces_present(winning_rook) == 1) {
        configure_rook_tables__single_rook(winning_side, target_square);
        return; //!!!
    } else {
    }
    // The standard-tables suffer from high boni at the 7th rank.
    // To be replaced by moderate boni on the a-file and h-file,
    // encouraging the rook-"ladder"
    TPieceSquareValueTable &rook_table = main_piece_square_value_table_set[winning_rook];
    CPsvModifier::make_equal(rook_table, bonus_for(winning_side, score_average_rook));
    constexpr int flank_bonus = 10;
    CPsvModifier::add_bonus_to_area(rook_table, A1, A8, bonus_for(winning_side, flank_bonus));
    CPsvModifier::add_bonus_to_area(rook_table, H1, H8, bonus_for(winning_side, flank_bonus));
}

void CExpertBasicMating::configure_knight_tables(TPlayerColour winning_side, const SSquare target_corner) {
    char winning_knight = (winning_side == WHITE_PLAYER) ? WHITE_KNIGHT : BLACK_KNIGHT;
    TPieceSquareValueTable &knight_table = main_piece_square_value_table_set[winning_knight];
    CPsvModifier::make_equal(knight_table, bonus_for(winning_side, precious_knight_score));
    constexpr int center_bonus = 17;
    CPsvModifier::add_bonus_to_extended_center(knight_table,  bonus_for(winning_side, center_bonus));
    CPsvModifier::add_bonus_to_center(knight_table,  bonus_for(winning_side, center_bonus));
    constexpr int border_penalty = -SCORE_HALF_PAWN;
    CPsvModifier::add_bonus_to_border_squares(knight_table, bonus_for(winning_side, border_penalty));
    constexpr int corner_penalty = border_penalty;
    CPsvModifier::add_bonus_to_squares(knight_table, CORNER_SQUARES, bonus_for(winning_side, corner_penalty));
    // Extra penalty for a knight that is threatend to get trapped.
    // TODO: target-corer might be not the corner that is threatend! fix and test!
    CPsvModifier::add_bonus_to_square(knight_table, target_corner, bonus_for(winning_side, corner_penalty));
    if (is_bishop_and_knight()) {
        // Knights belong on the bishop-colour in order to control all squares.
        constexpr int colour_bonus = 17;
        CPsvModifier::add_bonus_to_colour_complex(knight_table, CBoardLogic::bishop_colour(), bonus_for(winning_side, colour_bonus));
    }
}

bool CExpertBasicMating::winning_side() const {
    if (CBoardLogic::n_stones(WHITE_PLAYER) == 1) {
        assert(CBoardLogic::n_stones(BLACK_PLAYER) > 1);
        return BLACK_PLAYER;
    }
    assert(CBoardLogic::n_stones(BLACK_PLAYER) == 1);
    return WHITE_PLAYER;
}

bool CExpertBasicMating::is_bishop_and_knight() const {
    if (CBoardLogic::is_piece_present(WHITE_BISHOP) && CBoardLogic::is_piece_present(WHITE_KNIGHT)) {
        assert(CBoardLogic::n_stones(BLACK_PLAYER) == 1);
        return true;
    }
    if (CBoardLogic::is_piece_present(BLACK_BISHOP) && CBoardLogic::is_piece_present(BLACK_KNIGHT)) {
        assert(CBoardLogic::n_stones(WHITE_PLAYER) == 1);
        return true;
    }
    return false;
}

SSquare CExpertBasicMating::desired_mating_corner_for_bishop_and_knight(const SSquare losing_king_square) const {
    assert(square_in_range(losing_king_square));
    assert(is_bishop_and_knight());
    TSquareColour corner_colour = CBoardLogic::bishop_colour();
    SSquare target_corner = NULL_SQUARE;
    if (corner_colour == WHITE_SQUARE_COLOUR) {
        target_corner = CDistances::nearest_square(losing_king_square, WHITE_CORNER_SQUARES);
    } else {
        target_corner = CDistances::nearest_square(losing_king_square, BLACK_CORNER_SQUARES);
    }
    assert(square_in_range(target_corner));
    return target_corner;
}

SSquare CExpertBasicMating::desired_mating_corner(const SSquare losing_king_square) const {
    assert(square_in_range(losing_king_square));
    if (is_bishop_and_knight()) {
        return desired_mating_corner_for_bishop_and_knight(losing_king_square);
    }
    SSquare mating_corner = CDistances::nearest_square(losing_king_square, CORNER_SQUARES);
    assert(square_in_range(mating_corner));
    return mating_corner;
    ;
}

void CExpertBasicMating::configure_bishop_tables([[maybe_unused]]TPlayerColour winning_side) {
     // TODO: improve or remove
///    char winning_bishop = (winning_side == WHITE_PLAYER) ? WHITE_BISHOP : BLACK_BISHOP;
///    TPieceSquareValueTable &bishop_table = main_piece_square_value_table_set[winning_bishop];
///    assert((bishop_table == main_piece_square_value_table_set[WHITE_BISHOP]) || (bishop_table == main_piece_square_value_table_set[BLACK_BISHOP]));
    // 1) Centralization
///    constexpr int bonus_central_bishop_per_square = 10;
///    CPsvModifier::make_gradient(bishop_table, E5, bonus_for(winning_side, bonus_central_bishop_per_square));
    // 2) Avoid the kings diagonal. Possible obstructiion and wrong when mating on low depth.
///    constexpr int malus_for_bishop_on_kings_diagonal = -2 * bonus_central_bishop_per_square;
///    SSquare winning_king_square = CBoardLogic::king_square(winning_side);
///    CPsvModifier::add_bonus_to_diagonal(bishop_table, winning_king_square, bonus_for(winning_side, malus_for_bishop_on_kings_diagonal)); 
///    CPsvModifier::add_bonus_to_anti_diagonal(bishop_table, winning_king_square, bonus_for(winning_side, malus_for_bishop_on_kings_diagonal)); 
}

void CExpertBasicMating::configure_rook_tables__single_rook(TPlayerColour winning_side, const SSquare target_square) {
    assert(player_colour_in_range(winning_side));
    assert(!is_any_piece(winning_side));
    assert(square_in_range(target_square));
    char winning_rook = (winning_side == WHITE_PLAYER) ? WHITE_ROOK : BLACK_ROOK;
    TPlayerColour losing_side = !winning_side;
    SSquare losing_king_square = CBoardLogic::king_square(losing_side);
    assert(square_in_range(losing_king_square));
    std::cerr << "losing_king_square: " << losing_king_square << "\n";
    // Strategy for a single rook: box in the enemy king
    constexpr int bonus_rook = 12;
    static_assert(bonus_rook < bonus_winning_king);
    TPieceSquareValueTable &rook_table = main_piece_square_value_table_set[winning_rook];
    CPsvModifier::make_equal(rook_table, bonus_for(winning_side, score_average_rook));
    CPsvModifier::make_gradient(rook_table, losing_king_square, bonus_for(winning_side, bonus_rook));
    CPsvModifier::show_psv_table(winning_rook);///!!!
}

