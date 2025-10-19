#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>

class CVirtualExpert {
  public:
    virtual ~CVirtualExpert();
  public:
    void configure();
  private:
    // Mandatory methods, to be implemented by derived knowledge-experts
    virtual bool is_responsible() const = 0;
    virtual void apply_knowledge() = 0;
    virtual std::string get_name() const = 0;
};

