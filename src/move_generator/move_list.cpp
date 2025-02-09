// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "move_generator.h"
#include "../board/board.h"
#include "../board/board_logic.h"
#include "../board/square_constants.h"

constexpr unsigned int NOT_FOUND = INT_MAX;

bool square_attacked_by_side_to_move(const SSquare square) {
       CMoveGenerator response_generator;
       response_generator.generate_all();
        response_generator.move_list.prune_silent_moves();
        response_generator.move_list.filter_captures_by_target_square(square);
    return (response_generator.move_list.list_size() > 0);
}

bool square_attacked_by_side_not_to_move(const SSquare square) {
    board.move_maker.make_null_move();
    bool result = square_attacked_by_side_to_move(square);
    board.move_maker.unmake_null_move();
    return result;
}

CMoveList::CMoveList() {
    clear();
}

void CMoveList::clear() {
    first_capture = LIST_ORIGIN;
    last_silent_move = LIST_ORIGIN;
    consumer_position = LIST_ORIGIN;
    assert(list_size() == 0);
}

SMove CMoveList::get_random() const {
    if (list_size() <= 0) {
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for an early proof of concept
    unsigned int index = first_capture + rand() % list_size();
    assert(index >= first_capture);
    assert(index < last_silent_move);
    return bidirectional_move_list[index];
}

SMove CMoveList::get_next() {
    assert(consumer_position >= first_capture);
    if (consumer_position >= last_silent_move) {
        return NULL_MOVE;
    }
    SMove result = bidirectional_move_list[consumer_position];
    ++consumer_position;
    assert(move_in_range(result));
    return result;
}

unsigned int CMoveList::get_index(const SMove basic_move) const {
    assert(move_in_range(basic_move));
    assert(last_silent_move >= first_capture);
    for (unsigned int j = first_capture; j < last_silent_move; ++j) {
        if (move_coords_are_equal(basic_move, bidirectional_move_list[j])) {
            return j;
        }
    }
    return NOT_FOUND;
}

SMove CMoveList::lookup_move(const std::string &text_move) const {
     SMove basic_move = text_to_basic_move(text_move);
     if (basic_move == NULL_MOVE) {
         return NULL_MOVE;
     }
     // TODO: make this paer of text_to_basic_move
    assert(basic_move.move_type == MOVE_TYPE_NORMAL);
    if (text_move.length() > 4) {
        basic_move.move_type = text_move[4];
        assert(is_any_piece(basic_move.move_type));
    }
    unsigned int index = get_index(basic_move);
    if (index == NOT_FOUND) {
        return NULL_MOVE;
    }
    assert(index >= 0);
    assert(index <  LIST_SIZE);
    return bidirectional_move_list[index];
}

int CMoveList::list_size() const {
    assert(last_silent_move >= first_capture);
    return (last_silent_move - first_capture);
}

void CMoveList::store_silent_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = move_type;
    store_silent_move(new_move);
}

void CMoveList::store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    if (target_rank == RANK_8) {
        store_white_promotions(source_file, RANK_7, target_file, RANK_8);
    } else if (target_rank == RANK_1) {
        store_black_promotions(source_file, RANK_2, target_file, RANK_1);
    } else if (source_file != target_file) {
        store_capture(source_file, source_rank, target_file, target_rank);
    } else { 
        store_silent_move(source_file, source_rank, target_file, target_rank);
    }
}

void CMoveList::store_capture(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = MOVE_TYPE_CAPTURE;
    store_capture(new_move);
}

void CMoveList::store_pawn_capture(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    if (target_rank == RANK_8) {
        store_white_promotions(source_file, source_rank, target_file, target_rank);
    } else if (target_rank == RANK_1) {
        store_black_promotions(source_file, source_rank, target_file, target_rank);
    } else {
        store_capture(source_file, source_rank, target_file, target_rank);
    }
}

void CMoveList::store_eng_passeng(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = MOVE_TYPE_ENG_PASSENG;
    store_capture(new_move);
}

void CMoveList::store_white_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    // Promotions in the order of likelihood.
    // Promotions get treated as "captures", they chamge the material balance
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = WHITE_QUEEN;
    store_capture(new_move);
    new_move.move_type = WHITE_KNIGHT;
    store_capture(new_move);
    new_move.move_type = WHITE_ROOK;
    store_capture(new_move);
    new_move.move_type = WHITE_BISHOP;
    store_capture(new_move);
}

void CMoveList::store_black_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    new_move.move_type = BLACK_QUEEN;
    store_capture(new_move);
    new_move.move_type = BLACK_KNIGHT;
    store_capture(new_move);
    new_move.move_type = BLACK_ROOK;
    store_capture(new_move);
    new_move.move_type = BLACK_BISHOP;
    store_capture(new_move);
}

void CMoveList::store_silent_move(const SMove &move) {
    bidirectional_move_list[last_silent_move] = move; 
    ++last_silent_move;
   assert(last_silent_move < LIST_SIZE);
}

