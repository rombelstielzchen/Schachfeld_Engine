#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>
#include <vector>

// Caveat! All evaluations are from whites point of view!
// Hint: Add some extra-pieces  to enforce middle-game evaluations

struct STestcaseEvaluator {
    std::string better_position;
    std::string worse_position;
};

typedef std::vector<STestcaseEvaluator> TTestcaseSetEvaluator;

/*** General **************************/

inline const TTestcaseSetEvaluator testcase_set_material_count = {
    // Fingle pieces
    { "///3K w", "///3Q w" },
    { "///3Q w", "///3R w" },
    { "///3R w", "///3B w" },
    { "///3B w", "///3N w" },
    { "///3N w", "///3P w" },
    { "///3P w", "///3 w" },
    { "///3 w", "///3p w" },
    { "///3p w", "///3n w" },
    { "///3n w", "///3b w" },
    { "///3b w", "///3r w" },
    { "///3r w", "///3q w" },
    { "///3q w", "///3k w" },
    // Pieces in the corner
    { "Q w", "/ w" },
    { "7R w", "/ w" },
    { "///////B w", "/ w" },
    { "///////7N w", "/ w" },
    };

/*** Pawn-structure *******************/

inline const TTestcaseSetEvaluator testcase_set_pawn_structure = {
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
    // Bad exchange, protecting Bc4 by b3 instead of playing Bb3
    { "rrrrr/8/8/8/2B/1P/2P w", "rrrrr/8/8/8/8/1b/1PP w" },
    { "rrrrr/8/8/8/8/1P/1PP w", "rrrrr/8/8/8/2P/8/P1P w "},
    // Bad exchange, protecting Bf4 by g3 instead of playing Bg3
    { "rrrrr/8/8/8/8/6P/5PP w", "rrrrr/8/8/8/5P/8/5P1P w "},
    // Capture away from the center with pawns on d2 / e2 for free piece-play
    { "rrrrr/////2P/PPP w", "rrrrr/////2P/P1PP w" },
    { "rrrrr/////5P/5PPP w", "rrrrr/////5P/4P1PP w" },
};

/*** Piece placement ******************/

inline const TTestcaseSetEvaluator testcase_set_castling_direction = {
    // Castling direction (white)
    { "kn/////BBB/PPP/2KR3R w", "kn/////BBB/PPP/R4RK w" },
    { "kn/////BBB/5PPP/R4RK w", "kn/////BBB/5PPP/2KR3R w",  },
    // Castling direction (black)
    { "r4rk1/PPP/BBB/////4KB b", "2kr3r/ppp/BBB/////4KB b" },
    { "2kr3r/5ppp/5bbb/////6BK b", "r4rk/5ppp/5bbb/////6BK b" },
};

inline const TTestcaseSetEvaluator testcase_set_piece_placement = {
   // Knights on the king-side more worth than on the queen-side
    { "startpos moves g1f3", "startpos moves b1c3" },
    { "startpos moves h2h3 b8c6", "startpos moves h2h3 g8f6" },
    // Knights on e4 / e5 better than d4 / d5
    { "rrrrr////4N w", "rrrrr////3N w" },
    { "rrrrr///4N w", "rrrrr///3N w" },
    // Bishop on d3 more worth than e3 for attack and castling
    { "rrrrr/////3B w", "rrrrr/////4B w" },
    // Scandinavian: 3...Qa5 is better (for black) than Qe6
    { "rnb1kbnr/ppp1pppp/4q////PPPP1PPP/RNBQKBNR w", "rnb1kbnr/ppp1pppp//q///PPPP1PPP/RNBQKBNR w"} ,
    // Bad "active" queen-development to d3 in the opening
    { "rrrrr/8/8/8/8/8/8/3Q w", "rrrrr/8/8/8/8/3Q w" },
};

