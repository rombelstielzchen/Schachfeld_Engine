#pragma once

#ifndef DEBUG_LOG_ENABLE

#define DEBUG_SET_STREAM(stream) 
#define DEBUG_LOG_TO_FILE()
#define DEBUG_METHOD() 
#define DEBUG_MESSAGE(debug_message)
#define DEBUG_VALUE_OF(variable)

#else

#include <iostream>
#include <string>
#include <time.h>    

#define DEBUG_SET_STREAM(stream) {  CLog::set_stream(stream); }

#define DEBUG_LOG_TO_FILE() { CLog::log_to_file(); }

#define DEBUG_METHOD() CLog _debugLog(__FUNCTION__);

#define DEBUG_MESSAGE(debug_message) { _debugLog.message(debug_message); }

#define DEBUG_VALUE_OF(variable) { _debugLog.value_of(#variable, variable); }

class CLog {
  public:        // Constructor, Destructor
    CLog(const std::string& context);
    ~CLog();
  public:        // Methods
    static void log_to_file();
    void message(const std::string& message);
    template<class T> void value_of(const std::string& name, const T& value);
    static void set_stream(std::ostream& stream);
  private:    // Methods
    void write_indentation();
    std::ostream* safe_output_stream();
  private:    // Members
    static int indentation;
    const std::string context;
    clock_t start_time;
};

template<class T> void CLog::value_of(const std::string& name, const T& value) {
    write_indentation();
    *safe_output_stream() << name;
    *safe_output_stream() << "=[" << value << "]" << std::endl;
    // endl causes a flush, so all extra flushing removed
}

#endif

