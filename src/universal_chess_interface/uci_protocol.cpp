// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Universal Chess Interface Protocol
// https://gist.github.com/DOBRO/2592c6dad754ba67e6dcaec8c90165bf

#include "uci_protocol.h"
#include "command_interface.h"
#include "info_thread.h"
#include "../search/hash_table.h"
#include "../technical_functions/engine_test.h"
#include "../technical_functions/standard_headers.h"

const std::string ENGINE_ID = "MaterialGirl_1.3";
static_assert('a' > '9');

typedef struct {
    char selector;
    std::string description;
    std::string fen_position;
} SDefaultPosition;

const std::vector<SDefaultPosition> default_positions = {
    { ' ', "", "" },
    { '0', "mate with bishop and knight", "////3K//6k/n6b b" },
    { '7', "spanish pawn-endgame", "6k/ppp2ppp/2p//4P//PPP2PPP/6K w" },
    { 'b', "mate with two bishops", "////2Bk//6K/7B w" },
    { 'f', "Falkbeer-Counter-Gambit", "startpos moves e2e3 e7e6 e3e4 e6e5 f2f4 d7d5" },
    { 'g', "position after 1.g4", "startpos moves g2g4" },
    { 'h', "study by Herbstmann", "1B//7P/4p/3b3k///1K w" },
    { 'i', "talian game with c3", "e2e3 e7e6 e3e4 e6e5 g1f3 b8c6 f1c4 f8c5 c2c3" },
    { 'l', "Lucena", "2k1K/4P/////5r/3R w" },
    { 'n', "mate with three knights", "n6n///4K////n6k b"},
    { 'o', "opposition", "///2k///2PK w" },
    { 'p', "Philidor-position (queen-endgame)", "K/1R/2k/3q b" },
    { 'q', "mate with a queen", "///3k///6K/7Q w" },
    { 'r', "mate with a rook", "////4k///6KR b" },
    { 's', "start-position without opening-book", "startpos moves g1f3 g8f6 f3g1 f6g8" },
    { 't', "two knights game with Ng5", "e2e3 e7e6 e3e4 e6e5 g1f3 b8c6 f1c4 g8f6 f3g5" },
    { 'v', "Vienna game with 4.Qg4", "startpos moves e2e3 e7e6 e3e4 e6e5 b1c3 b8c6 f1c4 f8c5 d1g4 d8f6 c3d5" },
};

bool CUciProtocol::interactive_console_mode = false;
bool CUciProtocol::last_message_was_separator = false;
std::string CUciProtocol::recent_best_move = "";

CUciProtocol::CUciProtocol() {
    send_info(ENGINE_ID);
    send_info("'help' or '?' for some guidance");
    // Init the one and only info_thread immediately for convenience
    CInfoThread info_thread;
}

CUciProtocol::~CUciProtocol() {
    flush(std::cout);
    flush(std::cerr);
}

/* static */ void CUciProtocol::send_message(const std::string &message) {
    // Used by both UCI-thread and calculator-thread, therefore mutex-protected
        static std::mutex unique_message_mutex;
        std::lock_guard<std::mutex> lock(unique_message_mutex);
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
        + "default OurLittleAngel  by Rombelstielzchen. "
        + "Protocol: UCI. "
        + "Licensed as open-source under GPLv3. "
        + "Contact:  https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby "
        + "Source-code: https://github.com/rombelstielzchen/Schachfeld_Engine ");
    // UCI is a bit inconsistent. Mostly lowercase, the option is named "Hash".
    send_message(std::string("option name Hash type spin ")
        + "default 1 "
        + "min" + std::to_string(minimum_hash_MB) + " "
        + "max " + std::to_string(maximum_hash_MB) + " ");
    // Options for the future
    /* TODO; enable these options, once needed
    send_message(std::string("option name UCI_LimitStrength type check ")
         + "default false ");
    send_message(std::string("option name UCI_Elo type spin ")
        + "default 3456 "
        + "min 1 "
        + "max 3456 ");
    */
}

void CUciProtocol::send_info(const std::string &information) {
    std::string full_message = "info " + information;
    send_message(full_message);
    last_message_was_separator = false;
}

void CUciProtocol::log_separator() {
    send_info("****************************************");
    last_message_was_separator = true;
}

void CUciProtocol::send_error(const std::string &error_message) {
    std::string full_message = "error: " + error_message + "\n";
    std::cerr << full_message;
}

