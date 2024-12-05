// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "technical_functions/engine_test.h"
#include "universal_chess_interface/uci_protocol.h"
#include "technical_functions/standard_headers.h"

int main() {
    DEBUG_LOG_TO_FILE();
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

