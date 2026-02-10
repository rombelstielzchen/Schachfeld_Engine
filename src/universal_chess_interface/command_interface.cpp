// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "uci_protocol.h"
#include "../board/board.h"
#include "../board/game_saver.h"
#include "../evaluator/piece_square_value_tables.h"
#include "../move_generator/test_perft.h"
#include "../search/iterative_deepening.h"
#include "../technical_functions/engine_test.h"
#include "../technical_functions/standard_headers.h"
#include "../technical_functions/testing.h"

#ifndef _WIN32
#include <unistd.h>
#endif

int CCommandInterface::n_worker_threads_busy = 0;
std::mutex CCommandInterface::board_ownership;

#define ACQUIRE_BOARD_OWNERSHIP() std::lock_guard<std::mutex> lock(board_ownership)

CCommandInterface::CCommandInterface() {
}

void CCommandInterface::go_depth(const int depth_in_plies) {
    assert(depth_in_plies > 0);
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    std::string book_move = master_book.get_move(board.moves_from_startpos());
    if (book_move != NULL_MOVE_AS_TEXT) {
        send_best_move(book_move);
        return;
    }
    std::thread worker_thread(worker_go_depth, depth_in_plies);
    worker_thread.detach();
}

void CCommandInterface::go_nodes(const int64_t nodes) {
    assert(nodes > 0);
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    std::string book_move = master_book.get_move(board.moves_from_startpos());
    if (book_move != NULL_MOVE_AS_TEXT) {
        send_best_move(book_move);
        return;
    }
    std::thread worker_thread(worker_go_nodes, nodes);
    worker_thread.detach();
}

void CCommandInterface::go_mate(const int depth_in_moves) {
    // ATM we search "normally" with the necessary depth.
    assert(depth_in_moves > 0);
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    int64_t depth_in_plies = 2 * depth_in_moves - 1;
    constexpr int64_t extra_depth_until_king_gets_captured_by_final_quiescence = 1;
    int64_t required_depth_in_plies = depth_in_plies + extra_depth_until_king_gets_captured_by_final_quiescence;
    std::thread worker_thread(worker_go_depth, required_depth_in_plies);
    worker_thread.detach();
}

void CCommandInterface::go_infinite() {
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    std::thread worker_thread(worker_go_depth, INFINITE_DEPTH);
    worker_thread.detach();
}
 
void CCommandInterface::go_ponder() {
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
   assert(NOT_YET_IMPLEMENTED); 
}

void ponder_hit() {
    assert(NOT_YET_IMPLEMENTED);
}
  
void CCommandInterface::go_movetime(const int64_t time_milliseconds) {
    assert(time_milliseconds > 0);
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    std::string book_move = master_book.get_move(board.moves_from_startpos());
    if (book_move != NULL_MOVE_AS_TEXT) {
        send_best_move(book_move);
        return;
    }
    std::thread worker_thread(worker_go_movetime, time_milliseconds);
    worker_thread.detach();
}

void CCommandInterface::go_time(
    const int64_t white_time_milliseconds,
    const int64_t black_time_milliseconds,
    const int64_t white_increment_milliseconds,
    const int64_t black_increment_milliseconds,
    const int64_t moves_to_go) {
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    std::string book_move = master_book.get_move(board.moves_from_startpos());
    if (book_move != NULL_MOVE_AS_TEXT) {
        send_best_move(book_move);
        return;
    }
    assert(white_time_milliseconds >= 0);
    assert(black_time_milliseconds >= 0);
    assert(white_increment_milliseconds >= 0);
    assert(black_increment_milliseconds >= 0);
    assert(moves_to_go >= 0);
    std::thread worker_thread(worker_go_time,
        white_time_milliseconds,
        black_time_milliseconds,
        white_increment_milliseconds,
        black_increment_milliseconds,
        moves_to_go);
    worker_thread.detach();
}

