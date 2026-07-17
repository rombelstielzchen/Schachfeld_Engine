// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_evaluator.h"
#include "evaluator.h"
#include "score_constants.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseEvaluator> testcases_evaluator = {
   // Caveat! All evaluations are from whites point of view!
   // Hint: Add someextra-pieces  to enforce middle-game evaluations
   // First: material count, basic evaluation
    { "rrrrr///KPk w", "rrrrr///Kpk w" },
   // Kingside-structure, inspired by V_beinahe_9
    {"k///rrr/RRR/5PP/5P/6K w", "k/////6P/5P1P/6K w"},
    { "6k/5p1p/5p/rrr/RRR//K b", "6k/5p/5pp/rrr/RRR//K b"},
    // Central pawn structure: e4 + f4 / e5 + d6
    { "rrr/8/3p/4p/4PP///RRR w", "rrr/8/8/4p/4P///RRR w" },
    { "rrrrr/8/3p/8/4P w", "rrrrr/8/8/4p/4P w" },
    { "rrrrr/8/8/4p/4P w", "rrrrr/8/3p/4pP/4P w" },
    // Central pawn structure: e4 + d4 / e5 + d6
    { "rrrrr/8/3p/4p/3PP w", "rrrrr/8/8/4p/4P w" },
    { "rrrrr/8/8/4p/4P w", "rrrrr/8/3p/3Pp/4P w" },
    // Central pawn structure: e4 + d4 / d5 + e6
    { "rrrrr/8/4p/3p/3PP w", "rrrrr/8/8/3p/3P w" },
    { "rrrrr/8/3p/8/4P w", "rrrrr/8/8/4p/4P w" },
    { "rrrrr/8/4p/8/3P w", "rrrrr/8/4p/3pP/5P w" },
    // Central pawn structure: e4 + d4 / d5 + c6
    { "rrrrr/8/4p/2p/3PP w", "rrrrr/8/8/2p/3P w" },
    { "rrrrr/8/2p/8/3P w", "rrrrr/8/8/4p/4P w" },
    // Central pawn structure: c4 + d4 / d5 + c6
    { "rrrrr/8/2p/3p/2PP w", "rrrrr/8/8/3p/3P w" },
    { "rrrrr/8/2p/8/3P w", "rrrrr/8/2p/3p/2PP w" },
    // Central pawn structure: c4 + d4 / d5 + e6
    { "rrrrr/8/2p/3p/2PP w", "rrrrr/8/8/3p/3P w" },
    { "rrrrr/8/2p/8/3P w", "rrrrr/8/2p/3p/2PP w" },
    // Central pawn structure: c4 + d4 + c3 / c5 + d5 + e6
    { "rrrrr/8/4p/2ppP/3P/2P w", "rrrrr/8/4p/3pP/8/2P w" },
    { "rrrrr/8/4p/3pP/3P w", "rrrrr/8/4p/2ppP/3P/2P w" },
    // Central pawn structure: e4 / e5 + f5 + g6 (KID)
    { "rrrrr/8/6p/4pp/4P w", "rrrrr/8/8/4pp w" },
    // Central pawn structure: b4 + c5 + d5 / d6 (KID)
    { "rrrrr/8/8/2PP w", "rrrrr/8/3p/1pp w" },
    // Central pawn structure: c4 + d5 / d6+ e6 (Benoni)
    { "rrrrr/8/3pp/3P/2P w", "rrrrr/8/3p/3P w" },
    { "rrrrr/8/3p/3P w", "rrrrr/8/3p/8/2P w" },
    // Central pawn structure c3 or c2 / e5 (Ruy Lopez, Italian)
{ "rrrrr/8/8/8/3PP w", "rrrrr/8/8/4p/3PP/2P w" },
{ "rrrrr/8/8/8/3PP w", "rrrrr/8/8/4p/3PP/8/2P w" },
    // Pawns on 5th / 6th / 7th rank: semi-strong / monsters / potentially a bit weak
    { "rrrrr/8/PPPPPPPP w", "rrrrr/8/8/PPPPPPPP w" },
    { "rrrrr/8/PPPPPPPP w", "rrrrr/PPPPPPPP w" },
    // Pawns on 2nd / 3rd rank
    // 2nd rank is usuaööy better -- except d abd e file where they hinder development
    { "rrrrr/8/8/8/8/8/P w", "rrrrr/8/8/8/8/P w"},
    { "rrrrr/8/8/8/8/8/1P w", "rrrrr/8/8/8/8/1P w"},
    { "rrrrr/8/8/8/8/8/2P w", "rrrrr/8/8/8/8/2P w"},
    { "rrrrr/8/8/8/8/8/5P w", "rrrrr/8/8/8/8/5P w"},
    { "rrrrr/8/8/8/8/8/6P w", "rrrrr/8/8/8/8/6P w"},
    { "rrrrr/8/8/8/8/8/7P w", "rrrrr/8/8/8/8/7P w"},
    // Pawns on 2nd / 3rd rank, d and e file
    { "rrrrr/8/8/8/8/3P w", "rrrrr/8/8/8/8/8/3P w"},
    { "rrrrr/8/8/8/8/4P w", "rrrrr/8/8/8/8/8/4P w"},
    // Rook-Pawns: 3rd > 5th > 4th
    { "rrrrr/8/8/8/8/P w", "rrrrr/8/8/P w" },
    { "rrrrr/8/8/P w", "rrrrr/8/8/8/P w" },
    { "rrrrr/8/8/8/8/7P w", "rrrrr/8/8/7P w" },
    { "rrrrr/8/8/7P w", "rrrrr/8/8/8/7P w" },
    // Fianchetto
    { "rrrrr/8/8/8/8/5NP/5PKP w", "rrrrr/8/8/8/8/5NP/5P1P/6K w" },
    { "rrrrr/8/8/8/8/8/5PPP/6K w", "rrrrr/8/8/8/8/6P/5P1P/6K w" },
    { "rrrrr/8/8/8/8/6P/5PBP/6K w", "rrrrr/8/8/8/2B/8/6P/5PKP w" },
    { "rrrrr/8/8/8/2B/8/5PPP/6K w", "rrrrr/8/8/8/8/6P/5PBP/6K w" },
    // Bad exchange, protecting Bc4 by b3 instead of playing Bb3
    { "rrrrr/8/8/8/2B/1P/2P w", "rrrrr/8/8/8/8/1b/1PP w" },
    { "rrrrr/8/8/8/8/1P/1PP w", "rrrrr/8/8/8/2P/8/P1P w "},
    // Bad exchange, protecting Bf4 by g3 instead of playing Bg3
    { "rrrrr/8/8/8/8/6P/5PP w", "rrrrr/8/8/8/5P/8/5P1P w "},
    // Bad "active" queen-development to d3 in the opening
    { "rrrrr/8/8/8/8/8/8/3Q w", "rrrrr/8/8/8/8/3Q w" },
    // Capture away from the center with pawns on d2 / e2 for free piece-play
    { "rrrrr/////2P/PPP w", "rrrrr/////2P/P1PP w" },
    { "rrrrr/////5P/5PPP w", "rrrrr/////5P/4P1PP w" },
    // Pawn on d3 better then d2 for bettter development
   { "rrrrr/////3P w", "rrrrr//////3P w" },
   // Knights on the king-side more worth than on the queen-side:
   // Preparing castling, attacking / defending the king
   { "rrrrr/////5N w", "rrrrr/////2N w" },
   { "rrrrr//5N w", "rrrrr//2N w" },
    { "rrrrr////4N w", "rrrrr////3N w" },
    { "rrrrr///4N w", "rrrrr///3N w" },
    // Castling direction (white)
    { "kn/////BBB/PPP/2KR3R w", "kn/////BBB/PPP/R4RK w" },
    { "kn/////BBB/5PPP/R4RK w", "kn/////BBB/5PPP/2KR3R w",  },
    // Castling direction (black)
    { "r4rk1/PPP/BBB/////4KB b", "2kr3r/ppp/BBB/////4KB b" },
    { "2kr3r/5ppp/5bbb/////6BK b", "r4rk/5ppp/5bbb/////6BK b" },
    // Scandinavian: 3...Qa5 is better (for black) than Qe6
    { "rnb1kbnr/ppp1pppp/4q////PPPP1PPP/RNBQKBNR w", "rnb1kbnr/ppp1pppp//q///PPPP1PPP/RNBQKBNR w"} ,
    // TODO: remove, if we can't mate with depth 2
    // Mating with 2 bishops on very low depth. Good placement of the bishop that does not control the corner
