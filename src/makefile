CC=g++

CFLAGS=-Wall -O0  -c $^

engine: main.o board.o uci_protocol.o string_functions.o fen_parser.o
	g++ -o engine main.cpp string_functions.o uci_protocol.o board.o fen_parser.o
	@echo "===================="
	@ls -o engine

main.o: main.cpp
	$(CC) $(CFLAGS) 

board.o: board/board.cpp
	$(CC) $(CFLAGS) 

string_functions.o: technical_functions/string_functions.cpp
	$(CC) $(CFLAGS) 

uci_protocol.o: universal_chess_interface/uci_protocol.cpp
	$(CC) $(CFLAGS) 

fen_parser.o: board/fen_parser.cpp
	$(CC) $(CFLAGS) 

clean:
	rm -f *.o
	rm -f *.gch

stats:
	    wc *.cpp */*.cpp */*.h
		ls -o engine
