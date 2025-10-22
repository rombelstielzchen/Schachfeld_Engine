// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Universal Chess Interface Protocol
// https://gist.github.com/DOBRO/2592c6dad754ba67e6dcaec8c90165bf

#include "uci_protocol.h"
#include "command_interface.h"
#include "info_thread.h"
#include "../technical_functions/engine_test.h"
#include "../technical_functions/standard_headers.h"

const std::string ENGINE_ID = "Schachfeld_Engine_0.m";
static_assert('a' > '9');

bool CUciProtocol::interactive_console_mode = false;

CUciProtocol::CUciProtocol() {
    // Use std::cerr here; std::cout is reserved for the protocol
    std::cerr << ENGINE_ID << "\n";
    std::cerr << "'help' or '?' for some guidance\n";
    // Init the one and only info_thread immediately for convenience
    CInfoThread info_thread;
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
        std::string id_message = "id name " + ENGINE_ID;
        send_message(id_message);
    send_message("id autor Rombelstielzchen");
}

void CUciProtocol::send_list_of_options() const {
	send_message(std::string("option name book type combo ")
        + "default solid_mix "
        + "var broad_GM "
        + "var tabijas "
        + "var wonder_weapons"
        + "var solid_mix");
    send_message(std::string("option name UCI_EngineAbout type string ")
        + "default Schachfeld-engine by Rombelstielzchen. "
        + "Protocol: UCI. "
        + "Licensed as open-source under GPLv3. "
        + "Contact:  https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby "
        + "Source-code: https://github.com/rombelstielzchen/Schachfeld_Engine");
    // Options for the future
    send_message(std::string("option name hash type spin ")
        + "default 1 "
        + "min 1 "
        + "max " + std::to_string(INT16_MAX) + " ");
    send_message(std::string("option name UCI_LimitStrength type check ")
         + "default false ");
    send_message(std::string("option name UCI_Elo type spin ")
        + "default 3456 "
        + "min 1 "
        + "max 3456 ");
}

void CUciProtocol::send_info(const std::string &information) {
    std::string full_message = "info " + information;
    send_message(full_message);
}

void CUciProtocol::send_error(const std::string &error_message) {
    std::string full_message = "error: " + error_message + "\n";
    std::cerr << full_message;
}

void CUciProtocol::send_best_move(const std::string best_move) {
    if (interactive_console_mode) {
        display_board();
    }
    std::string message = "bestmove " + best_move;
    send_message(message);
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
    if (message == "") {
        return;
    }
    string_tokenizer.set_input(message);
    if (string_tokenizer.next_token_is_one_of("back", "b")) {
        interactive_console_mode = true;
       command_interface.takeback(); 
    } else if (string_tokenizer.next_token_is_one_of("go", "g")) {
        process_go_command(string_tokenizer);
    } else if (string_tokenizer.next_token_is_one_of("help", "?")) {
        interactive_console_mode = true;
        display_help();
    } else if (string_tokenizer.next_token_is("isready")) {
        // Our first version is always and immediately ready
        send_message("readyok");
    } else if (string_tokenizer.next_token_is("perft")) {
        interactive_console_mode = true;
        (void)command_interface.test_move_generator();
    } else if (string_tokenizer.next_token_is("psv")) {
        command_interface.show_main_psv_tables();  
    } else if (string_tokenizer.next_token_is_one_of("position", "p")) {
        std::string fen_position = string_tokenizer.get_the_rest();
        if (!command_interface.set_position(fen_position)) {
            send_error("invalid position received via UCI");
        }
    } else if (string_tokenizer.next_token_is_one_of("setoption", "so")) {
        process_option(string_tokenizer);
    } else if (string_tokenizer.next_token_is_one_of("stop", "s")) {
        command_interface.stop();
    } else if (string_tokenizer.next_token_is("test")) {
        interactive_console_mode = true;
        CEngineTest::test_everything(); 
    } else if (string_tokenizer.next_token_is("uci")) {
         identify_engine();
         send_list_of_options(); 
         send_message("uciok");
    } else if (string_tokenizer.next_token_is_one_of("ucinewgame", "ng")) {
        command_interface.new_game();
    } else {
        std::string next_token = string_tokenizer.next_token();
        process_unknown_token_potential_move(next_token);
        // UCI specification says: continue gracefully
        std::string remaining_message = string_tokenizer.get_the_rest();
        if (remaining_message != "") {
            // One non-empty token got consumed, so the recursion will terminate
            assert(remaining_message.length() < message.length());
            process_message(remaining_message);
        }
    }
}

void CUciProtocol::process_unknown_token_potential_move(const std::string &token) {
    // Try to execute a move.
    // No error-handling needed, as make_move() will care about that.
    if (board.move_maker.make_move(token)) {
        interactive_console_mode = true;
    }
}

void CUciProtocol::process_go_command(CStringTokenizer &string_tokenizer) {
    if (string_tokenizer.next_token_is_one_of("infinite", "i", "")) {
        command_interface.go_infinite();
        return;
    } 
    if (string_tokenizer.next_token_is_one_of("depth", "d")) {
        int depth = static_cast<int>(string_tokenizer.get_integer_token(1));
        command_interface.go_depth(depth);
        return;
    }
    if (string_tokenizer.next_token_is_one_of("nodes", "n")) {
        int64_t nodes = string_tokenizer.get_integer_token(1);
       command_interface.go_nodes(nodes);
       return;
    }
    if (string_tokenizer.next_token_is_one_of("mate", "m")) {
        int depth_in_moves = string_tokenizer.get_integer_token(1);
        command_interface.go_mate(depth_in_moves);
        return;
    }
    if (string_tokenizer.next_token_is_one_of("movetime", "mt")) {
        uint64_t move_time_ms = string_tokenizer.get_integer_token(1);
       command_interface.go_movetime(move_time_ms);
       return;
    }
    if (string_tokenizer.next_token_is_one_of("ponder", "p")) {
        command_interface.go_ponder();
        return;
    }
    uint64_t white_time_ms = 0;
    uint64_t black_time_ms = 0;
    uint64_t white_increment_ms = 0;
    uint64_t black_incrementt_ms = 0;
    uint64_t moves_to_go = 0;
    std::string next_token = string_tokenizer.next_token();
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
            send_error("unexpected token in go-command");
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
        trim(message);
        // Exit handling here in order to decouple
        // message_loop, string_tokenizer and process_message for better testability
        if  ((message == "quit") || (message == "exit") || (message == "q") || (message == "x")) {
            command_interface.on_exit();
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
    send_message("    * 'uciewgame' to start a new game");
    send_message("    * 'test' for the self-test");
    send_message("    * 'perft' for a looong test of the move_generator");
    send_message("    * 'psv' to display the main piece-square-value-tables");
    send_message("    * e2e4 to execute a move at the console interface");
    send_message("    * back or b to take back a move");
    send_message("    * 'quit' or 'x'to terminate");
}

void CUciProtocol::process_option(CStringTokenizer &string_tokenizer) {
    if (string_tokenizer.next_token_is_one_of( "name", "n") == false) {
       send_error("malformed option command"); 
        return;
    }
    std::string name = string_tokenizer.next_token();
    if (string_tokenizer.next_token_is_one_of( "value", "v") == false) {
       send_error("malformed option command"); 
        return;
    }
    std::string value = string_tokenizer.next_token();
    if ((name == "book") || (name == "b")) {
        command_interface.master_book.set_option(value);
    } else {
        send_error("unknown option name");
    }
}

void CUciProtocol::display_board() {
    send_message(board.get_fen_position());
    send_message(board.as_is());
}

