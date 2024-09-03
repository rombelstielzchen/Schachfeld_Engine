#if DEBUG_LOG_ENABLE

#include "debug_log.h"
#include <fstream>

// Do not use this tream directly, use the wrapper!
// At sartup it can be undefined due to initialization order!
// std::cout is only known at runtime!
std::ostream* debug_stream = &std::cout;
std::ofstream debug_file_stream;
int CLog::indentation = 0;

CLog::CLog(const std::string& ctx)	: context(ctx)
#ifdef DEBUG_LOG_ENABLE_TIMING
	, start_time(clock())
#endif
{
	write_indentation();
	*safe_output_stream() << "--> " << context << std::endl;
	++indentation;
}

std::ostream* CLog::safe_output_stream() {
    if (debug_stream != nullptr) {
        return debug_stream;
    }
    return &std::cout;
}

CLog::~CLog() {
	--indentation;
	write_indentation();
	*safe_output_stream() << "<-- " << context;
#ifdef DEBUG_LOG_ENABLE_TIMING
	*safe_output_stream() << " in " << ((double)(clock() - start_time) / CLOCKS_PER_SEC) << "s";
#endif
	*safe_output_stream() << std::endl;
}

void CLog::set_stream(std::ostream& stream) {
	debug_stream = &stream;
}

void CLog::write_indentation() {
	for(int i = 0; i < 2 * indentation; ++i) {
        *safe_output_stream() << " ";
	}
}

void CLog::log_to_file() {
    debug_file_stream.open("debug.txt");
    set_stream(debug_file_stream);
}

void CLog::message(const std::string& message) {
	write_indentation();
	*safe_output_stream() << message << std::endl;
}

#endif

