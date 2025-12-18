#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
//
// Code inspired by the logging-framework of Fredrik Bornander
// https://www.codeproject.com/Articles/63736/Simple-debug-log-for-C
// under the CodeProject license
// 
// Completely rewritten for the Schachfeld chess-engine.
// For the original code and some docu see the directory "docu_debug_log".
//
// Supported preprocessor-switches:
//    * DEBUG_LOG_ENABLE
//    * DEBUG_LOG_ENABLE_TIMING
//
// Provided macros: see below!
//
// DO NOT USE ANYTHING ELSE DIRECTLY!
// You would break macro-magic or mess up the order of initialization.

#ifndef DEBUG_LOG_ENABLE

#define  SWITCH_DEBUG_ON(discarded_bool);
#define DEBUG_MESSAGE(discarded_text)
#define DEBUG_METHOD()
#define DEBUG_VALUE_OF(discarded_object)
#define DEBUG_LOG_TO_FILE()
#define DEBUG_REDIRECT_TO_STREAM(unused_stream) 
#define DEBUG_ALWAYS_FLUSH_BUFFER()

#else

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

#define SWITCH_DEBUG_ON(on_off) { rombel::switch_debug_on(on_off); }

#define DEBUG_MESSAGE(...) { rombel::message(__VA_ARGS__); }

#define DEBUG_METHOD() rombel::CLog helper_object(__FUNCTION__);

#define DEBUG_VALUE_OF(object) { rombel::value_of(#object, object); }

#define DEBUG_LOG_TO_FILE() { rombel::log_to_file(); }

#define DEBUG_REDIRECT_TO_STREAM(stream) { rombel::redirect_to_stream(&stream); }

#define DEBUG_ALWAYS_FLUSH_BUFFER() { rombel::always_flush_buffer(); }

namespace rombel {

inline bool debug_on_off = false;
inline bool flush_buffer = false;
inline int indentation = 0;
// Do not use these streams directly!
// At startup they can be undefined due to order initialization!
// std::cout is only known at runtime!
inline std::ostream *debug_stream = &std::cout;
inline std::ofstream debug_file_stream;

inline void switch_debug_on(bool on_off) {
    debug_on_off = on_off;
}

inline void always_flush_buffer() {
    flush_buffer = true;
}

inline std::ostream* safe_logging_stream() {
    if (debug_stream != nullptr) {
        return debug_stream;
    }
    return &std::cout;
}

inline void redirect_to_stream(std::ostream &stream) {
	debug_stream = &stream;
}

template<class T> void value_of(const std::string &name, const T &value);

class CLog {
    // This class provides via its destructor:
    //   * an automatic end-of-function-message
    //   * optional timing
    //   * decreased indentation
  public:
    CLog(const std::string &context);
    ~CLog();
  private:
    const std::string context;
    clock_t start_time;
};

#ifdef _WIN32

inline std::string const debug_filename() {
    std::string filename = "%USERPROFILE%\\Desktop\\debug.txt";
    return filename;
}

#else

inline std::string debug_filename() {
    const std::string filename = "./debug.txt";
    return filename;
}

#endif

inline void log_to_file() {
    debug_file_stream.open(debug_filename());
    redirect_to_stream(debug_file_stream);
}

inline void log_variadic_helper() {}

template<typename First, typename ...Rest>
inline void log_variadic_helper(First && first, Rest && ...rest) {
    // Sending variadic arguments to the output stream, bit by bit
    // https://stackoverflow.com/questions/29326460/how-to-make-a-variadic-macro-for-stdcout
    *safe_logging_stream() << std::forward<First>(first);
    log_variadic_helper(std::forward<Rest>(rest)...);
}

template<typename First, typename ...Rest>
inline void message(First && first, Rest && ...rest) {
    if (debug_on_off == false) {
        return;
    }
    int indentation_width = 2 * indentation;
    std::string leading_spaces = std::string(indentation_width, ' ');
    log_variadic_helper(leading_spaces, first, std::forward<Rest>(rest)..., "\n");
    if (flush_buffer) {
        std::flush(*rombel::safe_logging_stream());
    }
}

template<class T> void rombel::value_of(const std::string &name, const T &value) {
    if (debug_on_off == false) {
        return;
    }
    std::string text = name + "=[" + value + "]";
    message(text);
}

inline CLog::CLog(const std::string &ctx) : context(ctx)
#ifdef DEBUG_LOG_ENABLE_TIMING
	, start_time(clock())
#endif
{
    if (debug_on_off == false) {
        return;
    }
    std::string text = "--> " + context;
    message(text);
	++indentation;
}

inline CLog::~CLog() {
    if (debug_on_off == false) {
        return;
    }
	--indentation;
    std::string text = "<-- " + context;
#ifdef DEBUG_LOG_ENABLE_TIMING
	text += < " in " + (static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC) + "s";
#endif
    message(text);
}

};

#endif