void CUciProtocol::send_best_move(const std::string &best_move) {
    assert(best_move != "");
    assert(looks_like_a_mnove(best_move));
    if (interactive_console_mode) {
        display_board();
        recent_best_move = best_move;
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

void CUciProtocol::process_message(std::string &message) {
    // This function is not reentrant, therefore proteccted by a mutex
    static std::mutex process_message_mutex;
    std::lock_guard<std::mutex> lock(process_message_mutex);
    process_message_recursively(message);
}

void CUciProtocol::process_message_recursively(std::string &message) {
    if (message == "") {
        return;
    }
    preprocess_message(message);
    CStringTokenizer string_tokenizer;
    string_tokenizer.set_input(message);
    if (string_tokenizer.next_token_is_one_of("back", "b")) {
        interactive_console_mode = true;
       command_interface.takeback();
    } else if (string_tokenizer.next_token_is_one_of("bestmove", "bm")) {
        // TODO: naming is not really uitable for this use-case
        process_unknown_token_potential_move(recent_best_move);
    } else if (string_tokenizer.next_token_is("debug")) { 
        interactive_console_mode = true;
        SWITCH_DEBUG_ON(string_tokenizer.next_token() == "on");
    } else if (string_tokenizer.next_token_is("dp")) {
        std::string next_token = string_tokenizer.next_token();
       process_default_position(next_token); 
    } else if (string_tokenizer.next_token_is_one_of("eval", "e")) {
        interactive_console_mode = true;
        command_interface.log_board_evaluation();
    } else if (string_tokenizer.next_token_is("hash")) {
       command_interface.show_hash(); 
    } else if (string_tokenizer.next_token_is_one_of("go", "g")) {
        process_go_command(string_tokenizer);
    } else if (string_tokenizer.next_token_is_one_of("help", "?")) {
        interactive_console_mode = true;
        display_help();
    } else if (string_tokenizer.next_token_is("isready")) {
        handle_isready_query();
    } else if (string_tokenizer.next_token_is("perft")) {
        interactive_console_mode = true;
        (void)command_interface.test_move_generator();
    } else if (string_tokenizer.next_token_is("psv")) {
        command_interface.show_main_psv_tables();  
    } else if (string_tokenizer.next_token_is_one_of("position", "p")) {
        std::string fen_position = string_tokenizer.get_the_rest();
        command_interface.set_position(fen_position);
    } else if (string_tokenizer.next_token_is_one_of("setoption", "so")) {
        process_option(string_tokenizer);
    } else if (string_tokenizer.next_token_is_one_of("stop", "s")) {
        command_interface.stop();
    } else if (string_tokenizer.next_token_is("test")) {
        interactive_console_mode = true;
        CEngineTest::test(); 
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
            process_message_recursively(remaining_message);
        }
    }
}

void CUciProtocol::process_unknown_token_potential_move(const std::string &token) {
    if (looks_like_a_mnove(token)) {
        //TODO: move all board-handling to CCommandInterface
        board.clone_from_global_reference_board();
        interactive_console_mode |= board.move_maker.make_move(token);
        board.clone_to_global_reference_board();
        return;
    }
    int my_maybe_number = atoi(token.c_str());
    constexpr int huge_number_that_can_hardly_qualify_as_rank_or_depth = 30;
    if (my_maybe_number > huge_number_that_can_hardly_qualify_as_rank_or_depth) {
        hash_table.set_size(my_maybe_number);
        return;
    }
    std::string message = "ignoring unknown token \"" + token + '"';
    send_error(message);
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
        if (next_token == "time") {
            // Consume silently, more tokens coming (wtime, btime, winc, binc, movestogo)
            (void)NULL;
        } else if (next_token == "wtime") {
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
                std::string error_message = "unexpected token in go-command: " + next_token;
            send_error(error_message);
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
    delay_in_ms += (last_message == "") ? delta_delay : 0;
    delay_in_ms = std::min(delay_in_ms, max_delay);
    delay_in_ms = (last_message == "") ? delay_in_ms : 0;
    assert((delay_in_ms == 0) || (last_message == ""));
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_in_ms));
}

void CUciProtocol::display_default_positions()  const {
    for (const SDefaultPosition &d: default_positions) {
        std::string info = std::string("dp ") + d.selector + ": " + d.description;
        send_info(info);
    };
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
    send_message("    * 'stop' or 's' to force a move");
    send_message("    * 'ucinewgame' or 'ng' to start a new game");
    send_message("    * 'test' for the self-test");
    send_message("    * 'perft' for a looong test of the move_generator");
    send_message("    * 'debug on | off' to toggle extended logging");
    send_message("    * 'eval' or 'e' for a static evaluation of the current position");
    send_message("    * 'hash' to display the hash-entry of the current position");
    send_message("    * 'psv' to display the main piece-square-value-tables");
    send_message("    * e2e4 to execute a move at the console interface");
    send_message("    * back or 'b' to take back a move");
    send_message("    * bestmove or 'bm' to play the recent bestmove");
    send_message("    * ''dp' to display / setup default test positions");
    send_message("    * 'quit' or 'x'to terminate");
}

void CUciProtocol::process_option(CStringTokenizer &string_tokenizer) {
    if (string_tokenizer.next_token_is_one_of( "name", "n") == false) {
       send_error("malformed option command. Missing \"name\""); 
        return;
    }
    std::string name = string_tokenizer.next_token();
    if (string_tokenizer.next_token_is_one_of( "value", "v") == false) {
       send_error("malformed option command. Missing \"value\""); 
        return;
    }
    std::string value = string_tokenizer.next_token();
    if ((name == "book") || (name == "b")) {
        command_interface.master_book.set_option(value);
    } else if ((name == "Hash") || (name == "hash") | (name == "h")) {
        // UCI is a bit inconsistent. Mostly lowercase, the option is named "Hash".
        int new_size = atoi(value.c_str());
        hash_table.set_size(new_size);    
    } else {
        send_error("unknown option name");
    }
}

void CUciProtocol::display_board() {
    board.clone_from_global_reference_board();
    send_message(board.get_fen_position());
    send_message(board.as_is());
}

void CUciProtocol::handle_isready_query() const {
    if (CEngineTest::is_testing()) {
        send_message("busytesting");
    } else {
        send_message("readyok");
    }
}

bool CUciProtocol::looks_like_a_mnove(const std::string token) {
    constexpr int length_of_move = 4;
    constexpr int length_of_move_with_promotion = 5;
    if ((token.length() < length_of_move) || (token.length() > length_of_move_with_promotion)) {
        return false;
    }
    return (isalpha(token[0]) && isdigit(token[1]) && isalpha(token[2]) && isdigit(token[3]));
}

void CUciProtocol::process_default_position(const std::string next_token) {
    if (next_token == "") {
        display_default_positions();
        return;
    }
    for (const SDefaultPosition &d: default_positions) {
        assert(next_token.length() >= 1);
        if (next_token[0] == d.selector) {
            command_interface.set_position(d.fen_position);
            break;
        }
    }
}

