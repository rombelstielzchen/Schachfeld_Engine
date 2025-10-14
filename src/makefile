#
# Project: Schachfeld_Engine
# Author: Rombelstielzchen
# License: GPLv3
# Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
#
# Build targets:
#   * make: build a Linux debug executable and run the self-test (default)
#   * make optimized: build an optimized Linux executable
#   * make exe: build a Windows executable (Visual Studio required)
#   * make clean: remove all executables and intermediate files
#   * make stats: display project statistics
#   * make todo: display TODO comments
#
# https://makefiletutorial.com/
# https://www.gnu.org/software/make/manual/make.html
#
# TODO
#    * header-dependencies
#    * maybe change optimized zo O3
#    * have a look, why "optimized" Linux is not even half as fast as Windows

### Default shell and automatic rules ##

SHELL := /bin/sh
.SUFFIXES:
.SUFFIXES: .c .cpp .o

### Compiler cnfiguration ##############
#
# GCC warning options: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

CXX := g++

GENERAL_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -fmax-errors=1 
GENERAL_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -fmax-errors=1 
DEBUG_FLAGS := -D DEBUG_LOG_ENABLE -O0
OPTIMIZED_FLAGS := -D NDEBUG -O2

CXXFLAGS := $(GENERAL_FLAGS)

.PHONY: debug
debug: CXXFLAGS += $(DEBUG_FLAGS)

.PHONY: optimized
optimized: CXXFLAGS += $(OPTIMIZED_FLAGS)

CXXFLAGS += -c $^

EXECUTABLE = engine

### File lists #########################

OBJECT_FILES :=  \
	board.o \
	board_logic.o \
	command_interface.o \
	data_book.o \
	depth_control.o \
	engine_test.o \
	evaluator.o \
	expert_endgame_king_activity.o \
	expert_endgame_pawn.o \
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
	mate_score.o \
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
	test_depth_control.o \
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

### Main build-target (Linux debug) ####

.PHONY: "debug
debug: engine

engine: $(OBJECT_FILES)
	make semi_clean 
	make standard_headers
	$(CXX) -o $@ $^ 
	make test
	make build_summary

### Object files #######################

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^ 

board.o: board/board.cpp
	$(CXX) $(CXXFLAGS) $^ 

string_functions.o: technical_functions/string_functions.cpp
	$(CXX) $(CXXFLAGS) $^ 

uci_protocol.o: universal_chess_interface/uci_protocol.cpp
	$(CXX) $(CXXFLAGS) $^ 

virtual_expert.o: evaluator/knowledge/virtual_expert.cpp
	$(CXX) $(CXXFLAGS) $^ 

wonder_weapons_black.o: opening_book/book_data/wonder_weapons_black.cpp
	$(CXX) $(CXXFLAGS) $^ 

wonder_weapons_white.o: opening_book/book_data/wonder_weapons_white.cpp
	$(CXX) $(CXXFLAGS) $^ 

fen_parser.o: board/fen_parser.cpp
	$(CXX) $(CXXFLAGS) $^ 

game_saver.o: board/game_saver.cpp
	$(CXX) $(CXXFLAGS) $^ 

command_interface.o: universal_chess_interface/command_interface.cpp
	$(CXX) $(CXXFLAGS) $^ 

move_generator.o: move_generator/move_generator.cpp
	$(CXX) $(CXXFLAGS) $^ 

move.o: move_generator/move.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_move.o: move_generator/test_move.cpp 
	$(CXX) $(CXXFLAGS) $^ 

test_move_generator.o: move_generator/test_move_generator.cpp
	$(CXX) $(CXXFLAGS) $^ 

fen_generator.o: board/fen_generator.cpp
	$(CXX) $(CXXFLAGS) $^ 

engine_test.o: technical_functions/engine_test.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_board.o: board/test_board.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_technical_functions.o: technical_functions/test_technical_functions.cpp
	$(CXX) $(CXXFLAGS) $^ 

time_functions.o: technical_functions/time_functions.cpp
	$(CXX) $(CXXFLAGS) $^ 

board_logic.o: board/board_logic.cpp
	$(CXX) $(CXXFLAGS) $^ $^

master_book.o: opening_book/master_book.cpp
	$(CXX) $(CXXFLAGS) $^ 

data_book.o: opening_book/data_book.cpp
	$(CXX) $(CXXFLAGS) $^ 


