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
// iCompletely rewritten for the Schachfeld chess-engine.
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

#define DEBUG_MESSAGE(text__linebreak_appended_automatically)
#define DEBUG_METHOD()
#define DEBUG_VALUE_OF(object)
#define DEBUG_LOG_TO_FILE()
#define DEBUG_REDIRECT_TO_STREAM(stream) 
#define DEBUG_ALWAYS_FLUSH_BUFFER()

#else

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>    

#define DEBUG_MESSAGE(debug_message) { ____message(text__linebreak_appended_automatically); }

#define DEBUG_METHOD() CLog _debugLog(__FUNCTION__);

#define DEBUG_VALUE_OF(object) { ____value_of(#object, object); }

#define DEBUG_LOG_TO_FILE() { ____log_to_file(); }

#define DEBUG_REDIRECT_TO_STREAM(stream) {  ____redirect_to_stream(stream); }

#define DEBUG_ALWAYS_FLUSH_BUFFER() { ___always_flush_buffer(); }

inline bool flush_buffer = false;
inline int indentation = 0;
// Do not use these streams directly!
// At startup they can be undefined due to order initializationr!
// std::cout is only known at runtime!
inline std::ostream* debug_stream = &std::cout;
inline std::ofstream debug_file_stream;

inline void ___always_flush_buffer() {
    flush_buffer = true;
}

inline std::ostream* ____safe_logging_stream() {
    if (debug_stream != nullptr) {
        return debug_stream;
    }
    return &std::cout;
}

inline void ____redirect_to_stream(std::ostream &stream) {
	debug_stream = &stream;
}

template<class T> void ____value_of(const std::string &name, const T &value);

class CLog {
    // This class provides via its destructor:
    //   * an automatic end-of-function-message
    //   * optional timing
  public:
    CLog(const std::string &context);
    ~CLog();
  private:
    const std::string context;
    clock_t start_time;
};

#ifdef _WIN32

#include <windows.h>
#include "shlobj_core.h"

inline std::wstring const debug_filename() {
    std::wstring debug_path = L".";
    PWSTR p_desktop_path;
    if (SHGetKnownFolderPath(FOLDERID_Desktop, 0, 0, &p_desktop_path) == S_OK) {
        debug_path = p_desktop_path;
    }
    // The calling process is responsible for freeing this resource once it is no longer needed 
    // by calling CoTaskMemFree, whether SHGetKnownFolderPath succeeded or not. 
    CoTaskMemFree(p_desktop_path);
    debug_path += L"/debug-txt";
    return debug_path;
}

#else

inline std::string debug_filename() {
    const std::string filename = "./debug.txt";
    return filename;
}

#endif

inline void ____log_to_file() {
    debug_file_stream.open(debug_filename());
    ____redirect_to_stream(debug_file_stream);
}

inline void ____message(const std::string &text__linebreak_appended_automatically) {
    int indentation_width = 2 * indentation;
    std::string indented_message = std::string(indentation_width, ' ') + text__linebreak_appended_automatically + "\n";
	*____safe_logging_stream() << indented_message;
    if (flush_buffer) {
        std::flush(*____safe_logging_stream());
    }
}

template<class T> void ____value_of(const std::string &name, const T &value) {
    std::string text = name + "=[" + value + "]";
    ____message(text);
}

inline CLog::CLog(const std::string &ctx) : context(ctx)
#ifdef DEBUG_LOG_ENABLE_TIMING
	, start_time(clock())
#endif
{
    std::string text = "--> " + context;
    ____message(text);
	++indentation;
}

inline CLog::~CLog() {
	--indentation;
    std::string text = "<-- " + context;
#ifdef DEBUG_LOG_ENABLE_TIMING
	text += < " in " + (static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC) + "s";
#endif
    ____message(text);
}

#endif
