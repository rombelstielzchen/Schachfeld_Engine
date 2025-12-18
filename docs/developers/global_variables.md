Global Variables
=================
The Schachfeld-engine tries to reduce the use of global variables  in order to minimize troubles. The following ones were necessary however:
* board/board.h:inline CBoard board;
* search/search_statistics.h:inline CSearchStatistics search_statistics;
* technical_functions/testing.h:inline int testcase_counter = 0;
* universal_chess_interface/command_interface.h:inline bool DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop;

