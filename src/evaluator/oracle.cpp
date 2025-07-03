// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "piece_square_value_tables.h"

bool is_endgame() {
    // TODO: move to CBoardLogic
    // TODO: proper implementation
    // TODO: test
    int n_officers = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            switch (board.get_square(j, k)) {
                case WHITE_KNIGHT:
                case WHITE_BISHOP:
                case WHITE_ROOK:
                case WHITE_QUEEN:
                case BLACK_KNIGHT:
                case BLACK_BISHOP:
                case BLACK_ROOK:
                case BLACK_QUEEN:
                    ++n_officers;
                    break;
            }
        }
    }
    assert(n_officers <= 14);
    return (n_officers <= 4);
}

void init_endgame_king() {
    // TODO: move to own class
    assign_psv_table(WHITE_KING, endgame_king_psv_table);
    normalize_average(main_piece_square_value_table_set[WHITE_KING], 20000);
    clone_from_white_to_black(BLACK_KING);

}

COracle::COracle() {
}

void COracle::configure_knowledge() {
    init_main_psv_set();
    if (is_endgame()) {
        init_endgame_king();
    }
}

