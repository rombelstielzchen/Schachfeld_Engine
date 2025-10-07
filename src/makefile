# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#
# Quick and dirty make-file; for some help please see README.md.
#
# TODO
#    * header-dependencies
#    * optimized

### Compiler cnfiguration ##############
#
# GCC warning options: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

CC=g++

DEBUGFLAGS=-D DEBUG_LOG_ENABLE -std=c++17 -Wall -Wextra -Wpedantic -Werror -fmax-errors=1 -O0 -c $^
OPTIMIZEDFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Werror -O2  -c $^
CFLAGS=$(DEBUGFLAGS)

### Main build-target ##################

default:
	make engine
	make test
	@echo "=============================="
	@ls -o engine

engine: \
	board.o \
	board_logic.o \
	command_interface.o \
	data_book.o \
	depth_control.o \
	engine_test.o \
	evaluator.o \
	expert_endgame_king_activity.o \
	expert_general.o \
	fen_generator.o \
	fen_parser.o \
	game_saver.o \
	gm_book.o \
	info_thread.o \
	iterative_deepening.o \
	killer_heuristics.o \
	main.o \
	master_book.o \
	math_functions.o \
	move.o \
	move_generator.o \
	move_list.o \
	move_list__filters.o \
	move_list__get.o \
	move_list__store.o \
	move_maker.o \
	oracle.o \
	piece_square_value_tables.o \
	search.o \
	search_statistics.o \
	string_functions.o  \
	string_tokenizer.o \
	tabijas.o \
	test_board.o \
	test_board_logic.o \
	test_evaluator.o \
	test_killer_heuristics.o \
	test_math_functions.o \
	test_move.o \
	test_move_generator.o \
	test_move_list.o \
	test_move_maker.o \
	test_opening_book.o \
	test_oracle.o \
	test_perft.o \
	test_piece_square_value_tables.o \
	test_search.o \
	test_statistics.o \
	test_technical_functions.o \
	time_functions.o \
	uci_protocol.o \
	virtual_expert.o \
	wonder_weapons_black.o \
	wonder_weapons_white.o
	make semi_clean 
	make standard_headers
	### Linking engine
	$(CC) -o $@ $^ 
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

virtual_expert.o: evaluator/knowledge/virtual_expert.cpp
	$(CC) $(CFLAGS) 

wonder_weapons_black.o: opening_book/book_data/wonder_weapons_black.cpp
	$(CC) $(CFLAGS) 

wonder_weapons_white.o: opening_book/book_data/wonder_weapons_white.cpp
	$(CC) $(CFLAGS) 

fen_parser.o: board/fen_parser.cpp
	$(CC) $(CFLAGS) 

game_saver.o: board/game_saver.cpp
	$(CC) $(CFLAGS) 

command_interface.o: universal_chess_interface/command_interface.cpp
	$(CC) $(CFLAGS) 

move_generator.o: move_generator/move_generator.cpp
	$(CC) $(CFLAGS) 

move.o: move_generator/move.cpp
	$(CC) $(CFLAGS) 

test_move.o: move_generator/test_move.cpp 
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

time_functions.o: technical_functions/time_functions.cpp
	$(CC) $(CFLAGS) 

board_logic.o: board/board_logic.cpp
	$(CC) $(CFLAGS) 

master_book.o: opening_book/master_book.cpp
	$(CC) $(CFLAGS) 

data_book.o: opening_book/data_book.cpp
	$(CC) $(CFLAGS) 


depth_control.o: search/depth_control.cpp
	$(CC) $(CFLAGS) 

test_oracle.o: evaluator/test_oracle.cpp
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

move_list__filters.o: move_generator/move_list__filters.cpp
	$(CC) $(CFLAGS) 

move_list__get.o: move_generator/move_list__get.cpp
	$(CC) $(CFLAGS) 

move_list__store.o: move_generator/move_list__store.cpp
	$(CC) $(CFLAGS) 

search.o: search/search.cpp
	$(CC) $(CFLAGS)

evaluator.o: evaluator/evaluator.cpp
	$(CC) $(CFLAGS)

expert_endgame_king_activity.o: evaluator/knowledge/endgame/expert_endgame_king_activity.cpp
	echo huhu
	$(CC) $(CFLAGS)

