#pragma once

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

#ifndef DEBUG_LOG_ENABLE

#define DEBUG_USING_NAMESPACE

#define DEBUG_SET_STREAM(stream) 
#define DEBUG_METHOD() 
#define DEBUG_MESSAGE(debug_message)
#define DEBUG_VALUE_OF(variable) 

#else

#include <iostream>
#include <string>
#ifdef DEBUG_LOG_ENABLE_TIMING
#include <time.h>	
#endif

#define DEBUG_USING_NAMESPACE using namespace bornander::debug;

#define DEBUG_SET_STREAM(stream) { bornander:debug::log::set_stream(stream); }

#define DEBUG_METHOD() bornander::debug::log _debugLog(__FUNCTION__);

#define DEBUG_MESSAGE(debug_message) { _debugLog.message(debug_message); }

#define DEBUG_VALUE_OF(variable) { _debugLog.value_of(#variable, variable, false); }

namespace bornander
{
	namespace debug
	{
		enum list_segment
		{
			all,
			top,
			bottom
		};

		class log
		{
		private:	// Members
			static int indentation;
			static std::ostream* stream;

			const std::string context;

#ifdef DEBUG_LOG_ENABLE_TIMING
			const clock_t start_time;
#endif
		
		private:	// Methods
			void write_indentation();
			void write_indentation(const char prefix);
		public:		// Methods
			void message(const std::string& message);
			template<class T> void value_of(const std::string& name, const T& value, const bool outputTypeInformation);

			static void set_stream(std::ostream& stream);
		public:		// Constructor, Destructor
			log(const std::string& context);
			~log();
		};

		template<class T> void log::value_of(const std::string& name, const T& value, const bool outputTypeInformation)
		{
			write_indentation();
			*stream << name;
#ifdef DEBUG_LOG_ENABLE_TYPE_OUTPUT
			if (outputTypeInformation)
			{
				*stream << "(" << typeid(value).name() << ")";
			}
#endif
			*stream << "=[" << value << "]" << std::endl;
			stream->flush();
		}
	}
}

#endif

