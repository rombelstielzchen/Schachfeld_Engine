#pragma once

#ifndef DEBUG_LOG_ENABLE

#define DEBUG_USING_NAMESPACE

#define DEBUG_SET_STREAM(stream) 
#define DEBUG_METHOD() 
#define DEBUG_MESSAGE(debug_message)
#define DEBUG_VALUE_OF(variable) 
//#define DEBUG_VALUE_AND_TYPE_OF(variable) 
//#define DEBUG_VALUE_OF_COLLECTION(variable)
//#define DEBUG_VALUE_OF_TOP_COLLECTION(variable, maxCount)
//#define DEBUG_VALUE_OF_BOTTOM_COLLECTION(variable, maxCount)
//#define DEBUG_VALUE_AND_TYPE_OF_COLLECTION(variable)
//#define DEBUG_VALUE_AND_TYPE_OF_TOP_COLLECTION(variable, maxCount)
//#define DEBUG_VALUE_AND_TYPE_OF_BOTTOM_COLLECTION(variable, maxCount)

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

//#define DEBUG_VALUE_AND_TYPE_OF(variable) { _debugLog.value_of(#variable, variable, true); }

//#define DEBUG_VALUE_OF_COLLECTION(variable)	{ _debugLog.value_of_collection(#variable, variable, 0, all, false); }

//
//#define DEBUG_VALUE_OF_TOP_COLLECTION(variable, maxCount) { _debugLog.value_of_collection(#variable, variable, maxCount, top, false); }

//#define DEBUG_VALUE_OF_BOTTOM_COLLECTION(variable, maxCount) { _debugLog.value_of_collection(#variable, variable, maxCount, bottom, false); }

//#define DEBUG_VALUE_AND_TYPE_OF_COLLECTION(variable) { _debugLog.value_of_collection(#variable, variable, 0, all, true); }

//#define DEBUG_VALUE_AND_TYPE_OF_TOP_COLLECTION(variable, maxCount) { _debugLog.value_of_collection(#variable, variable, maxCount, top, true); }

//#define DEBUG_VALUE_AND_TYPE_OF_BOTTOM_COLLECTION(variable, maxCount) { _debugLog.value_of_collection(#variable, variable, maxCount, bottom, true); }


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
//			template<class T> void value_of_collection(const std::string& name, const T& collection, const typename T::size_type max, const list_segment segment, const bool outputTypeInformation);

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

//		template<class T> void log::value_of_collection(const std::string& name, const T& collection, const typename T::size_type max, const list_segment segment, const bool outputTypeInformation)
//		{
//			const T::size_type limit = max != 0 ? std::min<T::size_type>(max, collection.size()) : collection.size();
//			
//			T::size_type startIndex = 0;
//			switch(segment)
//			{
//			case all:
//			case top:
//				startIndex = 0; 
//				break; 
//			case bottom:
//				startIndex = collection.size() - limit; 
//				break;
//			}
//
///			const T::size_type endIndex = startIndex + limit;
//
//			write_indentation();
//			*stream << "collection(" << name; 
//#ifdef DEBUG_LOG_ENABLE_TYPE_OUTPUT
//			if (outputTypeInformation)
//			{
//				*stream << "(" << typeid(collection).name() << ")";
//			}
//#endif
//			*stream << ", " << collection.size() << " items)" << std::endl; 
//			write_indentation();
//			*stream << "{" << std::endl;
//			
//			if (startIndex != 0)
//			{
//				write_indentation();
//				*stream << "   ..." << std::endl;
//			}
//
//			for(T::size_type i = startIndex; i < endIndex; ++i)
//			{
//				write_indentation();
//				*stream << "   [" << i << "]=[" << collection[i] << "]" << std::endl;
//			}
//
//			if (endIndex != collection.size())
//			{
//				write_indentation();
//				*stream << "   ..." << std::endl;
//			}
//
//			write_indentation();
//			*stream << "}" << std::endl;
//			stream->flush();
//
//		}
	}
}

#endif
