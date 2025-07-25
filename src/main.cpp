// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "technical_functions/engine_test.h"
#include "universal_chess_interface/uci_protocol.h"
#include "technical_functions/standard_headers.h"

static_assert(INTPTR_MAX == INT64_MAX, "64-bit technology required: parameter-passing of small structs; hash-table-entries in the future");

int main() {
    //DEBUG_LOAG_TO_FILE();
    // HERE time_t -> int
    srand(time(NULL));
#ifndef NDEBUG
    if (CEngineTest::test_everything() == false) {
        return EXIT_FAILURE;
    }
#endif
    CUciProtocol uci_protocol;
    uci_protocol.message_loop();
     return EXIT_SUCCESS;
}

