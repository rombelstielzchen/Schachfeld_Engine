#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby/page3

#include <string>

class CUciProtocol {
   public:
    void message_loop();
   private:
    void send_message(const std::string message);
    void identify_engine();
    void send_list_of_options();
    void send_best_move();
    void process_message(const std::string message);
};
