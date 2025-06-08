// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "info_thread.h"
#include "command_interface.h"
#include "uci_protocol.h"
#include "../technical_functions/standard_headers.h"

CInfoThread::CInfoThread() {
    std::thread info_thread(thread_function);
    info_thread.detach();
}

void CInfoThread::thread_function() {
    while (true) {
        constexpr int one_second_1000_ms = 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(one_second_1000_ms));
        if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop == false) {
                CUciProtocol::send_message("huhu");
        }
    }
}

