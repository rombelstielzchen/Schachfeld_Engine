# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#
# Quick and dirty make-file
# TODO
#    * header-dependencies
#    * optimized
#    * analysis

### Compiler cnfiguration ##############

CC=g++

DEBUGFLAGS=-Wall -O0  -D DEBUG_LOG_ENABLE -c $^
OPTIMIZEDFLAGS=-Wall -O2  -c $^
ANALYSISFLAGS=-Wall -Wextra -Wpedantic -O0  -c $^
CFLAGS=$(DEBUGFLAGS)

COMBINEDSOURCES="all_in_one.cpp"

### Main build-target ##################

debug:
	### Setting debug options, then going to compile
#	export CFLAGS=$(DEBUGFLAGS)
	make -e engine

engine: makefile main.o board.o uci_protocol.o string_functions.o  \
	fen_parser.o command_interface.o move_generator.o move.o debug_log.o \
	test_move_generator.o engine_test.o fen_generator.o
	#make semi_clean 
#	CFLAGS=-Wall -O0  -c $^
	#make standard_headers
	### Linking engine
	echo "huhu"
	echo $(CFLAGS)
	g++ -o engine main.o string_functions.o uci_protocol.o board.o  \
	fen_parser.o command_interface.o move_generator.o move.o debug_log.o  \
	test_move_generator.o engine_test.o fen_generator.o
	make test
	@sl -e +extra_foo +immortality
	@echo "=============================="
	@ls -o engine

### Object files #######################

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

command_interface.o: universal_chess_interface/command_interface.cpp
	$(CC) $(CFLAGS) 

move_generator.o: move_generator/move_generator.cpp
	$(CC) $(CFLAGS) 

move.o: move_generator/move.cpp
	$(CC) $(CFLAGS) 

debug_log.o: technical_functions/debug_log.cpp
	$(CC) $(CFLAGS) 
	
test_move_generator.o: move_generator/test_move_generator.cpp
	$(CC) $(CFLAGS) 

fen_generator.o: board/fen_generator.cpp
	$(CC) $(CFLAGS) 

engine_test.o: technical_functions/engine_test.cpp
	$(CC) $(CFLAGS) 

#### Other build targets ###############

optimized:
	make clean
	### Generating all-in-one source-file
	cat *.cpp */*.cpp > $(COMBINEDSOURCES)
	### Building with optimizing options
	CFLAGS=OPTIMIZEDFLAGS
	$(CC) $(CFLAGS) $(COMBINEDSOURCES)

analysis:
	make clean
	### Building with extra warnings
	CFLAGS=ANALYSISFLAGS
	make engine

test:
	### Testing engine
	# Quick and dirty:
	# Start the engine, self-test in debug-mode, then quit
	echo "quit" | ./engine

semi_clean:
	### Deleting automatically generated code
	rm -f $(COMBINEDSOURCES)
	### Deleting binaries
	rm -f engine
	rm -f a.out

clean:
	##
	make semi_clean
	### Deleting precompiled headers
	rm -f *.h,gch */*.h.gch
	### Remove all object files
	rm -f *.o */*.o

stats:
	wc *.cpp */*.cpp */*.h */*/*.cpp */*/*.h makefile
	ls -o engine

standard_headers: technical_functions/standard_headers.h.gch

technical_functions/standard_headers.h.gch: technical_functions/standard_headers.h
	### Building precompiled headers
	$(CC) technical_functions/standard_headers.h

