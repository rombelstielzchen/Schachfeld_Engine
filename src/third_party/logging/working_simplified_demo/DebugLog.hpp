#pragma once

#ifndef DEBUG_LOG_ENABLE

#define DEBUG_SET_STREAM(stream) 
#define DEBUG_METHOD() 
#define DEBUG_MESSAGE(debug_message)
//#define DEBUG_VALUE_AND_TYPE_OF_BOTTOM_COLLECTION(variable, maxCount)

#else

#include <iostream>
#include <string>
#include <vector>
#ifdef DEBUG_LOG_ENABLE_TIMING
#include <time.h>	
#endif

#define DEBUG_SET_STREAM(stream) { CLog::set_stream(stream); }

#define DEBUG_METHOD() CLog _debugLog(__FUNCTION__);

#define DEBUG_MESSAGE(debug_message) { _debugLog.message(debug_message); }

#define DEBUG_VALUE_OF(variable) { _debugLog.value_of(#variable, variable, false); }

class CLog
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
	CLog(const std::string& context);
	~CLog();
};

template<class T> void CLog::value_of(const std::string& name, const T& value, const bool outputTypeInformation)
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

#endif
