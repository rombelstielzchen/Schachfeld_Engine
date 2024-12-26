#pragma once

// Code based on the logging-framework by Fredrik Bornander
// https://www.codeproject.com/Articles/63736/Simple-debug-log-for-C
// CodeProject license
// 
// Lots of modifications for the Schachfeld chess-engine by Rombelstielzchen
// For the original code and some docu see the directory "docu_debug_log".
//
// Supported preprocessor-switches:
//    * DEBUG_LOG_ENABLE
//    * DEBUG_LOG_ENABLE_TIMING
//
// Provided macros: see below!
//
// DO NOT USE ANYTHING ELSE DIRECTLY!
// You would break macro-magic or initialization-order.

#ifndef DEBUG_LOG_ENABLE

#define DEBUG_SET_STREAM(stream) 
#define DEBUG_LOG_TO_FILE()
#define DEBUG_METHOD()
#define DEBUG_MESSAGE(debug_message)
#define DEBUG_VALUE_OF(variable)

#else

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>    

#define DEBUG_SET_STREAM(stream) {  set_stream(stream); }
#define DEBUG_LOG_TO_FILE() { log_to_file(); }
#define DEBUG_METHOD() CLog _debugLog(__FUNCTION__);
#define DEBUG_MESSAGE(debug_message) { message(debug_message); }
#define DEBUG_VALUE_OF(variable) { value_of(#variable, variable); }

inline int indentation = 0;
// Do not use these streams directly, use the wrapper!
// At startup they can be undefined due to initialization order!
// std::cout is only known at runtime!
inline std::ostream* debug_stream = &std::cout;
inline std::ofstream debug_file_stream;

inline std::ostream* safe_output_stream() {
    if (debug_stream != nullptr) {
        return debug_stream;
    }
    return &std::cout;
}

inline void set_stream(std::ostream& stream) {
	debug_stream = &stream;
}

template<class T> void value_of(const std::string& name, const T& value);

inline void write_indentation() {
	for(int i = 0; i < 2 * indentation; ++i) {
        *safe_output_stream() << " ";
	}
}

class CLog {
  public:
    CLog(const std::string& context);
    ~CLog();
    const std::string context;
    clock_t start_time;
};

template<class T> void value_of(const std::string& name, const T& value) {
    write_indentation();
    *safe_output_stream() << name;
    *safe_output_stream() << "=[" << value << "]" << std::endl;
    // endl causes a flush, so all extra flushing removed
}

inline void log_to_file() {
    debug_file_stream.open("debug.txt");
    set_stream(debug_file_stream);
}

inline void message(const std::string& message) {
	write_indentation();
	*safe_output_stream() << message << std::endl;
}

inline CLog::CLog(const std::string& ctx)	: context(ctx)
#ifdef DEBUG_LOG_ENABLE_TIMING
	, start_time(clock())
#endif
{
	write_indentation();
	*safe_output_stream() << "--> " << context << std::endl;
	++indentation;
}

inline CLog::~CLog() {
	--indentation;
	write_indentation();
	*safe_output_stream() << "<-- " << context;
#ifdef DEBUG_LOG_ENABLE_TIMING
	*safe_output_stream() << " in " << ((double)(clock() - start_time) / CLOCKS_PER_SEC) << "s";
#endif
	*safe_output_stream() << std::endl;
}

#endif

