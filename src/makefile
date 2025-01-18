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

DEBUGFLAGS=-D DEBUG_LOG_ENABLE -std=c++17 -Wall -O0 -c $^
OPTIMIZEDFLAGS=-std=c++17 -Wall -O2  -c $^
ANALYSISFLAGS==-std=c++17 -Wall -Wextra -Wpedantic -O0  -c $^
CFLAGS=$(DEBUGFLAGS)

### Main build-target ##################

engine: main.o board.o uci_protocol.o string_functions.o  \
	fen_parser.o command_interface.o move_generator.o move.o \
test_move_generator.o engine_test.o fen_generator.o test_board.o \
	test_technical_functions.o board_logic.o opening_book.o test_opening_book.o \
	gm_book.o move_maker.o test_move_maker.o move_list.o search.o test_search.o \
	evaluator.o test_evaluator.o search_statistics.o iterative_deepening.o \
	string_tokenizer.o test_statistics.o test_math_functions.o math_functions.o \
	test_move_list.o test_board_logic.o
	make semi_clean 
	make standard_headers
	### Linking engine
	$(CC) -o $@ $^ 
	make test
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

test_move_generator.o: move_generator/test_move_generator.cpp
	$(CC) $(CFLAGS) 

fen_generator.o: board/fen_generator.cpp
	$(CC) $(CFLAGS) 

engine_test.o: technical_functions/engine_test.cpp
	$(CC) $(CFLAGS) 

test_board.o: board/test_board.cpp
	$(CC) $(CFLAGS) 

test_technical_functions.o: technical_functions/test_technical_functions.cpp
	$(CC) $(CFLAGS) 

board_logic.o: board/board_logic.cpp
	$(CC) $(CFLAGS) 

opening_book.o: opening_book/opening_book.cpp
	$(CC) $(CFLAGS) 

test_opening_book.o: opening_book/test_opening_book.cpp
	$(CC) $(CFLAGS) 

gm_book.o: opening_book/book_data/gm_book.cpp
	$(CC) $(CFLAGS) 

move_maker.o: board/move_maker.cpp
	$(CC) $(CFLAGS) 

test_move_maker.o: board/test_move_maker.cpp
	$(CC) $(CFLAGS) 

move_list.o: move_generator/move_list.cpp
	$(CC) $(CFLAGS) 

search.o: search/search.cpp
	$(CC) $(CFLAGS)

evaluator.o: evaluator/evaluator.cpp
	$(CC) $(CFLAGS)

test_evaluator.o: evaluator/test_evaluator.cpp
	$(CC) $(CFLAGS)

test_search.o: search/test_search.cpp
	$(CC) $(CFLAGS) 

search_statistics.o: search/search_statistics.cpp
	$(CC) $(CFLAGS) 

iterative_deepening.o: search/iterative_deepening.cpp
	$(CC) $(CFLAGS) 

string_tokenizer.o: technical_functions/string_tokenizer.cpp
	$(CC) $(CFLAGS) 

test_statistics.o: search/test_statistics.cpp
	$(CC) $(CFLAGS) 

test_math_functions.o: technical_functions/test_math_functions.cpp
	$(CC) $(CFLAGS) 

math_functions.o: technical_functions/math_functions.cpp
	$(CC) $(CFLAGS) 

test_move_list.o: move_generator/test_move_list.cpp
	$(CC) $(CFLAGS) 

test_board_logic.o: board/test_board_logic.cpp
	$(CC) $(CFLAGS) 

#### Other build targets ###############

test:
	### Testing engine, executing a quick self-test, without UCI.
	# For more tests see the "test" directory.
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
	@wc *.cpp */*.cpp */*.h */*/*.cpp */*/*.h makefile */*/*.sh
	@echo -n "Book-lines: "
	@grep "\"," opening_book/book_data/gm_book.cpp | wc -l
	@echo -n "TODO items: "
	@grep TODO *.cpp */*.cpp */*/*.cpp | wc -l
	@ls -o engine

standard_headers: technical_functions/standard_headers.h.gch

technical_functions/standard_headers.h.gch: technical_functions/standard_headers.h
	### Building precompiled headers
	$(CC) technical_functions/standard_headers.h

