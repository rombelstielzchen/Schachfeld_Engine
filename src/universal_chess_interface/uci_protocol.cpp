// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Universal Chess Interface Protocol
// https://gist.github.com/DOBRO/2592c6dad754ba67e6dcaec8c90165bf

#include "uci_protocol.h"
#include "command_interface.h"
#include "../technical_functions/engine_test.h"
#include "../technical_functions/standard_headers.h"

CUciProtocol::CUciProtocol() {
}

/* static */ void CUciProtocol::send_message(const std::string &message) {
    // Used by both UCI-thread and calculator-thread, therefore mutex-protected
        std::mutex message_mutex;
        std::lock_guard<std::mutex> lock(message_mutex);
    // UCI standard says:
    //   * communication via text-IO
    //   * every message should end with a new-line, "\n"
    // To be on the safe side. we use endl, which also flushes the buffer.
    std::cout << message << std::endl;
}

void CUciProtocol::identify_engine() const {
    send_message("id name Schachfeld 0.6");
    send_message("id author Rombelstielzchen");
}

void CUciProtocol::send_list_of_options() const {
    // None yet
}

void CUciProtocol::process_message(const std::string &message) {
    string_tokenizer.set_input(message);
    std::string command = string_tokenizer.next_token(); 
    if (command == "go") {
        // TODO: parse the many options of "go", all in the same line
        command_interface.go_infinite();
    } else if (command == "isready") {
        // Our first version is always and immediately ready
        send_message("readyok");
    } else if (command == "position") {
        std::string fen_position = string_tokenizer.get_the_rest();
        if (!command_interface.set_position(fen_position)) {
            std::cerr << "ERROR: invalid position received via UCI" << std::endl;
        }
    } else if (command == "stop") {
        command_interface.stop();
    } else if (command == "test") {
            CEngineTest::test_everything(); 
    } else if (command == "uci") {
         identify_engine();
         send_list_of_options(); 
         send_message("uciok");
    } else if (command == "ucinewgame") {
        command_interface.new_game();
    } else {
        // "quit" already gets handled by the message_loop().
        // So this is an unknown token. According to the UCI-standard
        // we should try to continue with the rest of the line.
        std::string command_candidate = string_tokenizer.next_token();
        if (command_candidate != "") {
            // One non-empty token got consumed, so the recursion will terminate
            process_message(command_candidate);
        }
    }
}

void CUciProtocol::message_loop() {
    DEBUG_METHOD();
    while (true) {
        std::string message;
        getline(std::cin, message);
        DEBUG_VALUE_OF(message);
        // Checking the input for an exact match in order to decpuple
        // message_loop, string_tokenizer and process_message for better testability
        if  (message == "quit") {
            break;
        }
        process_message(message);
        dynamic_sleep(message);
    }
}

void CUciProtocol::dynamic_sleep(const std::string &last_message) const {
    static int delay_in_ms = 0;
    constexpr int max_delay = 500;
    constexpr int delta_delay = 50;
    delay_in_ms += (last_message != "") ? delta_delay : 0;
    delay_in_ms = std::min(delay_in_ms, max_delay);
    delay_in_ms = (last_message != "") ? delay_in_ms : 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_in_ms));
}