inline const TTestcaseSetEvaluator testcase_set_pawn_placement = {
    // Pawns on 5th / 6th / 7th rank: semi-strong / monsters / potentially a bit weak
    { "rrrrr/8/PPPPPPPP w", "rrrrr/8/8/PPPPPPPP w" },
    { "rrrrr/8/PPPPPPPP w", "rrrrr/PPPPPPPP w" },
    // Pawns on 2nd / 3rd rank
    // 2nd rank is usually better -- except d and e file where they hinder development
    { "rrrrr/8/8/8/8/8/P w", "rrrrr/8/8/8/8/P w"},
    { "rrrrr/8/8/8/8/8/1P w", "rrrrr/8/8/8/8/1P w"},
    { "rrrrr/8/8/8/8/8/2P w", "rrrrr/8/8/8/8/2P w"},
    { "rrrrr/8/8/8/8/8/5P w", "rrrrr/8/8/8/8/5P w"},
    { "rrrrr/8/8/8/8/8/6P w", "rrrrr/8/8/8/8/6P w"},
    { "rrrrr/8/8/8/8/8/7P w", "rrrrr/8/8/8/8/7P w"},
    // Pawns on 2nd / 3rd rank, d and e file. 3rd better for development
    { "rrrrr/8/8/8/8/3P w", "rrrrr/8/8/8/8/8/3P w"},
    { "rrrrr/8/8/8/8/4P w", "rrrrr/8/8/8/8/8/4P w"},
    // Rook-Pawns: 3rd > 5th > 4th
    { "rrrrr/8/8/8/8/P w", "rrrrr/8/8/P w" },
    { "rrrrr/8/8/P w", "rrrrr/8/8/8/P w" },
    { "rrrrr/8/8/8/8/7P w", "rrrrr/8/8/7P w" },
    { "rrrrr/8/8/7P w", "rrrrr/8/8/8/7P w" },
};

inline const TTestcaseSetEvaluator testcase_set_fianchetto = {
    // King better on g2, if bishop missing
    { "rrrrr/8/8/8/8/5NP/5PKP w", "rrrrr/8/8/8/8/5NP/5P1P/6K w" },
    // Pawns on f2 / g2 / h2 better than fianchetto-hole
    { "rrrrr/8/8/8/8/8/5PPP/6K w", "rrrrr/8/8/8/8/6P/5P1P/6K w" },
    // Fianchetto-bishop better than bishop on c4 and fianchetto-hole
    { "rrrrr/8/8/8/8/6P/5PBP/6K w", "rrrrr/8/8/8/2B/8/6P/5PKP w" },
    // Bishop on c4 plus safe king even better than a fianchetto-position
    { "rrrrr/8/8/8/2B/8/5PPP/6K w", "rrrrr/8/8/8/8/6P/5PBP/6K w" },
};

/**************************************/

/*** Mating ***********************************/

inline const TTestcaseSetEvaluator testcase_set_mating = {
    // TODO: remove, if we can't mate with depth 2
    // Mating with 2 bishops on very low depth. Good placement of the bishop that does not control the corner
///    { "k/2K///2BB b", "k/2K//4B/2B b" },
    // Mating with bishop and knight.
    // Prefer the bishop to control the bishop-colour; keep the knight away from the border
    { "/////5K/5N1B/5k b", "///4B//5K1N//5k b" },
};

/*** Endgame **************************/

inline const TTestcaseSetEvaluator testcase_set_endgame_king = {
    { "k///3PK w", "k///3P///K w" },
    { "k///3p///K w", "///3pk///K w" },
    // king near "good" castling-squares g8 / g1
    { "k////4P//5K/ w", "k////3P///7K w" },
    { "6k//4p/////K w", "/5k/4p/////K w" },
};

const TTestcaseSetEvaluator testcase_set_endgame_pawn_advance = {
    { "k///1P////K w", "k//////1P/K w" },
    { "k///3p///K w", "k//////2p/K w" },
};

