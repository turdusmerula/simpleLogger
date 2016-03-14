#ifndef _SIMPLELOGGER_SIMPLELOGGER_H_
#define _SIMPLELOGGER_SIMPLELOGGER_H_

//#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

// just log messages with severity >= SEVERITY_THRESHOLD are written
#define SEVERITY_THRESHOLD_CONSOLE logging::trivial::debug

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

// just a helper macro used by the macros below - don't use it in your code
#define LOG(severity) BOOST_LOG_SEV(logger::get(),boost::log::trivial::severity)

// ===== log macros =====
#define LOG_TRACE_0()   LOG(trace) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), "
#define LOG_TRACE_1(A)   LOG(trace) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), " << A << ", "
#define LOG_TRACE_X(x,A,FUNC, ...)  FUNC
#define LOG_TRACE(...)	LOG_TRACE_X(,##__VA_ARGS__, LOG_TRACE_1(__VA_ARGS__), LOG_TRACE_0(__VA_ARGS__))

#define LOG_DEBUG_0()   LOG(debug) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), "
#define LOG_DEBUG_1(A)   LOG(debug) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), " << A << ", "
#define LOG_DEBUG_X(x,A,FUNC, ...)  FUNC
#define LOG_DEBUG(...)	LOG_DEBUG_X(,##__VA_ARGS__, LOG_DEBUG_1(__VA_ARGS__), LOG_DEBUG_0(__VA_ARGS__))

#define LOG_INFO_0()   LOG(info) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), "
#define LOG_INFO_1(A)   LOG(info) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), " << A << ", "
#define LOG_INFO_X(x,A,FUNC, ...)  FUNC
#define LOG_INFO(...)	LOG_INFO_X(,##__VA_ARGS__, LOG_INFO_1(__VA_ARGS__), LOG_INFO_0(__VA_ARGS__))

#define LOG_WARNING_0()   LOG(warning) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), "
#define LOG_WARNING_1(A)   LOG(warning) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), " << A << ", "
#define LOG_WARNING_X(x,A,FUNC, ...)  FUNC
#define LOG_WARNING(...)	LOG_WARNING_X(,##__VA_ARGS__, LOG_WARNING_1(__VA_ARGS__), LOG_WARNING_0(__VA_ARGS__))

#define LOG_ERROR_0()   LOG(error) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), "
#define LOG_ERROR_1(A)   LOG(error) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), " << A << ", "
#define LOG_ERROR_X(x,A,FUNC, ...)  FUNC
#define LOG_ERROR(...)	LOG_ERROR_X(,##__VA_ARGS__, LOG_ERROR_1(__VA_ARGS__), LOG_ERROR_0(__VA_ARGS__))

#define LOG_FATAL_0()   LOG(fatal) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), "
#define LOG_FATAL_1(A)   LOG(fatal) << "(" << boost::filesystem::path(__FILE__).filename() << ":" << __LINE__ << "), " << A << ", "
#define LOG_FATAL_X(x,A,FUNC, ...)  FUNC
#define LOG_FATAL(...)	LOG_FATAL_X(,##__VA_ARGS__, LOG_FATAL_1(__VA_ARGS__), LOG_FATAL_0(__VA_ARGS__))

class simpleLogger
{
public:
	simpleLogger() ;

	~simpleLogger() ;

    using text_sink = boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> ;
	boost::shared_ptr<text_sink> console_sink ;
} ;

#endif
