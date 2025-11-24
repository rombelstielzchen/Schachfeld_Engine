// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "virtual_expert.h"
#include "../../universal_chess_interface/uci_protocol.h"
#include "../../technical_functions/debug_log.h"
#include "../../technical_functions/standard_headers.h"

CVirtualExpert::~CVirtualExpert() {
}

void CVirtualExpert::configure() {
    bool responsible = is_responsible();
    if (responsible) {
        apply_knowledge();
    }
#ifndef NDEBUG
    std::string message = get_name();
    message += responsible ? "" : " not";
    message += " responsible";
    CUciProtocol::send_info(message);
#endif
}

