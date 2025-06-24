#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "command_interface.h"
#include "../technical_functions/string_functions.h"
#include "../technical_functions/string_tokenizer.h"

class CUciProtocol {
  public:
    CUciProtocol();
  public:
    void message_loop();
    static void send_message(const std::string &message);
    static void send_info(const std::string &information);
    static void send_error(const std::string &error_message);
    static void send_best_move(const std::string best_move);
  private:
    void identify_engine() const;
    void send_list_of_options() const;
    void preprocess_message(std::string &message) const;
    void process_message(const std::string &message);
    void process_go_command(CStringTokenizer &string_tokenizer);
    void process_option(CStringTokenizer &string_tokenizer);
    void process_unknown_token_potential_move(const std::string &token);
    void dynamic_sleep(const std::string &last_message) const;
    void display_help() const;
    static void display_board();
  private:
    CCommandInterface command_interface;
    CStringTokenizer string_tokenizer;
    static bool interactive_console_mode;
};

