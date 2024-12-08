// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "uci_protocol.h"
#include "../board/board.h"
#include "../search/iterative_deepening.h"
#include "../technical_functions/standard_headers.h"

constexpr int64_t INFINITE_DEPTH = INT_MAX;

CCommandInterface::CCommandInterface() {
}

void CCommandInterface::go_depth(const int depth_in_plies) {
    // Temp tinkering
    std::string book_move = opening_book.get_move(board.get_moves_from_startpos());
    if (book_move != NULL_MOVE_AS_TEXT) {
        send_best_move(book_move);
        return;
    }
    assert(depth_in_plies > 0);
    std::thread worker_thread(worker_go_depth, depth_in_plies);
    worker_thread.detach();
}

void CCommandInterface::go_nodes(const int64_t nodes) {
    assert(nodes > 0);
    std::thread worker_thread(worker_go_nodes, nodes);
    worker_thread.detach();
}

void CCommandInterface::go_mate(const int depth_in_moves) {
    // ATM we search "normally" with the necessary depth.
    // TODO: special mate-search 
    assert(depth_in_moves > 0);
    int64_t depth_in_plies = 2 * depth_in_moves - 1;
    constexpr int64_t extra_depth_until_king_gets_captured = 2;
    int64_t required_depth_in_plies = depth_in_plies + extra_depth_until_king_gets_captured;
    go_depth(required_depth_in_plies);
}

void CCommandInterface::go_infinite() {
    go_depth(INFINITE_DEPTH);
}
 
void CCommandInterface::go_ponder() {
    // Assume the "best" opponents move while it s his turn, then calculate.
    // TODO
}

void ponder_hit() {
    assert(NOT_YET_IMPLEMENTED);
}
  
void CCommandInterface::go_movetime(const int64_t time_milliseconds) {
    assert(time_milliseconds > 0);
    std::thread worker_thread(worker_go_movetime, time_milliseconds);
    worker_thread.detach();
}

void CCommandInterface::go_time(
    const int64_t white_time_milliseconds,
    const int64_t black_time_milliseconds,
    const int64_t white_increment_milliseconds,
    const int64_t blacl_increment_milliseconds,
    const int64_t moves_to_go) {
    assert(white_time_milliseconds >= 0);
    assert(black_time_milliseconds >= 0);
    assert(white_increment_milliseconds >= 0);
    assert(blacl_increment_milliseconds >= 0);
    assert(moves_to_go >= 0);
    std::thread worker_thread(worker_go_time,
        white_time_milliseconds,
        black_time_milliseconds,
        white_increment_milliseconds,
        blacl_increment_milliseconds,
        moves_to_go);
    worker_thread.detach();
}

void CCommandInterface::new_game() {
    // TODO
}

void CCommandInterface::stop() {
   // TODO 
}

bool CCommandInterface::set_position(const std::string &fen_position) {
    return board.set_fen_position(fen_position);
}

void CCommandInterface::send_best_move(const std::string &best_move){
    std::string message = "bestmove " + best_move;
    CUciProtocol::send_message(message);
}

void CCommandInterface::send_best_move(SMove best_move){
    assert(move_in_range(best_move) || (best_move == NULL_MOVE));
    send_best_move(move_as_text(best_move));
}

void CCommandInterface::worker_go_depth(const int64_t depth_in_plies) {
  // TODO
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search(depth_in_plies);
    send_best_move(calculated_move);
}

void CCommandInterface::worker_go_nodes(int64_t nodes) {
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_nodes(nodes);
    send_best_move(calculated_move);
}

void CCommandInterface::worker_go_movetime(int64_t time_milliseconds) {
    assert(time_milliseconds > 0);
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_movetime(time_milliseconds);
    send_best_move(calculated_move);
}

void CCommandInterface::worker_go_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t blacl_increment_milliseconds,
        const int64_t moves_to_go) {
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_time(
        white_time_milliseconds,
        black_time_milliseconds,
        white_increment_milliseconds,
        blacl_increment_milliseconds,
        moves_to_go);
    send_best_move(calculated_move);
}

