#pragma once

#include <sstream>
#include <string>

//namespace rombel_std {

    void replace_tabs_by_spaces(std::string &in_out_string);

    void trim_left(std::string &in_out_string);

    void trim_right(std::string &in_out_string);
    
    void trim(std::string &in_out_string);

    class CStringTokenizer {
      public:
        CStringTokenizer(const std::string input);
        std::string next_token();
      private:
        std::istringstream input_stream;
    };
//}