///    { "k/2K///2BB b", "k/2K//4B/2B b" },
    // Mating with bishop and knight.
    // Prefer the bishop to control the bishop-colour; keep the knight away from the border
    { "/////5K/5N1B/5k b", "///4B//5K1N//5k b" },
};

bool CTestEvaluator::test_everything() {
    BEGIN_TESTSUITE("CTestEvaluator");
    EXPECT(test_equal_positions());
    EXPECT(test_decided_positions());
    EXPECT(test_move_sequence());
    EXPECT(test_black_advantage());
    EXPECT(test_pawn_values());
    EXPECT(test_positions());
    EXPECT(test_wood_points());
    return true;
}
bool CTestEvaluator::test_equal_positions() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(evaluates_approximately_to(0));
    return true;
}

bool CTestEvaluator::test_decided_positions() {
    TEST_FUNCTION();
    std::string decided_position = "1K/3q/1k b";
    EXPECT(board.set_fen_position(decided_position));
    board.evaluator.log_board_evaluation();//!!!
    EXPECT(board.evaluator.evaluate() < -500);
    return true;
}

bool CTestEvaluator::test_move_sequence() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.play_variation("e2e4 e7e5 g1f3");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("b8c6");
    EXPECT(board.evaluator.evaluate() >= 0);
    board.move_maker.play_variation("b1c3 g8f6");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.play_variation("f1b5");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("f8b4");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.make_move("e1g1");
    EXPECT(board.evaluator.evaluate() > 0);
    board.move_maker.make_move("e8g8");
    EXPECT(board.evaluator.evaluate() == 0);
    board.move_maker.unmake_all();
    EXPECT(board.evaluator.evaluate() == 0);
    return true;
}

