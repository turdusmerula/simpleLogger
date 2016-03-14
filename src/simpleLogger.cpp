#include "simpleLogger.h"

#include <boost/log/core/core.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <ostream>

#include <atomic>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

// initialize and close logger
static simpleLogger _logger_ ;

class current_thread_id : public boost::log::attribute
{
public:
    //! A held attribute value type
    typedef unsigned long value_type ;

protected:
    static std::atomic_ulong next_threadid ;
    static thread_local unsigned long threadid ;

    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl : public boost::log::attribute_value::impl
    {
    public:
        bool dispatch(boost::log::type_dispatcher& dispatcher)
        {
        	boost::log::type_dispatcher::callback< value_type > callback=dispatcher.get_callback< value_type >() ;
            if (callback)
            {
            	callback(threadid);
                return true ;
            }
            else
                return false ;
        }

        boost::typeindex::type_index get_type() const { return boost::typeindex::type_id< value_type >(); }
    };
public:
    /*!
     * Default constructor
     */
    current_thread_id() : attribute(new impl())
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit current_thread_id(boost::log::attributes::cast_source const& source) :
        attribute(source.as< impl >())
    {
    }
} ;

std::atomic_ulong current_thread_id::next_threadid(0) ;
thread_local unsigned long current_thread_id::threadid=next_threadid.fetch_add(1, std::memory_order_relaxed) ;

BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logging::trivial::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", unsigned long)

BOOST_LOG_GLOBAL_LOGGER_INIT(logger, src::severity_logger_mt) {
    src::severity_logger_mt<boost::log::trivial::severity_level> logger;

    // add attributes
    logger.add_attribute("LineID", attrs::counter<unsigned int>(0));     // lines are sequentially numbered
    logger.add_attribute("TimeStamp", attrs::local_clock());             // each log line gets a timestamp
    logger.add_attribute("ThreadID", current_thread_id()) ;

    // add a text_ostream sink
    _logger_.console_sink = boost::make_shared<simpleLogger::text_sink>();

    // add "console" output stream to our sink
    _logger_.console_sink->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));

    // specify the format of the log message
    logging::formatter formatter = expr::stream
        << line_id
		<< " [" << thread_id << "]"
        << expr::format_date_time(timestamp, " %Y-%m-%d, %H:%M:%S.%f") << " "
        << "[" << logging::trivial::severity << "]"
        << expr::smessage;
    _logger_.console_sink->set_formatter(formatter);

    // only messages with severity >= SEVERITY_THRESHOLD are written
    _logger_.console_sink->set_filter(severity >= SEVERITY_THRESHOLD_CONSOLE);

    // "register" our sink
    logging::core::get()->add_sink(_logger_.console_sink);

    return logger;
}

simpleLogger::simpleLogger()
{

}

simpleLogger::~simpleLogger()
{
//	boost::log::sinks::asynchronous_sink::flush() ;
}
