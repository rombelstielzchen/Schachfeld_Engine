#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Purpose: updating some statistics frequently (once per second):
//   * principal variation
//   * hash full
// Most info gets sent by CSearchStatistics directly.

class CInfoThread {
  public:
    CInfoThread();
  private:
    static void thread_function();
  private:
    static void send_hash_statistics();
    static void send_principal_variation();
};

