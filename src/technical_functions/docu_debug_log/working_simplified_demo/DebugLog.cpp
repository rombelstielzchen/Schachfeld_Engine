#include "DebugLog.hpp"

#if DEBUG_LOG_ENABLE

int CLog::indentation = 0;
std::ostream* CLog::stream = &std::cout;

CLog::CLog(const std::string& ctx)
	: context(ctx)
#ifdef DEBUG_LOG_ENABLE_TIMING
	, start_time(clock())
#endif
{
	write_indentation();
	*stream << "--> " << context << std::endl;
	++indentation;
	stream->flush();
}

CLog::~CLog()
{
	--indentation;
	write_indentation(' ');
	*stream << "<-- " << context;
#ifdef DEBUG_LOG_ENABLE_TIMING
	*stream << " in " << ((double)(clock() - start_time) / CLOCKS_PER_SEC) << "s";
#endif
	*stream << std::endl;
	stream->flush();
}

void CLog::set_stream(std::ostream& stream)
{
	CLog::stream = &stream;
}

void CLog::write_indentation()
{
	write_indentation(' ');
}

void CLog::write_indentation(const char prefix)
{
	*stream << prefix;
	for(int i = 0; i < indentation * 2; ++i)
	{
		*stream << " ";
	}
}

void CLog::message(const std::string& message)
{
	write_indentation();
	*stream << message << std::endl;
	stream->flush();
}

#endif