expert_general.o: evaluator/knowledge/general/expert_general.cpp
	$(CC) $(CFLAGS)

test_evaluator.o: evaluator/test_evaluator.cpp
	$(CC) $(CFLAGS)

test_search.o: search/test_search.cpp
	$(CC) $(CFLAGS) 

search_statistics.o: search/search_statistics.cpp
	$(CC) $(CFLAGS) 

info_thread.o: universal_chess_interface/info_thread.cpp
	$(CC) $(CFLAGS) 

iterative_deepening.o: search/iterative_deepening.cpp
	$(CC) $(CFLAGS) 

string_tokenizer.o: technical_functions/string_tokenizer.cpp
	$(CC) $(CFLAGS) 

tabijas.o: opening_book/book_data/tabijas.cpp
	$(CC) $(CFLAGS) 

test_piece_square_value_tables.o: evaluator/test_piece_square_value_tables.cpp

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

test_piece_square_value_tables.o: evaluator/test_piece_square_value_tables.cpp
	$(CC) $(CFLAGS) 

oracle.o: evaluator/oracle.cpp
	$(CC) $(CFLAGS) 

piece_square_value_tables.o: evaluator/piece_square_value_tables.cpp
	$(CC) $(CFLAGS) 

test_perft.o: move_generator/test_perft.cpp
	$(CC) $(CFLAGS) 

killer_heuristics.o: search/killer_heuristics.cpp
	$(CC) $(CFLAGS) 

test_killer_heuristics.o: search/test_killer_heuristics.cpp
	$(CC) $(CFLAGS) 

#### Other build targets ###############

exe:
	make clean
	cd visual_studio; \
	bash ./build.sh

test:
	### Testing engine, executing a quick self-test, without UCI.
	# For more tests see the "test" directory.
	echo "quit" | ./engine

semi_clean:
	### Deleting automatically generated code
	### Deleting Linux binaries
	rm -f engine
	rm -f a.out

clean:
	make semi_clean
	### Deleting Windows executables
	find visual_studio/ -name '*.exe' | xargs rm -f
	### Deleting precompiled headers
	find . -name '*.gch' | xargs rm -f
	find . -name '*.pch' | xargs rm -f
	### Remove all object files
	find . -name '*.o' | xargs rm -f
	find . -name '*.obj' | xargs rm -f
	# Remove logs
	find . -name 'debug.txt' | xargs rm -f
	find . -name 'schachfeld_games.pgn' | xargs rm -f

stats:
	@echo -n "LOC total:      "
	@find .. -name '*.cpp' -o -name '*.h' -o -name '*.sh' -o -name '*.pl' -o -name 'makefile' | sed '/docu_/d' | sed '/docs/d' | xargs  cat | wc -l
	@echo -n "Book-lines:      "
	@grep "\"," opening_book/book_data/*.cpp | wc -l
	@echo -n "Unit-tests:      "
	@find . -name 'test*.cpp' -o -name 'test*.h' -o -name '*test.cpp' -o -name '*test.h' | xargs cat | wc -l
	@echo -n "UCI-test:         "
	@cat ../test/*.pl | wc -l
	@echo -n "Assertions:       "
	@find . -name '*.cpp' -o -name '*.h' | xargs grep -s assert | wc -l
	@echo -n "LOC tools:        "
	@find .. -name 'makefile' -o -name '*.sh' -o -name '*.pl' | xargs cat | wc -l
	@echo -n "TODO items:        "
	@find . -name '*.cpp' -o -name '*.h' | xargs grep -s TODO | wc -l
	@echo -n "Longest header: " 
	@find . -name '*.h' | xargs wc -l | sort | tail -n 2 | head -n 1
	@echo -n "Longest source:" 
	@find . -name '*.cpp' | xargs wc -l | sed '/book_data/d' | sort | tail -n 2 | head -n 1
	@ls -o engine

todo:
	@find . -name '*.cpp' -o -name '*.h' | xargs grep -A1 -B1 TODO

standard_headers: technical_functions/standard_headers.h.gch

technical_functions/standard_headers.h.gch: technical_functions/standard_headers.h
	### Building precompiled headers
	$(CC) technical_functions/standard_headers.h

