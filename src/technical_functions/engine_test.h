#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CEngineTest {
  public:
     static void test_everything();
     inline static bool is_testing() { return testing; }
  private:
     static void test_thread_function();
  private:
     static bool testing;
};

