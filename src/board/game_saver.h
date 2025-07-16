#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CGameSaver {
  public:
    CGameSaver();
    ~CGameSaver();
  public:
    void save_game();
  private:
    bool open_pgn_file();
    void close_pgn_file();
    void append_pgn_header();
    void append_moves();
  private:
    void append_pgn_tag(const std::string &name, const std::string value);
    void append_line_of_text(const std::string &text);
    std::string pgn_filename();
  private:
    FILE *pgn_file;
};

