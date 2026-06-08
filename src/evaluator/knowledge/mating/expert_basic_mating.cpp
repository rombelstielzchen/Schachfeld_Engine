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
// But not too high, otherwise the winner would be willing to sacrifice material
// in order to lure the opponent into the corner,
constexpr int bonus_losing_king = 36;
constexpr int bonus_winning_king = 15;
// Standard-tables are nearly OK. except that a knight in the corner is not worth enough,
// leading to stupid losses, if it can lure the enemy into the corner.
// Therefore we raise the value of the knight.
constexpr int precious_knight_score = score_average_rook;

// TODO: move to PSV-modifiers?
int bonus_for(TPlayerColour which_player, int positive_bonus__negative_malus) {
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
    m_winning_side = winning_side();
    m_losing_side = (m_winning_side == WHITE_PLAYER) ? BLACK_PLAYER : WHITE_PLAYER;
    assert(m_winning_side != m_losing_side);
    m_winning_king = (m_winning_side == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    m_losing_king = (m_losing_side == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    assert(m_winning_king != m_losing_king);
    m_winning_queen = (m_winning_side == WHITE_PLAYER) ? WHITE_QUEEN : BLACK_QUEEN;
    m_winning_rook = (m_winning_side == WHITE_PLAYER) ? WHITE_ROOK : BLACK_ROOK;
    m_winning_bishop = (m_winning_side == WHITE_PLAYER) ? WHITE_BISHOP : BLACK_BISHOP;
    m_winning_knight = (m_winning_side == WHITE_PLAYER) ? WHITE_KNIGHT : BLACK_KNIGHT;
    m_winning_king_square = CBoardLogic::king_square(m_winning_side);
    assert(square_in_range(m_winning_king_square));
    m_losing_king_square = CBoardLogic::king_square(m_losing_side);
    assert(square_in_range(m_losing_king_square));
    m_target_corner = desired_mating_corner(m_losing_king_square);
    assert(square_in_range(m_target_corner));
     configure_losing_king_tables();
     configure_winning_king_tables();
     configure_queen_tables();
     configure_rook_tables();
     configure_bishop_tables();
     configure_knight_tables();
     // Nothing to be changed for pawns
}

void CExpertBasicMating::configure_losing_king_tables() {
    TPieceSquareValueTable &losing_king_table = main_piece_square_value_table_set[m_losing_king];
    CPsvModifier::make_equal(losing_king_table, bonus_for(m_losing_side, SCORE_KING));
    CPsvModifier::make_gradient(losing_king_table, m_target_corner, bonus_for(m_winning_side, bonus_losing_king));
}

void CExpertBasicMating::configure_winning_king_tables() {
    // We want the winning king to march towards the loser,
    // but not to the extreme, that we occupy his border-square.
    // Especially in KBNk-endgames we need the winner more centralized.
    constexpr int bonus_extended_center = 99;
    TPieceSquareValueTable &winning_king_table = main_piece_square_value_table_set[m_winning_king];
    CPsvModifier::make_equal(winning_king_table, bonus_for(m_winning_side, SCORE_KING));
    CPsvModifier::make_gradient(winning_king_table, m_losing_king_square, bonus_for(m_winning_side, bonus_winning_king));
    CPsvModifier::add_bonus_to_extended_center(winning_king_table, bonus_for(m_winning_side, bonus_extended_center));
    TSquareList mate_support_squares = {};
    if (m_target_corner == A1) {
        mate_support_squares = { C2, B3 };
    } else if (m_target_corner == H1) {
        mate_support_squares = { F2, G3 };
    } else if (m_target_corner == A8) {
        mate_support_squares = { C7, B6 };
    } else {
        assert(m_target_corner == H8);
        mate_support_squares = { F7, G6 };
    } 
    assert(mate_support_squares.size() == 2);
    constexpr int bonus_mate_support_squares = bonus_extended_center + bonus_winning_king;
    CPsvModifier::add_bonus_to_squares(winning_king_table, mate_support_squares, bonus_for(m_winning_side, bonus_mate_support_squares));
}

void CExpertBasicMating::configure_queen_tables() {
    // The standard tables are nearly good enough, 
    // except high boni for F7 / G7 / H7 / H8 and a malus for B7 / C3
    TPieceSquareValueTable &queen_table = main_piece_square_value_table_set[m_winning_queen];
    CPsvModifier::make_gradient(queen_table, nearest_center_square(m_losing_king_square), bonus_for(m_winning_side, 10));
    const TSquareList good_pre_mating_squares = { D2, E2, B4, B5, D7, E7, G4, G5 };
    constexpr int bonus_mate_support_squares = 15;
    CPsvModifier::add_bonus_to_squares(queen_table, good_pre_mating_squares, bonus_for(m_winning_side, bonus_mate_support_squares));
}

void CExpertBasicMating::configure_rook_tables() {
    if (CBoardLogic::n_pieces_present(m_winning_rook) == 1) {
        configure_rook_tables__single_rook();
    } else {
        configure_rook_tables__multiple_rooks();
    }
}

void CExpertBasicMating::configure_rook_tables__multiple_rooks() {
    TPieceSquareValueTable &rook_table = main_piece_square_value_table_set[m_winning_rook];
    constexpr int vertical_bonus = 5;
    constexpr int horizontal_malus = -15;
    constexpr int bonus_ladder_steps = -horizontal_malus + 1;
    constexpr int central_malus = -50;
    TSquareColour colour_beautiful_ladder_steps = !m_winning_side;
    CPsvModifier::make_equal(rook_table, bonus_for(m_winning_side, score_average_rook));
    CPsvModifier::show_psv_table(m_winning_rook);
    CPsvModifier::make_vertical_gradient(rook_table, m_losing_king_square.rank, bonus_for(m_winning_side, vertical_bonus));
    CPsvModifier::show_psv_table(m_winning_rook);
    CPsvModifier::make_horizontal_gradient(rook_table, m_losing_king_square.file, bonus_for(m_winning_side, horizontal_malus));
    CPsvModifier::show_psv_table(m_winning_rook);
    CPsvModifier::add_bonus_to_colour_complex(rook_table, colour_beautiful_ladder_steps, bonus_for(m_winning_side, bonus_ladder_steps));
    CPsvModifier::show_psv_table(m_winning_rook);
    CPsvModifier::add_bonus_to_area(rook_table, C1, F8, bonus_for(m_winning_side, central_malus));
    CPsvModifier::show_psv_table(m_winning_rook);
}

void CExpertBasicMating::configure_knight_tables() {
    TPieceSquareValueTable &knight_table = main_piece_square_value_table_set[m_winning_knight];
    CPsvModifier::make_equal(knight_table, bonus_for(m_winning_side, precious_knight_score));
    constexpr int center_bonus = 17;
    CPsvModifier::add_bonus_to_extended_center(knight_table, bonus_for(m_winning_side, center_bonus));
    CPsvModifier::add_bonus_to_center(knight_table,  bonus_for(m_winning_side, center_bonus));
    constexpr int border_penalty = -SCORE_HALF_PAWN;
    CPsvModifier::add_bonus_to_border_squares(knight_table, bonus_for(m_winning_side, border_penalty));
    constexpr int corner_penalty = border_penalty;
    CPsvModifier::add_bonus_to_squares(knight_table, CORNER_SQUARES, bonus_for(m_winning_side, corner_penalty));
    // Extra penalty for a knight that is threatend to get trapped.
    // TODO: target-corer might be not the corner that is threatend! fix and test!
    CPsvModifier::add_bonus_to_square(knight_table, m_target_corner, bonus_for(m_winning_side, corner_penalty));
    if (is_bishop_and_knight()) {
        // Knights belong on the bishop-colour in order to control all squares.
        constexpr int colour_bonus = 17;
        CPsvModifier::add_bonus_to_colour_complex(knight_table, CBoardLogic::bishop_colour(), bonus_for(m_winning_side, colour_bonus));
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

void CExpertBasicMating::configure_bishop_tables() {
    TPieceSquareValueTable &bishop_table = main_piece_square_value_table_set[m_winning_bishop];
    assert((bishop_table == main_piece_square_value_table_set[WHITE_BISHOP]) || (bishop_table == main_piece_square_value_table_set[BLACK_BISHOP]));
    CPsvModifier::make_equal(bishop_table, bonus_for(m_winning_side, score_average_bishop));
    // 0) Prioritize king-centralization.
    // this avoids stupid repetitions like Be6-c4-e6.
    // When attacked, move far away,
    if (!CBoardLogic::is_piece_at(m_winning_king, EXTENDED_CENTER_SQUARES) && !short_before_mate()) {
        constexpr int malus_too_close_to_enemy_king = -1;
        CPsvModifier::make_gradient(bishop_table, m_losing_king_square, malus_too_close_to_enemy_king);
        return;
    }
    // 1) Centralization
    constexpr int bonus_central_bishop_per_square = 8;
    CPsvModifier::make_gradient(bishop_table, nearest_center_square(m_losing_king_square), bonus_for(m_winning_side, bonus_central_bishop_per_square));
    // 2) Avoid the kings diagonal. Possible obstructiion and wrong when mating on low depth.
    constexpr int malus_for_bishop_on_kings_diagonal = -2 * bonus_central_bishop_per_square;
    CPsvModifier::add_bonus_to_diagonal(bishop_table, m_winning_king_square, bonus_for(m_winning_side, malus_for_bishop_on_kings_diagonal)); 
    CPsvModifier::add_bonus_to_anti_diagonal(bishop_table, m_winning_king_square, bonus_for(m_winning_side, malus_for_bishop_on_kings_diagonal)); 
    // 3) Encourage final checks on low depth
    if (losing_king_near_target_corner()) {
        constexpr int bonus_final_bishop_checks = 2 * bonus_central_bishop_per_square;
        CPsvModifier::add_bonus_to_diagonal(bishop_table, m_losing_king_square, bonus_for(m_winning_side, bonus_final_bishop_checks));
        CPsvModifier::add_bonus_to_anti_diagonal(bishop_table, m_losing_king_square, bonus_for(m_winning_side, bonus_final_bishop_checks));
    }
    // 4) With a king near the corner. prevent Be6-c4-e6-repetitions.
    // Allow the bishop to a6 / c8 to prevent escape
    if (losing_king_near_target_corner()) {
        TSquareList good_near_corner_squares = {};
        constexpr int near_corner_bonus = 30;
        if (m_target_corner== A1) {
            good_near_corner_squares = { A3, C1 };
        } else if (m_target_corner== A8) {
            good_near_corner_squares = { A6, C8 };
        } else if (m_target_corner== H1) {
            good_near_corner_squares = { F1, H3 };
        } else if (m_target_corner== H8) {
            good_near_corner_squares = { F8, H6 };
        }
        CPsvModifier::add_bonus_to_squares(bishop_table, good_near_corner_squares, bonus_for(m_winning_side, near_corner_bonus));
    }
    assert(m_winning_side == winning_side());
    CPsvModifier::show_psv_table(m_winning_bishop);
}

void CExpertBasicMating::configure_rook_tables__single_rook() {
    constexpr int bonus_rook = 12;
    static_assert(bonus_rook < bonus_winning_king);
    TPieceSquareValueTable &rook_table = main_piece_square_value_table_set[m_winning_rook];
    CPsvModifier::make_equal(rook_table, bonus_for(m_winning_side, score_average_rook));
    SSquare rook_square = CBoardLogic::piece_square(m_winning_rook);
    assert(square_in_range(rook_square));
    if (CDistances::mixed_distance(rook_square, m_winning_king_square) < 3) {
        // Box in the enemy king, if our own king is nearby
        CPsvModifier::make_gradient(rook_table, m_losing_king_square, bonus_for(m_winning_side, bonus_rook));
    } else {
        // Keep some distance to avoid perpetual attacks
            CPsvModifier::make_vertical_gradient(rook_table, m_losing_king_square.rank, bonus_for(m_winning_side, bonus_rook));
            constexpr int horizontal_malus = -7;
            CPsvModifier::make_horizontal_gradient(rook_table, m_losing_king_square.file, bonus_for(m_winning_side, horizontal_malus));
    }
}

SSquare CExpertBasicMating::nearest_center_square(const SSquare s) {
    assert(square_in_range(s));
    return CDistances::nearest_square(s, CENTER_SQUARES);
}

bool CExpertBasicMating::losing_king_near_target_corner() const {
    return (CDistances::mixed_distance(m_losing_king_square, m_target_corner) < 1.1);
}

bool CExpertBasicMating::winning_king_near_losing_king() const {
    // Max: larger than 2 adjacent squares, smaller than 2 diagonal.
    constexpr double max_near_distance = 2.5;
    return (CDistances::mixed_distance(m_winning_king_square, m_losing_king_square) < max_near_distance);
}

bool CExpertBasicMating::short_before_mate() const {
    return (losing_king_near_target_corner() && winning_king_near_losing_king());
}