depth_control.o: search/depth_control.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_oracle.o: evaluator/test_oracle.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_opening_book.o: opening_book/test_opening_book.cpp
	$(CXX) $(CXXFLAGS) $^ 

gm_book.o: opening_book/book_data/gm_book.cpp
	$(CXX) $(CXXFLAGS) $^ 

move_maker.o: board/move_maker.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_move_maker.o: board/test_move_maker.cpp
	$(CXX) $(CXXFLAGS) $^ 

move_list.o: move_generator/move_list.cpp
	$(CXX) $(CXXFLAGS) $^ 

move_list__filters.o: move_generator/move_list__filters.cpp
	$(CXX) $(CXXFLAGS) $^ 

move_list__get.o: move_generator/move_list__get.cpp
	$(CXX) $(CXXFLAGS) $^ 

move_list__store.o: move_generator/move_list__store.cpp
	$(CXX) $(CXXFLAGS) $^ 

search.o: search/search.cpp
	$(CXX) $(CXXFLAGS) $^

evaluator.o: evaluator/evaluator.cpp
	$(CXX) $(CXXFLAGS) $^

expert_endgame_king_activity.o: evaluator/knowledge/endgame/expert_endgame_king_activity.cpp
	$(CXX) $(CXXFLAGS) $^

expert_endgame_pawn.o: evaluator/knowledge/endgame/expert_endgame_pawn.cpp
	$(CXX) $(CXXFLAGS) $^

expert_general.o: evaluator/knowledge/general/expert_general.cpp
	$(CXX) $(CXXFLAGS) $^

test_evaluator.o: evaluator/test_evaluator.cpp
	$(CXX) $(CXXFLAGS) $^

test_search.o: search/test_search.cpp
	$(CXX) $(CXXFLAGS) $^ 

search_statistics.o: search/search_statistics.cpp
	$(CXX) $(CXXFLAGS) $^ 

info_thread.o: universal_chess_interface/info_thread.cpp
	$(CXX) $(CXXFLAGS) $^ 

iterative_deepening.o: search/iterative_deepening.cpp
	$(CXX) $(CXXFLAGS) $^ 

string_tokenizer.o: technical_functions/string_tokenizer.cpp
	$(CXX) $(CXXFLAGS) $^ 

tabijas.o: opening_book/book_data/tabijas.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_piece_square_value_tables.o: evaluator/test_piece_square_value_tables.cpp

test_statistics.o: search/test_statistics.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_math_functions.o: technical_functions/test_math_functions.cpp
	$(CXX) $(CXXFLAGS) $^ 

mate_score.o: search/mate_score.cpp
	$(CXX) $(CXXFLAGS) $^

math_functions.o: technical_functions/math_functions.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_move_list.o: move_generator/test_move_list.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_board_logic.o: board/test_board_logic.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_depth_control.o:	search/test_depth_control.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_piece_square_value_tables.o: evaluator/test_piece_square_value_tables.cpp
	$(CXX) $(CXXFLAGS) $^ 

oracle.o: evaluator/oracle.cpp
	$(CXX) $(CXXFLAGS) $^ 

piece_square_value_tables.o: evaluator/piece_square_value_tables.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_perft.o: move_generator/test_perft.cpp
	$(CXX) $(CXXFLAGS) $^ 

killer_heuristics.o: search/killer_heuristics.cpp
	$(CXX) $(CXXFLAGS) $^ 

test_killer_heuristics.o: search/test_killer_heuristics.cpp
	$(CXX) $(CXXFLAGS) $^ 

#### Other build targets ###############

.PHONY: "build_summary
build_summary:
	@echo "=============================="
	@ls -o engine

.PHONY: "clean
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

.PHONY: "exe
exe:
	make clean
	cd visual_studio; \
	bash ./build.sh

.PHONY: "optimized
optimized:	engine

.PHONY: "semi_clean
semi_clean:
	### Deleting automatically generated code
	### Deleting Linux binaries
	rm -f engine
	rm -f a.out

.PHONY: "standard_headers
standard_headers: technical_functions/standard_headers.h.gch

technical_functions/standard_headers.h.gch: technical_functions/standard_headers.h
	### Building precompiled headers
	$(CXX) technical_functions/standard_headers.h

.PHONY: "stats
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

.PHONY: test
test:
	### Testing engine, executing a quick self-test, without UCI.
	# For more tests see the "test" directory.
	echo "quit" | ./engine

.PHONY: todo
todo:
	@find . -name '*.cpp' -o -name '*.h' | xargs grep -A1 -B1 TODO