void CCommandInterface::new_game() {
    stop(); 
    assert(n_worker_threads_busy == 0);
    ACQUIRE_BOARD_OWNERSHIP();
    board.game_saver.save_game();
    board.set_start_position();
    master_book.on_new_game();
}

void CCommandInterface::stop() {
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = true;
    // Self-test runs now blocking within the UCI-thread, so ...
    assert(CEngineTest::is_testing() == false);
    ACQUIRE_BOARD_OWNERSHIP();
    assert(n_worker_threads_busy == 0);
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
}

void CCommandInterface::set_position(const std::string &fen_position) {
    // The assertion below indicates bad coordination of self-test and external test
    assert(CEngineTest::is_testing() == false);
    stop();
    assert(n_worker_threads_busy == 0);
    ACQUIRE_BOARD_OWNERSHIP();
    if(board.set_fen_position(fen_position)) {
        std::string confirmation = "new position: " + board.get_fen_position();
        CUciProtocol::send_info(confirmation); 
    } else {
        CUciProtocol:: send_error("invalid position received via UCI");
    }
}

void CCommandInterface::send_best_move(const std::string &best_move){
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = true;
    CUciProtocol::send_best_move(best_move);
}

void CCommandInterface::send_best_move(SMove best_move){
    assert(move_in_range(best_move) || (best_move == NULL_MOVE));
    send_best_move(move_as_text(best_move));
}

void CCommandInterface::worker_go_depth(const int64_t depth_in_plies) {
    assert(n_worker_threads_busy == 0);
    ++n_worker_threads_busy;
    ACQUIRE_BOARD_OWNERSHIP();
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_depth(depth_in_plies);
    send_best_move(calculated_move);
    --n_worker_threads_busy;
}

void CCommandInterface::worker_go_nodes(int64_t nodes) {
    assert(n_worker_threads_busy == 0);
    ++n_worker_threads_busy;
    ACQUIRE_BOARD_OWNERSHIP();
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_nodes(nodes);
    send_best_move(calculated_move);
    --n_worker_threads_busy;
}

void CCommandInterface::worker_go_movetime(int64_t time_milliseconds) {
    assert(n_worker_threads_busy == 0);
    ++n_worker_threads_busy;
    ACQUIRE_BOARD_OWNERSHIP();
    assert(time_milliseconds > 0);
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_movetime(time_milliseconds);
    send_best_move(calculated_move);
    --n_worker_threads_busy;
}

void CCommandInterface::worker_go_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t black_increment_milliseconds,
        const int64_t moves_to_go) {
    assert(n_worker_threads_busy == 0);
    ++n_worker_threads_busy;
    ACQUIRE_BOARD_OWNERSHIP();
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_time(
        white_time_milliseconds,
        black_time_milliseconds,
        white_increment_milliseconds,
        black_increment_milliseconds,
        moves_to_go);
    send_best_move(calculated_move);
    --n_worker_threads_busy;
}

bool CCommandInterface::test_move_generator() {
    stop();
    assert(n_worker_threads_busy == 0);
    ACQUIRE_BOARD_OWNERSHIP();
    EXPECT(CTestPerft::test_extended_depth());
    return true;
}

void CCommandInterface::takeback() {
    if (any_worker_thread_busy()) {
        stop();
        CUciProtocol::send_info("Calculation stopped for takeback");
    }
    assert(n_worker_threads_busy == 0);
    ACQUIRE_BOARD_OWNERSHIP();
    board.move_maker.takeback();
}

void CCommandInterface::on_exit() {
    CUciProtocol::send_info("Confirming quit");
    stop(); 
    CUciProtocol::send_info("calculator-threads stopped");
    assert(n_worker_threads_busy == 0);
    // Potential race condition here.
    // TODO: the last engine-move is not yet stored in the move_history
    board.game_saver.save_game();
    CUciProtocol::send_info("### End Of Session ###########");
}

void CCommandInterface::show_main_psv_tables() {
    CPsvModifier::show_main_psv_tables();
}

