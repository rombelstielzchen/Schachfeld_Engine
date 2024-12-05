#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "../technical_functions/string_functions.h"

class CUciProtocol {
  public:
    CUciProtocol();
  public:
    void message_loop();
    static void send_message(const std::string &message);
    static void send_info(const std::string &information);
  private:
    void identify_engine() const;
    void send_list_of_options() const;
    void process_message(const std::string &message);
    void process_go_command(CStringTokenizer &string_tokenizer);
    void dynamic_sleep(const std::string &last_message) const;
  private:
    CCommandInterface command_interface;
    CStringTokenizer string_tokenizer;
};

