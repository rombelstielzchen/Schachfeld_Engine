// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "uci_protocol.h"
#include "../board/board.h"
#include "../opening_book/opening_book.h"
#include "../search/search.h"
#include "../technical_functions/standard_headers.h"

CCommandInterface::CCommandInterface() {
}


void CCommandInterface::go_depth(const int64_t depth_in_plies) {
//    std::thread worker_thread(worker_go_depth, depth_in_plies);
    std::thread worker_thread(worker_go_depth, 7);
    worker_thread.detach();
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
}

void CCommandInterface::stop() {
    go_depth(42);
    //assert(NOT_YET_IMPLEMENTED);
}

bool CCommandInterface::set_position(const std::string &fen_position) {
    return board.set_fen_position(fen_position);
}

void CCommandInterface::send_best_move(const std::string &best_move){
    std::string message = "bestmove " + best_move;
    CUciProtocol::send_message(message);
}

void CCommandInterface::send_best_move(SMove best_move){
    send_best_move(move_as_text(best_move));
}

void CCommandInterface::worker_go_depth(const int64_t depth_in_plies) {
  // TODO
    // Temp tinkering
    COpeningBook opening_book;
    std::string book_move = opening_book.get_move(board.get_moves_from_startpos());
    if (book_move != NULL_MOVE_AS_TEXT) {
        assert(move_in_range(text_to_basic_move(book_move)));
        send_best_move(book_move);
        return;
    }
    CSearch searcher;
    SMove calculated_move = searcher.search(depth_in_plies);
    assert(move_in_range(calculated_move));
    send_best_move(calculated_move);
}

