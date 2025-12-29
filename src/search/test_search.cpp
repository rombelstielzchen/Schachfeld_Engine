// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"test_search.h"
#include "iterative_deepening.h"
#include "search.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"
#include "../universal_chess_interface/command_interface.h"

const std::vector<STestcaseStaticExchangeEvaluation> testcases_static_exchange_evaluation = {
    // White to move
    { "/ w", A8, false },
    { "1R w", A8, false },
    { "1r w", A8, false },
    { "rR w", A8, true },
    
{ "rR b", B8, true },
    { "rRr w", A8, false },
    { "8/5ppp/5n/8/8/8/2B/1Q w", H7, true },
    { "8/5ppp/5n/8/8/8/2Q/1B w", H7, false },
    { "8/5ppp/5n/5B2////7R w", H7, true },
    { "8/8/5ppp/5n///7R/7R w", H7, false },
    { "8/5ppp/5n/5B2////7Q w", H7, true },
    { "8/5ppp/5n/5B1Q w", H7, true },
    { "rRrRrRrR w", A8, true },
    { "rRrRrRr w", A8, false },
    { "rRrrRRR w", A8, false },
    { "rRrRrRrR/r/R/r/R/r/R w", A8, true },
    { "rRrRrRrR/r/R/r/R/r/R/r w", A8, false  },
    // Black to move
    { "/ b", A8, false },
    { "1R b", A8, false },
    { "1r b", A8, false },
    { "rR b", B8, true },
    { "rRr b", B8, true },
    { "3q/3Q/3q/4Q/3q b", D7, true },
    // King in check, can capture
    { "K5Rk b", G8, true },
    // King in check, can not capture
    { "KR4Rk b", G8, false },
};

const std::vector<STestcaseSearch> testcases_search = {
    // Capturing the king
    { 1, "g7g8", "6k1/6Q1/6K1 w" },
    // Capturing the queen with royal fork and perpetual
    { 1, "f4g6", "2q2rk1/4qn1n/6q1/8/5N1q/8/7q/K w" },
    // King in check, must capture
    { 1, "h8g8", "K5Qk b" },
    // King in check, can and should capture
    { 1, "h8g8", "K5Rk b" },
    // King in check, must not capture
    { 1, "h8h7", "KR4Rk b" },
    // Capturing the queen with mate
    { 1, "b1h1", "7k/8/8/8/8/8/6R1/KR5q w" },
    // Black to move: capturing the queen with mate
    { 1, "c1h1", "7K/8/8/8/8/8/6r1/k1r4Q b" },
    // Two pawns under attack, one protected by recapture
    { 3, "d5e6", "8/1p6/2p1p3/3P3K////k w" },
    // Two knights under attack, one protected by recapture
    { 4, "a6a4", "8/6k1/R6n/8/n7/8/8/K7 w" }, 
    // Mate in 1, capturing the king in 3 plies
    // Follow-ups of the next, formerly failed testcase
    { 1, "h8b8", "1k5R/5R2//////K w" },
    { 1, "f7a7", "7R/k4R2//////K w" },
    { 1, "f7b7", "7R/1k3R2//////K w" },
    // Mate in 1, higher depths formerly failed
    { 1, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    { 2, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    { 3, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    // Mate in 2
    { 5, "a5b6", "k/7R//K w" },
    // Skewer
     { 3, "d8a5", "k2b4/8/8/8/8/2K5/8/4Q3 b" },
    // Royal fork for black, no capture at first move
    { 3, "d4c2", "8/8/8/8/3n4/8/8/Q3K2k b" },
    // Smothered mate, very basic
    { 4, "a2g8", "5r1k/6pp/7N/8/8/8/Q7/7K w" },
    // Requires static exchange evaluation and depth >= 2, more than root-node
    { 2, "e6a6", "8/5k2/n3R1b1/8/8/8/8/7K w" },
    { 2, "b8c8", "RRb/p2b w" },
    { 2, "a8a7", "RRb/p2b/4b w" },
    { 1, "d5e4", "q/Bq/2q/3q/4R/5Q/6Q/7Q b" },
    { 1, "d5e4", "q/1q/2q/3q/4R/5Q/6Q/7Q b" },
    { 2, "b7a7", "8/Bq/2q/3q/4R/5Q/6Q/7Q b" },
    { 2, "b7a7", "q/Bq/2q/3q/4R/5Q/6B/7Q b" },
    { 2, "c8d8", "rrrQRRR b" },
    { 2, "b8c8", "RRnq/2k4K w" },
    { 2, "c6b6", "B/1B/1pQ/3b/4b w" },
    // Former bug: counter-attacks in check
    { 4, "h8g8", "5q1k/1q3pp1/8/8/8/8/7Q/K6R b" },
    // Avoid stalemate
    { 4, "d4b6", "/k/p//3q//5Q/7K b" },
    // Various forms of "mate in 1", "loss in 1.5", "mate in 2", ...
    { 2, "h1h8", "k/pp//////K6R w" },
    { 3, "g2g8", "k6R/pp/////6r/K6R b" },
    { 4, "h1h8", "k/pp/////6r/K6R w" },
    { 5, "f3f8", "k5RR/pp////5r/5r/K b" },
    // "Too much depth" for mate
    { 3, "h1h8", "k/pp//////K6R w" },
    // Stalemate-sacrifice
    { 4, "h4f2", "/k/1q//7B///7K w" },
    // Preventing pawn-promotion, own stalemate
   { 4, "b8a8", "1k/P/1K b" },
   // Better mates: shorter
   { 4, "a6c8", "k/p1p/Qp/3K w" },
   // Better mates: less greedy
    { 2, "a1a8", "r3k2q/3ppp//////R3K2R w" },
    { 2, "h1h8", "q3k2r/3ppp//////R3K2R w" },
    // Better mates: sacrificing material, white and black to move
    { 4, "h2b8", "k6r/pp/N////6KQ w" },
    { 2, "f8f1", "1k3r2/8/7q/8/8/8/PP4B1/K7 b - - 0 1" },
    // Better mates: under-promotion
    { 2, "h7h8R", "k/3Q3P//////K w" },
    // Test for rescuing a knight from the corner
    { 4, "d5c6", "N6N///3k4////K7 b" },
    { 5, "a8c7", "N6N///3k4////K6N w" },
};

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
    EXPECT(test_go_movetime());
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
    EXPECT(searcher.search_movetime(1000) == "c1c8");
    return true;
}

