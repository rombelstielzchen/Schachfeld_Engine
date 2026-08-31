// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"test_search.h"
#include "testcases_search.h"
#include "testcases_static_exchange_evaluation.h"
#include "iterative_deepening.h"
#include "search.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../evaluator/score_constants.h"
#include "../technical_functions/testing.h"
#include "../universal_chess_interface/command_interface.h"

bool CTestSearch::test_everything() {
    BEGIN_TESTSUITE("CTestSearch");
    bool former_dobb_dobb_dobb = DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop;
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    EXPECT(test_no_legal_moves());
    EXPECT(test_scores());
    EXPECT(test_non_greedy_mate_scores());
    EXPECT(test_static_exchange_evaluation());
    EXPECT(test_early_exit());
    EXPECT(test_anti_repetition());
    EXPECT(test_positions());
    EXPECT(test_go_nodes());
///TODO    EXPECT(test_go_movetime());
    EXPECT(test_repeated_mate_in_one());
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = former_dobb_dobb_dobb;
    return true;
}

bool CTestSearch::test_no_legal_moves() {
    TEST_FUNCTION();
    CSearch search;
    SILENT_EXPECT(board.set_fen_position("1k//K1Q w"));
    EXPECT(search.no_legal_moves() == false);
    board.move_maker.make_null_move();
    EXPECT(search.no_legal_moves() == true);
    board.move_maker.unmake_null_move();
    EXPECT(search.no_legal_moves() == false);
    return true;
}

bool CTestSearch::test_static_exchange_evaluation() {
    TEST_FUNCTION();
    CSearch searcher;
    for (const STestcaseStaticExchangeEvaluation &testcase : testcases_static_exchange_evaluation) {
        CTEST << "Testcase: " << testcase.fen_position << testcase.capture_square << testcase.favorable_capture << "\n";
        SILENT_EXPECT(board.set_fen_position(testcase.fen_position));
        int initial_evaluation = board.evaluator.evaluate();
        int initial_negascore = board.evaluator.nega_score();
        int negamax_evaluation_after_capture = searcher.static_exchange_evaluation_negamax(testcase.capture_square, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta);
        EXPECT((negamax_evaluation_after_capture > initial_negascore) == testcase.favorable_capture);
        int minimax_evaluation_after_capture = searcher.static_exchange_evaluation_minimax(testcase.capture_square, INFINITE_ALPHA_BETA_WINDOW);
        if (board.get_side_to_move() == WHITE_PLAYER) {
            EXPECT((minimax_evaluation_after_capture > initial_evaluation) == testcase.favorable_capture);

        } else {
            EXPECT((minimax_evaluation_after_capture < initial_evaluation) == testcase.favorable_capture);
        }
    }
    return true;
}

bool CTestSearch::test_early_exit() {
    TEST_FUNCTION();
    CTEST << "Testing some trivial positions for early exit.\n";
    CTEST << "If we get stuck, something went wrong.\n";
    CIterativeDeepening searcher, searcher2;
    constexpr int really_deep = 666;
    std::string no_legal_moves = "k/2QK b";
    EXPECT(board.set_fen_position(no_legal_moves));
    EXPECT(searcher.search_depth(really_deep) == NULL_MOVE);
    std::string only_one_legal_move = "k/3QK b";
    EXPECT(board.set_fen_position(only_one_legal_move));
    EXPECT(searcher.search_depth(really_deep) == "a8b8");
    std::string mate_in_one = "k/3P/K w";
    EXPECT(board.set_fen_position(mate_in_one));
    SMove mating_move = searcher2.search_depth(really_deep);
    EXPECT((mating_move == "d7d8Q") || (mating_move == "d7d8R"));
    return true;
}

bool CTestSearch::test_anti_repetition() {
    TEST_FUNCTION();
    EXPECT(board.set_fen_position("R4rk/////6P/5PKP/ w"));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    EXPECT(move_generator.move_list.list_size() == 22);
    EXPECT(board.move_maker.move_history_contains_repetition() == false);
    EXPECT(board.move_maker.play_variation("a8a7 f8f7 a7a8"));
    EXPECT(board.move_maker.move_history_contains_repetition() == false);
    EXPECT(board.move_maker.play_variation("f7f8"));
    EXPECT(board.move_maker.move_history_contains_repetition() == true);
    CIterativeDeepening searcher;
    SMove best_move = searcher.search_depth(1);
    CTEST << "Got move: " << best_move << "\n";
    EXPECT(best_move == "a8f8");
    EXPECT(best_move.potential_gain > 0);
    return true;
}

