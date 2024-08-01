#include "universal_chess_interface/uci_protocol.h"

int main() {
    CUciProtocol uci_protocol;
    uci_protocol.message_loop();
     return EXIT_SUCCESS;
}
