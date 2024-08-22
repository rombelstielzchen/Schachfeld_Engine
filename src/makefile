# Compiler cnfiguration

CC=g++

CFLAGS=-Wall -O0  -c $^

# Variables

CombinedSources="all_in_one.cpp"

Tmp1=".tmp1.tmp"
Tmp2=".tmp2.tmp"

# Main build target

debug: makefile main.o board.o uci_protocol.o string_functions.o fen_parser.o command_interface.o move_generator.o move.o
	make semi_clean 
	# Building engine
	g++ -o engine main.cpp string_functions.o uci_protocol.o board.o fen_parser.o command_interface.o move_generator.o move.o
	@echo "===================="
	@ls -o engine
	@sl

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
	
# Other build targets

optimized:
	make clean
	cat */*.h >> $(Tmp1)
	cat *.cpp >> $(Tmp1)
	cat */*.cpp >> $(Tmp1)
	# Edit some preprocessor directives away
	sed -e 's/#include "/\/\/#include "/' $(Tmp1) > $(Tmp2)
	mv $(Tmp2) $(CombinedSources)
	wc $(CombinedSources)
	$(CC) $(CFLAGS) $(CombinedSources)

semi_clean:
	# Deleting unnecessary and potentially outdated precompiled headers
	rm -f *.h,gch */*.h.gch
	# Deleting code, automatically derived from other files
	rm -f $(CombinedSources)
	# Deleting binaries
	rm -f engine
	rm -f a.out

clean:
	make semi_clean
	# Remove all object files
	rm -f *.o

stats:
	wc *.cpp */*.cpp */*.h
	ls -o engine
