// Code taken from Fredrik Bornander, CodeProject. Thanks a lot!
//
// For the original code and docu see the docs directory.
// The directory working_simplified_demo compiles with g++ 11.4.0.
//Use the compiler-switch "-D DEBUG_LOG_ENABLE" to turn logging on
//
//Changes by Rombelstielzchen for the Schachfeld-engine:
// * code for exceptions removed (did not compile)
// * code for collections removed (did not compile)
// * files slightly renamed

#include "debug_log.h"

#if DEBUG_LOG_ENABLE

namespace bornander
{
	namespace debug
	{
		int log::indentation = 0;
		std::ostream* log::stream = &std::cout;

		log::log(const std::string& ctx)
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

		log::~log()
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

		void log::set_stream(std::ostream& stream)
		{
			log::stream = &stream;
		}


		void log::write_indentation()
		{
			write_indentation(' ');
		}

		void log::write_indentation(const char prefix)
		{
			*stream << prefix;
			for(int i = 0; i < indentation * 2; ++i)
			{
				*stream << " ";
			}
		}

		void log::message(const std::string& message)
		{
			write_indentation();
			*stream << message << std::endl;
			stream->flush();
		}

	}
}
#endif
