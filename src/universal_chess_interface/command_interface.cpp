// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "uci_protocol.h"
#include "../board/board.h"
#include "../move_generator/move_generator.h"
#include "../opening_book/opening_book.h"
#include "../technical_functions/standard_headers.h"

const std::string NO_MOVES_FROM_STARTPOS = "You better calculate, buddy!";

CCommandInterface::CCommandInterface() {
    moves_from_startpos = "";
}

SMove CCommandInterface::best_move() const {
  // TODO
    // Temp tinkering
    COpeningBook opening_book;
    std::string book_move = opening_book.get_move(moves_from_startpos);
    if (book_move != NULL_MOVE_AS_TEXT) {
        assert(move_in_range(text_to_move(book_move)));
        return text_to_move(book_move);
    }
    CMoveGenerator move_generator;
    move_generator.generate_all();
    SMove random_move = move_generator.get_random();
    return random_move;
}

void CCommandInterface::go_depth(const int64_t depth_in_plies) {
  send_best_move(best_move());
}

void CCommandInterface::go_nodes(const int64_t nodes) {
    assert(NOT_YET_IMPLEMENTED);
}

void CCommandInterface::go_mate(const int64_t depth_in_moves) {
    // ATM we search "normally" with the necessary depth.
    // TODO: special mate-search 
    int64_t depth_in_plies = 2 * depth_in_moves + 1;
    constexpr int64_t extra_depth_until_king_gets_captured = 2;
    int64_t required_depth_in_plies = depth_in_plies + extra_depth_until_king_gets_captured;
    go_depth(required_depth_in_plies);
}

void CCommandInterface::go_infinite() {
    go_depth(INT64_MAX);
}
 
void CCommandInterface::go_ponder() {
    // Assume the "best" opponents move while it s his turn, then calculate.
    // TODO
    go_infinite();
}

void ponder_hit() {
    assert(NOT_YET_IMPLEMENTED);
}
  
void CCommandInterface::go_movetime(const int64_t time_milliseconds) {
    assert(NOT_YET_IMPLEMENTED);
}

void CCommandInterface::go_time(
    const int64_t white_time_milliseconds,
    const int64_t black_time_milliseconds,
    const int64_t white_increment_milliseconds,
    const int64_t blacl_increment_milliseconds,
    const int64_t moves_to_go) {
    assert(NOT_YET_IMPLEMENTED);
}

void CCommandInterface::new_game() {
    // TODO
    moves_from_startpos = NO_MOVES_FROM_STARTPOS;
}

void CCommandInterface::stop() {
    go_depth(42);
    //assert(NOT_YET_IMPLEMENTED);
}

bool CCommandInterface::set_position(const std::string &fen_position) {
    extract_moves_from_startpos(fen_position);
    return board.set_fen_position(fen_position);
}

void CCommandInterface::send_best_move(SMove best_move) const {
    std::string message = "bestmove " + move_as_text(best_move);
    CUciProtocol::send_message(message);
}

void CCommandInterface::extract_moves_from_startpos(const std::string &position_command) {
    moves_from_startpos = NO_MOVES_FROM_STARTPOS;
    CStringTokenizer tokenizer(position_command);
    std::string next_token = tokenizer.next_token();
    if (next_token != "startpos")  {
        return;
    }
    next_token = tokenizer.next_token();
    if (next_token != "moves")  {
        return;
    }
    moves_from_startpos = tokenizer.get_the_rest();
    trim(moves_from_startpos);
}