bool CTestEvaluator::test_black_advantage() {
    TEST_FUNCTION();
    board.set_start_position();
    board.move_maker.play_variation("e2e4 e7e5 g1f3 g8f6 f3g1 f6e4");
    EXPECT(board.evaluator.evaluate() < -100);
    return true;
}

bool CTestEvaluator::test_pawn_values() {
    TEST_FUNCTION();
    // Logical consequences from more complex tests
    // 1) avoid bad central advances
    EXPECT(first_pawn_better(C4, C5));
    EXPECT(first_pawn_better(D4, D5));
    EXPECT(first_pawn_better(E4, E5));
    EXPECT(first_pawn_better(F4, F5));
    // Avoid bad exchanges of central pawn (for white)
    // Slav
    EXPECT(first_pawn_better(C4, C3));
    EXPECT(first_pawn_better(D4, C4));
    // Queens Gambit
    EXPECT(first_pawn_better(C4, E3));
    EXPECT(first_pawn_better(D4, C4));
    // Caro-Kann
    EXPECT(first_pawn_better(E4, C3));
    EXPECT(first_pawn_better(E4, D4));
    // French
    EXPECT(first_pawn_better(E4, E3));
    EXPECT(first_pawn_better(E4, D4)); 
    //  Scotch
    EXPECT(first_pawn_better(D4, D3));
    EXPECT(first_pawn_better(E4, D4));
    // Kings Gambit
    EXPECT(first_pawn_better(F4, D3));
    EXPECT(first_pawn_better(E4, F4));
    // Kings Indian (1)
    EXPECT(first_pawn_better(E4, F4));
    EXPECT(first_pawn_better(E4, G3));
    // Kings Indian (2)
    EXPECT(first_pawn_better(D3, B4));
    // Conflict: c2 > c4 > c5 > black c7 = c2
    //    EXPECT(first_pawn_better(C5, C2));
    EXPECT(first_pawn_better(C2, C5));
    // Benoni
    EXPECT(first_pawn_better(D5, E3));
    EXPECT(first_pawn_better(C4, E3));
    // Ruy Lopez / Italian
    EXPECT(first_pawn_better(E4, C3));
    EXPECT(first_pawn_better(E4, C2));
    // King-safety, actually testing F2/F3/G3 vs F2/G3/H2
    EXPECT(first_pawn_better(F3, H2));
    return true;
}

 bool CTestEvaluator::test_positions() {
    TEST_FUNCTION();
    for (const STestcaseEvaluator &testcase : testcases_evaluator) {
        SILENT_EXPECT(first_position_better(testcase));
    }
    return true;
}

bool CTestEvaluator::first_position_better(const std::string &first_fen, const std::string &second_fen) {
    SILENT_EXPECT(board.set_fen_position(first_fen));
    int first_value = board.evaluator.evaluate();
    board.evaluator.log_board_evaluation();
    CTEST << first_fen<< "    " << first_value << "\n";
    SILENT_EXPECT(board.set_fen_position(second_fen));
    int second_value = board.evaluator.evaluate();
    board.evaluator.log_board_evaluation();
    CTEST << second_fen << "    " << second_value << "\n";
    return first_value > second_value;
}

bool CTestEvaluator::first_position_better(const STestcaseEvaluator &testcase) {
    return first_position_better(testcase.better_position, testcase.worse_position);
}

bool CTestEvaluator::first_pawn_better(const SSquare first, const SSquare second) {
    int first_value = CEvaluator::evaluate_white_pawn(first);
    int second_value = CEvaluator::evaluate_white_pawn(second);
    return (first_value > second_value);
}

bool CTestEvaluator::evaluates_approximately_to(const int score) {
    int real_score = board.evaluator.evaluate();
    return (abs(real_score - score) < SCORE_HALF_PAWN);
}

bool CTestEvaluator::test_wood_points() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(board.evaluator.wood_points(WHITE_PLAYER) == 39);
    EXPECT(board.evaluator.wood_points(BLACK_PLAYER) == 39);
    EXPECT(board.evaluator.wood_points() == 0);
    return true;
}

