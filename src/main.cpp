// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "universal_chess_interface/uci_protocol.h"

#include <iostream>
#include <fstream>

int main() {
    std::ofstream ofs("debug.txt");
    DEBUG_SET_STREAM(&ofs);
    srand(time(NULL));
    CUciProtocol uci_protocol;
    uci_protocol.message_loop();
     return EXIT_SUCCESS;
}

