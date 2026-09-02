// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_search.h"

const std::vector<STestcaseSearch> testcases_search = {
    //*** Basic check-handling *********
    // Capturing the king
    { 1, "g7g8", "6k1/6Q1/6K1 w" },
    // King in check, must capture
    { 1, "h8g8", "K5Qk b" },
    // King in check, can and should capture
    { 1, "h8g8", "K5Rk b" },
    // King in check, must not capture
    { 1, "h8h7", "KR4Rk b" },
    //*** Basic captures ***************
    // Capturing the queen with royal fork and perpetual
    { 1, "f4g6", "2q2rk1/4qn1n/6q1/8/5N1q/8/7q/K w" },
    // Capturing the queen with mate
    { 1, "b1h1", "7k/8/8/8/8/8/6R1/KR5q w" },
    // Black to move: capturing the queen with mate
    { 1, "c1h1", "7K/8/8/8/8/8/6r1/k1r4Q b" },
    //*** More advanced captures *******
    // Two pawns under attack, one protected by recapture
    { 3, "d5e6", "8/1p6/2p1p3/3P3K////k w" },
    // Two knights under attack, one protected by recapture
    { 4, "a6a4", "8/6k1/R6n/8/n7/8/8/K7 w" }, 
    //*** Basic mates ******************
    // Mate in 1, capturing the king in 3 plies
    //*** Follow-ups from failed tests *
    { 1, "h8b8", "1k5R/5R2//////K w" },
    { 1, "f7a7", "7R/k4R2//////K w" },
    { 1, "f7b7", "7R/1k3R2//////K w" },
    // Mate in 1, higher depths formerly failed
    { 1, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    { 2, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    { 3, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    //*** More advanced mates ***********
    // Mate in 2
    { 5, "a5b6", "k/7R//K w" },
    // Smothered mate, very basic
    { 4, "a2g8", "5r1k/6pp/7N/8/8/8/Q7/7K w" },
    //*** Tactics ************
    // Skewer
     { 3, "d8a5", "k2b4/8/8/8/8/2K5/8/4Q3 b" },
    // Royal fork for black, no capture at first move
    { 3, "d4c2", "8/8/8/8/3n4/8/8/Q3K2k b" },
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

    //!!!
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
    { 2, "g7g8R", "k/3Q2P//////K w" },
    // Test for trapping / rescuing a knight from the corner
    { 4, "d5c6", "N6N///3k4////K7 b" },
    { 2, "a8c7", "N6N///3k4////K6N w" },
    { 2, "h8f7", "N6N///4k3////K6N w" },
    { 2, "a1b3", "N6N////3k4///N6K w" },
    { 2, "h1g3", "N6N////4k3///K6N w" },
    { 2, "h1g3", "7N/N///4k3///K6N w" },
    { 2, "a1h8", "N///////Bk5K w" },
    // Mate with a single rook, boxing in the enemy king
    { 2, "a8a4", "R//3K//4k w" },
    { 2, "a8a5", "RK////7k w" },
    { 2, "h5e5", "///7R/3k1K2/// w" },
    // Mate with a single rook; good waiting-moves before mate, identical for black and white
    { 2, "c7c6", "1k/2R/1K w"},
    { 2, "c7c6", "1K/2r/1k b" },
    { 2, "f2f3", "/////6K/5R/6k w" },
    { 2, "f2f3", "/////6k/5r/6K b" },
    // Mate with a single rook
    // Stay close, when own king is nearby, otherwise go for a distant vertical cutoff
    { 2, "e6h6", "//4R/3k////7K w" },
    { 2, "e6e4", "//4R/3k//5K// w" },
    { 2, "c5c6", "k//1R/2K w" },
    // Mate with 2 rooks
    { 2, "h3h5", "///5K/r/7r//k b" },
    { 2, "h4h6", "//3K/r/7r///k b" },
    { 2, "a1h1", "///3K/r//k/r b"},
    // Mate with 2 bishops
    { 2, "f1a6", "///////BK3Bk w" },
    { 2, "f1g2", "k/2K//2B////5B w" },
    { 2, "d6c5", "/k1K/3B/////5B w" },
    { 2, "c6b6", "1k/4B/2K1B w" },
    { 2, "e6c8", "/k3B/2K1B w" },
    { 2, "c4a6", "1K1b//2k//2b b" },
    { 2, "f4e5", "//7B/2k/5K///7B w" },
    { 2, "f4e5", "//7b/2K/5k///7b b" },
    // TODO: sort tests below
    // Positional king-play in the endgame
    { 1, "g2f3", "k/P/////6K w" },
    { 1, "b2c3", "k/P/////1K w" },
    { 1, "g7f6", "/6k/////pK b" },
    { 1, "b7c6", "/1k/////pK b" },
};

