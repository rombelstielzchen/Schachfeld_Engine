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
    send_message("id name Schachfeld 0.8");
    send_message("id autor Rombelstielzchen");
}

void CUciProtocol::send_list_of_options() const {
    // None yet
}

void CUciProtocol::send_info(const std::string &information) {
    std::string full_message = "info " + information;
    send_message(full_message);
}

void CUciProtocol::process_message(const std::string &message) {
    string_tokenizer.set_input(message);
    std::string command = string_tokenizer.next_token(); 
    if (command == "go") {
        process_go_command(string_tokenizer);
    } else if (command == "isready") {
        // Our first version is always and immediately ready
        send_message("readyok");
    } else if ((command == "position") || (command == "p")) {
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

void CUciProtocol::process_go_command(CStringTokenizer &string_tokenizer) {
    std::string next_token = string_tokenizer.next_token();
    if (next_token == "infinite") {
        command_interface.go_infinite();
        return;
    } 
    if (next_token == "depth") {
        int  depth = stoi(string_tokenizer.next_token());
        command_interface.go_depth(depth);
        return;
    }
    if (next_token == "nodes") {
        int64_t nodes = stoi(string_tokenizer.next_token());
       command_interface.go_nodes(nodes);
       return;
    }
    if (next_token == "mate") {
        int depth_in_moves = stoi(string_tokenizer.next_token());
        command_interface.go_mate(depth_in_moves);
        return;
    }
    if (next_token == "movetime") {
        uint64_t move_time = stoi(string_tokenizer.next_token());
       command_interface.go_movetime(move_time);
       return;
    }
    if (next_token == "ponder") {
        assert(NOT_YET_IMPLEMENTED);
        return;
    }
    uint64_t white_time_ms = 0;
    uint64_t black_time_ms = 0;
    uint64_t white_increment_ms = 0;
    uint64_t black_incrementt_ms = 0;
    uint64_t moves_to_go = 0;
    while (next_token != "") {
        if (next_token == "wtime") {
            white_time_ms = stoi(string_tokenizer.next_token());
        } else if (next_token == "btime") {
            black_time_ms = stoi(string_tokenizer.next_token());
        } else if (next_token == "winc") {
            white_increment_ms = stoi(string_tokenizer.next_token());
        } else if (next_token == "binc") {
            black_incrementt_ms = stoi(string_tokenizer.next_token());
        } else if (next_token == "movestogo") {
            moves_to_go = stoi(string_tokenizer.next_token());
        }
        next_token = string_tokenizer.next_token();
    }
    command_interface.go_time(white_time_ms, black_time_ms, white_increment_ms, black_incrementt_ms, moves_to_go);
}

void CUciProtocol::message_loop() {
    DEBUG_METHOD();
    while (true) {
        std::string message;
        getline(std::cin, message);
        DEBUG_VALUE_OF(message);
        // Checking the input for an exact match in order to decouple
        // message_loop, string_tokenizer and process_message for better testability
        if  ((message == "quit") || (message == "exit") || (message == "x")) {
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

