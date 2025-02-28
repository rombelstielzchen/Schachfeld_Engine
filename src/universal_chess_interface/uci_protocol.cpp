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

const std::string ENGINE_ID = "Schachfeld_Engine_0.d";
static_assert('a' > '9');

CUciProtocol::CUciProtocol() {
    // Use std::cerr here; std::cout is reserved for the protocol
    std::cerr << ENGINE_ID << "\n";
    std::cerr << "'help' or '?' for some guidance\n";
}

/* static */ void CUciProtocol::send_message(const std::string &message) {
    // Used by both UCI-thread and calculator-thread, therefore mutex-protected
        std::mutex message_mutex;
        std::lock_guard<std::mutex> lock(message_mutex);
    // UCI standard says:
    //   * communication via text-IO
    //   * every message should end with a new-line, "\n"
    // To be on the safe side. we use endl, which also flushes the buffer.
    // TODO: 2 functions, with and wirhout flush
    std::cout << message << std::endl;
}

void CUciProtocol::identify_engine() const {
        std::string id_message = "id name " + ENGINE_ID;
        send_message(id_message);
    send_message("id autor Rombelstielzchen");
}

void CUciProtocol::send_list_of_options() const {
    send_message("option name UCI_EngineAbout type string default Schachfeld-engine by Rombelstielzchen. Protocol: UCI. Licensed as open-source under GPLv3. Contact:  https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby. Source-code: https://github.com/rombelstielzchen/Schachfeld_Engine");
    // No real options yet
}

void CUciProtocol::send_info(const std::string &information) {
    std::string full_message = "info " + information;
    send_message(full_message);
}

void CUciProtocol::preprocess_message(std::string &message) const {
    trim(message);
    size_t phpbb_fen_pos = message.find("[FEN]");
    if (phpbb_fen_pos == std::string::npos) {
        return;
    }
    if (phpbb_fen_pos == 0) {
        replace_substring(message, "[FEN]", "position fen ", true);
    }
    remove_all_substrings(message, "[FEN]");
    remove_all_substrings(message, "[/FEN]");
}

void CUciProtocol::process_message(const std::string &message) {
    string_tokenizer.set_input(message);
    std::string command = string_tokenizer.next_token(); 
    if ((command == "go") || (command == "g")) {
        process_go_command(string_tokenizer);
    } else if (command == "isready") {
        // Our first version is always and immediately ready
        send_message("readyok");
    } else if ((command == "position") || (command == "p")) {
        std::string fen_position = string_tokenizer.get_the_rest();
        if (!command_interface.set_position(fen_position)) {
            std::cerr << "ERROR: invalid position received via UCI" << std::endl;
        }
    } else if ((command == "stop") || (command == "s")) {
        command_interface.stop();
    } else if (command == "test") {
            CEngineTest::test_everything(); 
    } else if (command == "uci") {
         identify_engine();
         send_list_of_options(); 
         send_message("uciok");
    } else if (command == "ucinewgame") {
        command_interface.new_game();
    } else if ((command == "help") || (command == "?")) {
        display_help();
    } else if (command == "perft") {
        (void)command_interface.test_move_generator();
    } else {
        // "quit" already gets handled by the message_loop().
        // So this is an unknown token. According to the UCI-standard
        // we should try to continue with the rest of the line.
        std::string remaining_message = string_tokenizer.get_the_rest();
        if (remaining_message != "") {
            // One non-empty token got consumed, so the recursion will terminate
            assert(remaining_message.length() < message.length());
            process_message(remaining_message);
        }
    }
}

void CUciProtocol::process_go_command(CStringTokenizer &string_tokenizer) {
    std::string next_token = string_tokenizer.next_token();
    if ((next_token == "infinite") || (next_token == "i") || (next_token == "")) {
        command_interface.go_infinite();
        return;
    } 
    if ((next_token == "depth") || (next_token == "d")) {
        int  depth = string_tokenizer.get_integer_token(1);
        command_interface.go_depth(depth);
        return;
    }
    if ((next_token == "nodes") || (next_token == "n")) {
        int64_t nodes = string_tokenizer.get_integer_token(1);
       command_interface.go_nodes(nodes);
       return;
    }
    if ((next_token == "mate") || (next_token == "m")) {
        int depth_in_moves = string_tokenizer.get_integer_token(1);
        command_interface.go_mate(depth_in_moves);
        return;
    }
    if ((next_token == "movetime") || (next_token == "mt")) {
        uint64_t move_time_ms = string_tokenizer.get_integer_token(1);
       command_interface.go_movetime(move_time_ms);
       return;
    }
    if ((next_token == "ponder") || (next_token == "p")) {
        command_interface.go_ponder();
        return;
    }
    uint64_t white_time_ms = 0;
    uint64_t black_time_ms = 0;
    uint64_t white_increment_ms = 0;
    uint64_t black_incrementt_ms = 0;
    uint64_t moves_to_go = 0;
    while (next_token != "") {
        if (next_token == "wtime") {
            white_time_ms = string_tokenizer.get_integer_token(1);
        } else if (next_token == "btime") {
            black_time_ms = string_tokenizer.get_integer_token(1);
        } else if (next_token == "winc") {
            white_increment_ms = string_tokenizer.get_integer_token(1);
        } else if (next_token == "binc") {
            black_incrementt_ms = string_tokenizer.get_integer_token(1);
        } else if (next_token == "movestogo") {
            moves_to_go = string_tokenizer.get_integer_token(1);
        } else {
            std::cerr << "ERROR: unexpected tokeen in go-command\n";
            return;
        }
        next_token = string_tokenizer.next_token();
    }
    command_interface.go_time(white_time_ms, black_time_ms, white_increment_ms, black_incrementt_ms, moves_to_go);
}

void CUciProtocol::message_loop() {
    while (true) {
        std::string message;
        getline(std::cin, message);
        preprocess_message(message);
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

void CUciProtocol::display_help() const {
    send_message("This chess-engine is meant to be used with any modern graphical user-interface,");
    send_message("communicating via the UCI protocol.");
    send_message("If you are curious, you might try the command-line:");
    send_message("    * 'position startpos moves g2g4' or 'p s m g2g4'");
    send_message("    * Alternatively: 'position fen ....'");
    send_message("    * 'go depth 7' or 'g d 7' to search");
    send_message("    * 'go movetime 20000' or ' g mt 20000'");
    send_message("    * 'go infinite' or 'go' or 'g'");
    send_message("    * 'stop' to force a move");
    send_message("    * 'test' for the self-test");
    send_message("    * 'perft' for a looong test of the move_generator");
    send_message("    * 'quit' or 'x'to terminate");
}

