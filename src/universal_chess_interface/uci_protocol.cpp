#include "uci_protocol.h"

#include <iostream>
#include <string>

#include "../technical_functions/string_functions.h"

std::string best_move() {
    // Dummy-function, just playing Ng8-f6-g8-f6, just to get UCI running
    static bool knight_on_g8 = false;
    knight_on_g8 = !knight_on_g8;
    return knight_on_g8 ? "g8f6" : "f6g8";
}

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
    send_message("id name Schachfeld 0.1");
    send_message("id author Rombelstielzchen");
}

void CUciProtocol::send_list_of_options() {
    // None yet
}

void CUciProtocol::send_best_move() {
    std::string message = "bestmove " + best_move();
    send_message(message);
}

void CUciProtocol::process_message(const std::string command) {
    if (command == "uci") {
         identify_engine();
         send_list_of_options(); 
         send_message("uciok");
    } else if (command== "isready") {
        // Our first version is always and immediately ready
        send_message("readyok");
    } else if (command== "go") {
        send_best_move();
    } else if (command== "stop") {
        send_best_move();
    } else {
        // "quit" already gets handled by the message_loop().
        // Silently ignore all unknown / unsupported commands
    }
}

void CUciProtocol::message_loop() {
    while (true) {
        std::string message;
        getline(std::cin, message);
        CStringTokenizer tokenizer(message);
        std::string command = tokenizer.next_token(); 
        if  (command == "quit") {
            break;
        }
        process_message(command);
    }
}
