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
#include <unistd.h>

int CCommandInterface::n_worker_threads_busy = 0;

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
    board.game_saver.save_game();
    board.set_start_position();
    master_book.on_new_game();
}

void CCommandInterface::stop() {
    if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop == true) {
        return;
    }
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = true;
    do {
        // We do first sleep, then check the condition,
        // in case we only want to self-test before quit.
        std::this_thread::sleep_for(std::chrono::milliseconds(1234));
    } while (CEngineTest::is_testing());
    constexpr int deci_seconds_to_wait_for_calculator_thread = 30;
    for (int j = 0; j < deci_seconds_to_wait_for_calculator_thread; ++j) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop == false) {
            break;
        }
    }
    assert(n_worker_threads_busy == 0);
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
}

void CCommandInterface::set_position(const std::string &fen_position) {
    // The assertion below indicates bad coordination of self-test and external test
    assert(CEngineTest::is_testing() == false);
    stop();
    assert(n_worker_threads_busy == 0);
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
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_depth(depth_in_plies);
    send_best_move(calculated_move);
    --n_worker_threads_busy;
}

void CCommandInterface::worker_go_nodes(int64_t nodes) {
    assert(n_worker_threads_busy == 0);
    ++n_worker_threads_busy;
    CIterativeDeepening searcher;
    SMove calculated_move = searcher.search_nodes(nodes);
    send_best_move(calculated_move);
    --n_worker_threads_busy;
}

void CCommandInterface::worker_go_movetime(int64_t time_milliseconds) {
    assert(n_worker_threads_busy == 0);
    ++n_worker_threads_busy;
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
    EXPECT(CTestPerft::test_extended_depth());
    return true;
}

void CCommandInterface::takeback() {
    if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop == false) {
        CUciProtocol::send_error("Can not take back while calculating");
        return;
    }
    assert(n_worker_threads_busy == 0);
    board.move_maker.takeback();
}

void CCommandInterface::on_exit() {
    CUciProtocol::send_info("Confirming quit");
    stop(); 
    std::cerr << "stopped\n";
    assert(n_worker_threads_busy == 0);
    // Potential race condition here.
    // If we quit in the middle of a calculation, the last engine-move will not be saved, most probably
    board.game_saver.save_game();
    CUciProtocol::send_info("\n### End Of Session ###########\n");
    flush(std::cout);
    flush(std::cerr);
}

void CCommandInterface::show_main_psv_tables() {
    CPsvModifier::show_main_psv_tables();
}

