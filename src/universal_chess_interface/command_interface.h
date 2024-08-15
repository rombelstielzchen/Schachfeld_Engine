#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#include "../board/board.h"
#include <cstdint>
#include <string>

class CCommandInterface {
  public:
    void new_game();
    bool set_position(const std::string &fen_position);
    void stop();
  public:
    void go_depth(const int64_t depth_in_plies);
    void go_nodes(const int64_t nodes);
    void go_mate(const int64_t depth_in_moves);
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
        const int64_t blacl_increment_milliseconds,
        const int64_t moves_to_go);
  public:
    void go_searchmoves(std::string moves);
  private:
    void send_best_move();
  private:
    CBoard board;
};
