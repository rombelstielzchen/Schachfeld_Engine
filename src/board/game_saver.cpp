// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "game_saver.h"
#include "board.h"
#include "move_maker.h"
#include "../universal_chess_interface/uci_protocol.h"

CGameSaver::CGameSaver() {
}

CGameSaver::~CGameSaver() {
}

void CGameSaver::save_game() {
    if (open_pgn_file()) {
        append_pgn_header();
        append_moves();
        append_line_of_text("");
        close_pgn_file();
    } else {
        CUciProtocol::send_error("Inable to open PGN-file for writing");
    }
}

bool CGameSaver::open_pgn_file() {
    const std::string file_append_mode = "a";
    pgn_file = std::fopen(pgn_filename().c_str(), file_append_mode.c_str()); 
    return (pgn_file != nullptr);
}

void CGameSaver::close_pgn_file() {
    assert(pgn_file != nullptr);
    std::fclose(pgn_file);
    pgn_file = nullptr;
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
    // TODO: FEN, if game was not fom startpos
}

void CGameSaver::append_moves() {
    std::cout << board.move_maker.moves_from_initial_position() << "\n";
}

void CGameSaver::append_line_of_text(const std::string &text) {
    assert(pgn_file != nullptr);
    int total_length = text.length() + 1;
    std::fwrite(text.c_str(), total_length, 1, pgn_file);
    std::fwrite("\n", 2, 1, pgn_file);
}

std::string CGameSaver::pgn_filename() {
    return "schachfeld_games.pgn";
}

void CGameSaver::append_pgn_tag(const std::string &name, const std::string value) {
    std::string full_line = std::string("[") + name + " \"" + value + "\"]";
    append_line_of_text(full_line);
}

