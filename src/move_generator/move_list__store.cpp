// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "../board/board.h"
#include "../evaluator/evaluator.h"

// Rough estimates for move-ordering: Q > N > R > B
// We rate N higher as R here, as underpromotions to a knight are more likely,
constexpr int potential_gain_queen_promotion = 900;
constexpr int potential_gain_knight_promotion = 401;
constexpr int potential_gain_rook_promotion = 400;
constexpr int potential_gain_bishop_promotion = 200;
constexpr int potential_gain_eng_passeng = 100;

void CMoveList::store_silent_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = move_type;
    new_move.potential_gain = 0;
    assert(move_in_range(new_move));
    assert(is_silent_move(new_move));
    store_silent_move(new_move);
    assert(valid_list());
}

void CMoveList::store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    if (target_rank == RANK_8) {
        // TODO: remove_superfluous parameters
        store_white_promotions(source_file, RANK_7, target_file, RANK_8);
    } else if (target_rank == RANK_1) {
        store_black_promotions(source_file, RANK_2, target_file, RANK_1);
    } else if (source_file != target_file) {
        store_capture(source_file, source_rank, target_file, target_rank);
    } else { 
        store_silent_move(source_file, source_rank, target_file, target_rank);
    }
    assert(valid_list());
}

void CMoveList::store_capture(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = MOVE_TYPE_CAPTURE;
    new_move.potential_gain = abs(board.evaluator.evaluate_square(new_move.target));
    assert(new_move.potential_gain > 0);
    store_capture(new_move);
    assert(valid_list());
}

void CMoveList::store_pawn_capture(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    if (target_rank == RANK_8) {
        store_white_promotions(source_file, source_rank, target_file, target_rank);
    } else if (target_rank == RANK_1) {
        store_black_promotions(source_file, source_rank, target_file, target_rank);
    } else {
        store_capture(source_file, source_rank, target_file, target_rank);
    }
    assert(valid_list());
}

void CMoveList::store_eng_passeng(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = MOVE_TYPE_ENG_PASSENG;
    // Do not evaluate the empty target-square to estimate the gain
    new_move.potential_gain = potential_gain_eng_passeng; 
    store_capture(new_move);
    assert(valid_list());
}

void CMoveList::store_white_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    // Promotions in the order of likelihood.
    // Promotions get treated as "captures", they chamge the material balance
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    // TODO: reverse order!
    new_move.move_type = WHITE_QUEEN;
    new_move.potential_gain = potential_gain_queen_promotion;
    store_capture(new_move);
    new_move.move_type = WHITE_KNIGHT;
    new_move.potential_gain = potential_gain_knight_promotion;
    store_capture(new_move);
    new_move.move_type = WHITE_ROOK;
    new_move.potential_gain = potential_gain_rook_promotion;
    store_capture(new_move);
    new_move.move_type = WHITE_BISHOP;
    new_move.potential_gain = potential_gain_bishop_promotion;
    store_capture(new_move);
    assert(valid_list());
}

void CMoveList::store_black_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    // TODO: reverse order
    new_move.move_type = BLACK_QUEEN;
    new_move.potential_gain = potential_gain_queen_promotion;
    store_capture(new_move);
    new_move.move_type = BLACK_KNIGHT;
    new_move.potential_gain = potential_gain_knight_promotion;
    store_capture(new_move);
    new_move.move_type = BLACK_ROOK;
    new_move.potential_gain = potential_gain_rook_promotion;
    store_capture(new_move);
    new_move.move_type = BLACK_BISHOP;
    new_move.potential_gain = potential_gain_bishop_promotion;
    store_capture(new_move);
    assert(valid_list());
}

void CMoveList::store_silent_move(const SMove &move) {
    assert(is_silent_move(move));
    bidirectional_move_list[next_empty_slot] = move; 
    ++next_empty_slot;
   assert(next_empty_slot < LIST_SIZE);
    assert(valid_list());
}

void CMoveList::store_capture(const SMove &move) {
    assert(move.potential_gain > 0);
    // If this assertion fails, then we need to adjust MAX_CAPTURES_IN_CHESS_POSITION
    assert(first_capture > 0);
    assert(valid_list());
    --first_capture;
    --consumer_position;
    bidirectional_move_list[first_capture] = move;
    assert(valid_list_origin());
 }

void CMoveList::store_castling(const char move_type) {
    SMove new_move;
    new_move.source.file = FILE_E;
    new_move.move_type = move_type;
    new_move.potential_gain = 30;
    switch (move_type) {
        case MOVE_TYPE_WHITE_LONG_CASTLING:
            new_move.source.rank = RANK_1;
            new_move.target.file = FILE_C;
            new_move.target.rank = RANK_1;
            break;
        case MOVE_TYPE_WHITE_SHORT_CASTLING:
            new_move.source.rank = RANK_1;
            new_move.target.file = FILE_G;
            new_move.target.rank = RANK_1;
            break;
        case MOVE_TYPE_BLACK_LONG_CASTLING:
            new_move.source.rank = RANK_8;
            new_move.target.file = FILE_C;
            new_move.target.rank = RANK_8;
            break;
        case MOVE_TYPE_BLACK_SHORT_CASTLING:
            new_move.source.rank = RANK_8;
            new_move.target.file = FILE_G;
            new_move.target.rank = RANK_8;
            break;
        default:
            constexpr bool invalid_move_type = false;
            assert(invalid_move_type);
            break;
    }
    store_silent_move(new_move);
    assert(valid_list());
}