void CMoveList::store_capture(const SMove &move) {
    assert(first_capture > 0);
    assert(consumer_position >= first_capture);
    --first_capture;
    --consumer_position;
    bidirectional_move_list[first_capture] = move;
 }

void CMoveList::prune_silent_moves() {
    assert(first_capture <= LIST_ORIGIN);
    assert(last_silent_move >= LIST_ORIGIN);
    last_silent_move = LIST_ORIGIN;
}

void CMoveList::prune_illegal_moves() {
    bool my_colour = board.get_side_to_move();
    SMove move = get_next();
    while (move != NULL_MOVE) {
        board.move_maker.make_move(move);
        SSquare my_king_square = CBoardLogic::king_square(my_colour);
        if (square_attacked_by_side_to_move(my_king_square)) {
            SMove illegal_move = move;
            remove(illegal_move);
        }
        board.move_maker.unmake_move();
        move = get_next();
    }
    prune_illegal_castlings();
    reuse_list();
}

void CMoveList::store_castling(const char move_type) {
    SMove new_move;
    new_move.source.file = FILE_E;
    new_move.move_type = move_type;
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
    }
    store_silent_move(new_move);
}

void CMoveList::filter_captures_by_target_square(const SSquare &target_square) {
    prune_silent_moves();
    for (unsigned int j = first_capture; j < LIST_ORIGIN; ++j) {
        SMove move = bidirectional_move_list[j];
        if ((move.target.file == target_square.file) && (move.target.rank == target_square.rank)) {
            store_silent_move(move);
        }
    }
    first_capture = LIST_ORIGIN;
}

SMove CMoveList::get_least_valuable_aggressor() const {
    int least_value = INT_MAX;
    SMove best_move = NULL_MOVE;
    for (unsigned int j = first_capture; j < last_silent_move; ++j) {
        int piece_value = abs(board.evaluator.evaluate_square(bidirectional_move_list[j].source));
        if (piece_value < least_value) {
            least_value = piece_value;
            best_move = bidirectional_move_list[j];
        }
    }
    return best_move;
}

void CMoveList::reuse_list() {
     assert(consumer_position >= first_capture);
    consumer_position = first_capture;
}

void CMoveList::shift_current_move_to_top() {
    unsigned int former_consumer_position = consumer_position - 1;
    assert(former_consumer_position >= first_capture);
    assert(former_consumer_position < last_silent_move);
    SMove new_top_move = bidirectional_move_list[former_consumer_position];
    unsigned int secomd_position = first_capture + 1;
    for (unsigned int j = former_consumer_position; j >= secomd_position; --j) {
       bidirectional_move_list[j] = bidirectional_move_list[j - 1];;
    }
    bidirectional_move_list[first_capture] = new_top_move;
}

std::string CMoveList::as_text() const {
    std::string info ="move_list (" + std::to_string(list_size()) + "): ";
    for (int j = 0; j < list_size(); ++j) {
        int index = first_capture + j;
        info +=move_as_text(bidirectional_move_list[index]);
        info += " ";
    }
    return info;
}

void CMoveList::remove(const SMove move) {
    unsigned int position = get_index(move);
    if (position == NOT_FOUND) {
        return;
    }
    assert(position >= first_capture);
    assert(position < last_silent_move);
    if (position < LIST_ORIGIN) {
        bidirectional_move_list[position] = bidirectional_move_list[first_capture];
        ++first_capture;
    } else {
        bidirectional_move_list[position] = bidirectional_move_list[last_index()];
        --last_silent_move;
        consumer_position = position;
    }
}

void CMoveList::remove(const std::string &move_text) {
    SMove move = text_to_basic_move(move_text);
    remove(move);
}

bool CMoveList::move_on_list(const std::string &text_move) const {
    SMove move = text_to_basic_move(text_move);
    return (get_index(move) != NOT_FOUND);
}

void CMoveList::prune_illegal_castlings() {
    // TODO: refactoring
    SSquare king_square = CBoardLogic::king_square(board.get_side_to_move());
    if (king_square.file != FILE_E) {
        return;
    }
    if (king_square.rank != CBoardLogic::my_back_rank()) {
        return;
    }
    if (board.get_side_to_move() == WHITE_PLAYER) {
        if (!move_on_list("e1f1") && move_on_list("e1g1")) {
            remove("e1g1");
        }
        if (!move_on_list("e1d1") && move_on_list("e1c1")) {
            remove("e1c1");
        }
        if (square_attacked_by_side_not_to_move(king_square)) {
            remove("e1g1");
            remove("e1c1");
        }
        return;
    }
    if (!move_on_list("e8f8") && move_on_list("e8g8")) {
        remove("e8g8");
    }
    if (!move_on_list("e8d8") && move_on_list("e8c8")) {
        remove("e8c8");
    }
        if (square_attacked_by_side_not_to_move(king_square)) {
            remove("e8g8");
            remove("e8c8");
        }
}

