#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "../technical_functions/string_functions.h"

class CUciProtocol {
  public:
    void message_loop();
    static void send_message(const std::string &message);
  private:
    void identify_engine() const;
    void send_list_of_options() const;
    void process_message(const std::string &message);
  private:
    CCommandInterface command_interface;
    CStringTokenizer string_tokenizer;
};

