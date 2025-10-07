#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../board/board.h"
#include "../move_generator/move.h"
#include "../opening_book/master_book.h"
#include "../technical_functions/standard_headers.h"

class CCommandInterface {
    friend class CUciProtocol;
  public:
    CCommandInterface();
  public:
    void new_game();
    void on_exit();
    bool set_position(const std::string &fen_position);
    void stop();
  public:
    void go_depth(const int depth_in_plies);
    void go_nodes(const int64_t nodes);
    void go_mate(const int depth_in_moves);
    void go_infinite();
  public:
    void go_ponder();
    void ponder_hit();
  public:
    void go_movetime(const int64_t time_milliseconds);
    void go_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t black_increment_milliseconds,
        const int64_t moves_to_go);
  public:
    void go_searchmoves(std::string &moves);
    void takeback();
  public:
    bool test_move_generator();
    void show_main_psv_tables();
  private:
    static void send_best_move(const std::string &best_move);
    static void send_best_move(SMove best_move);
  private:
    // Worker-functions, to be run in extra-threads
    static void worker_go_depth(const int64_t depth_in_plies);
    static void worker_go_nodes(int64_t nodes);
    static void worker_go_movetime(int64_t time_milliseconds);
    static void worker_go_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t blacl_increment_milliseconds,
        const int64_t moves_to_go);
  private:
    CMasterBook master_book;
};

inline volatile bool DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = true;

