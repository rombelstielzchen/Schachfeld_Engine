// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "universal_chess_interface/uci_protocol.h"
#include "technical_functions/standard_headers.h"

static_assert(INTPTR_MAX >= INT64_MAX, "64-bit technology required");

int main() {
    srand(static_cast<int>(time(NULL)));
    board.set_start_position();
    board.clone_to_global_reference_board();
    CUciProtocol uci_protocol;
    uci_protocol.message_loop();
     return EXIT_SUCCESS;
}

