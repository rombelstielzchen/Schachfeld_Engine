// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "game_saver.h"
#include "board.h"
#include "move_maker.h"

CGameSaver::CGameSaver() {
}

CGameSaver::~CGameSaver() {
    save_game();
}

void CGameSaver::save_game() {
    open_pgn_file();
    append_pgn_header();
    append_moves();
    close_pgn_file();
}

void CGameSaver::open_pgn_file() {
}

void CGameSaver::close_pgn_file() {
}

void CGameSaver::append_pgn_header() {
    // Mandatory PGN-tags, most info not known
    append_pgn_tag("Event", "FIDE Waldmeisterschaft of Universe");
    append_pgn_tag("Site", "Milkyway");
    append_pgn_tag("Date", "TODO");
    append_pgn_tag("Round", "?");
    append_pgn_tag("White", "White");
    append_pgn_tag("Black", "Black");
    append_pgn_tag("Result", "*");
}

void CGameSaver::append_moves() {
    std::cout << board.move_maker.moves_from_initial_position() << "\n";
}

void CGameSaver::append_line_of_text(const std::string &text) {
    std::cerr << text << "\n";
}

std::string CGameSaver::pgn_filename() {
    return "";
}

void CGameSaver::append_pgn_tag(const std::string &name, const std::string value) {
    std::string full_line = std::string("[") + name + " \"" + value + "\"]";
    append_line_of_text(full_line);
}

