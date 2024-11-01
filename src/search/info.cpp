// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "info.h"
#include "../universal_chess_interface/uci_protocol.h"

CInfo::CInfo() {
    clear_all();
}

void CInfo::clear_all() {
}

void CInfo::set_best_move(const std::string &best_move, const int score) {
    std::string info = "bestmove " + best_move + " score " + std::to_string(score);
    CUciProtocol::send_info(info);
}

void CInfo::set_depth(const int depth) {
    std::string info = "depth " + std::to_string(depth);
    CUciProtocol::send_info(info);
}

void CInfo::set_current_move(const std::string &current_move) {
    std::string info = "currmove " + current_move;
    CUciProtocol::send_info(info);
}


