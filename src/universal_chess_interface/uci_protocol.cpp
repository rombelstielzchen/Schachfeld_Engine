// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "uci_protocol.h"
#include "command_interface.h"
#include <iostream>
#include <string>

// Universal Chess Interface Protocol
// https://gist.github.com/DOBRO/2592c6dad754ba67e6dcaec8c90165bf

void CUciProtocol::send_message(const std::string message) {
    // UCI standard says:
    //   * communication via text-IO
    //   * every message should end with a new-line, "\n"
    // To be on the safe side. we use endl, which also flushes the buffer.
    std::cout << message << std::endl;
}

void CUciProtocol::identify_engine() {
    send_message("id name Schachfeld 0.2");
    send_message("id author Rombelstielzchen");
}

void CUciProtocol::send_list_of_options() {
    // None yet
}

void CUciProtocol::process_message(const std::string command) {
    if (command== "go") {
        // TODO: parse the many options of "go", all in the same line
        command_interface.go_infinite();
    } else if (command== "isready") {
        // Our first version is always and immediately ready
        send_message("readyok");
    } else if (command == "position") {
        std::string fen_position = string_tokenizer.get_the_rest();
        command_interface.set_position(fen_position);
    } else if (command== "stop") {
        command_interface.stop();
    } else if (command == "uci") {
         identify_engine();
         send_list_of_options(); 
         send_message("uciok");
    } else if (command == "ucinewgame") {
        command_interface.new_game();
    } else {
        // "quit" already gets handled by the message_loop().
        // Silently ignore all unknown / unsupported commands
    }
}

void CUciProtocol::message_loop() {
    while (true) {
        std::string message;
        getline(std::cin, message);
        string_tokenizer.set_input(message);
        std::string command = string_tokenizer.next_token(); 
        if  (command == "quit") {
            break;
        }
        process_message(command);
    }
}
