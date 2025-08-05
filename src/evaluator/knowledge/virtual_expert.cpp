// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "virtual_expert.h"
#include "../../technical_functions/debug_log.h"

CVirtualExpert::~CVirtualExpert() {
}

void CVirtualExpert::configure() {
    if (is_responsible()) {
        apply_knowledge();
    }
}