bool CTestSearch::test_scores() {
    TEST_FUNCTION();
    CSearch searcher;
    std::string illegal_position = "///////// w";
    EXPECT(searcher.search_position(illegal_position) == SCORE_TECHNICAL_MIN);
    std::string draw = "kQ5K/6r b";
    EXPECT(abs(searcher.search_position(draw)) < SCORE_HALF_PAWN);
///    EXPECT(searcher.search_position(draw) == SCORE_DRAW);
       std::string const already_mate = "1k5R//1K b";
    std::string const mate_in_one = "k/7R/K w";
    std::string mate_in_one_dot_five = "k/7R/1K b";
    std::string const mate_in_two = "k/7P//K w";
    EXPECT(board.set_fen_position(already_mate));
    int evaluation = searcher.alpha_beta_negamax(1, 1, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta);
    EXPECT(evaluation < 0);
    EXPECT(evaluation < -SCORE_KING);
    EXPECT(board.set_fen_position(mate_in_one));
    evaluation = searcher.alpha_beta_negamax(2, 1, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta);
    EXPECT(evaluation > 0);
    EXPECT(evaluation > SCORE_KING);
    EXPECT(board.set_fen_position(mate_in_one_dot_five));
    evaluation = searcher.alpha_beta_negamax(3, 1, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta);
    EXPECT(evaluation < 0);
    EXPECT(evaluation < -SCORE_KING);
    EXPECT(board.set_fen_position(mate_in_two));
    evaluation = searcher.alpha_beta_negamax(4, 1, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta);
    EXPECT(evaluation > 0);
    EXPECT(evaluation > SCORE_KING);
    return true;
}

bool CTestSearch::test_non_greedy_mate_scores() {
    TEST_FUNCTION();
    CSearch searcher;
     std::string mate_with_rook = "k6R//K b";
    std::string mate_with_queen = "k6Q//K b";
    CTEST << "mate_with_queen: " << searcher.search_position(mate_with_queen) << "\n";
    CTEST << "mate_with_rook: " << searcher.search_position(mate_with_rook) << "\n";
    // Attention! The losing side is on the move, 
    // so the mate with the queen is better, worse for the enemy!
    EXPECT(searcher.search_position(mate_with_queen) > searcher.search_position(mate_with_rook));


    return true;
}

bool CTestSearch::test_positions() {
    TEST_FUNCTION();
    for (const STestcaseSearch &testcase : testcases_search) {
        SILENT_EXPECT(test_position(testcase));
    }
    return true;
}

bool CTestSearch::test_position(const STestcaseSearch &testcase) {
    assert(testcase.depth > 0);
    assert(testcase.expected_move != "");
    assert(testcase.fen_position != "");
    CTEST << "Searching: " << testcase.fen_position << "\n";
    CTEST << "Expecting: " << testcase.expected_move << "\n";
    SILENT_EXPECT(board.set_fen_position(testcase.fen_position));
    assert((board.evaluator.nega_score()) < SCORE_HALF_KING);
    CIterativeDeepening searcher;
    SMove best_move = searcher.search_depth(testcase.depth);
    CTEST << "Searching: " << testcase.fen_position << "\n";
    CTEST << "Expecting: " << testcase.expected_move << "\n";
    CTEST << "Got move: " << best_move << "\n";
    EXPECT(best_move == testcase.expected_move);
    return true;
}

bool CTestSearch::test_go_nodes() {
    TEST_FUNCTION();
    CIterativeDeepening searcher;
    SILENT_EXPECT(board.set_fen_position("k//K/////2R w"));
    EXPECT(searcher.search_nodes(1000) == "c1c8");
    return true;
}

bool CTestSearch::test_go_movetime() {
    TEST_FUNCTION();
    CIterativeDeepening searcher;
    SILENT_EXPECT(board.set_fen_position("k//K/////2R w"));
    EXPECT(searcher.search_movetime(5000) == "c1c8");
    return true;
}

bool CTestSearch::test_repeated_mate_in_one() {
    TEST_FUNCTION();
    // This test once raised assertions in the UCI-stresstest
    std::string mate_in_one = "startpos moves f2f3 e7e5 g2g4";
    constexpr int n_repetitions = 20;
    SILENT_EXPECT(board.set_fen_position(mate_in_one));
    CSearch recursive_search;
    for (int j = 1; j <= n_repetitions; ++j) {
        CTEST << "test_repeated_mate_in_one (recursive search): iteration " << j << " of " << n_repetitions << "\n";
        EXPECT(recursive_search.alpha_beta_negamax(2, 1, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta) > SCORE_HALF_KING);
    }
    CIterativeDeepening root_node_search;
    for (int j = 1; j <= n_repetitions; ++j) {
        CTEST << "test_repeated_mate_in_one (root-node search): iteration " << j << " of " << n_repetitions << "\n";
        EXPECT(root_node_search.search_depth(2) == "d8h4");
    }
    return true;
}

