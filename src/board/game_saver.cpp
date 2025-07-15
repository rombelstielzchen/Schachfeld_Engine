// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "game_saver.h"

CGameSaver::CGameSaver() {
}

void CGameSaver::save_game() {
}

void CGameSaver::open_pgn_file() {
}

void CGameSaver::close_pgn_file() {
}

void CGameSaver::append_PGN_header() {
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
}

void CGameSaver::append_line_of_text(const std::string &text) {
    std::cerr << text << "\n";
}

std::string CGameSaver::pgn_filename() {
}

void CGameSaver::append_pgn_tag(const std::string &name, const std::string value) {
    std::string full_line = std::string("[") + name + " \"" + value + "\"]";
    append_line_of_text(full_line);
}

