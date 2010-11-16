/* 
 * File:   logger.h
 * Author: jan
 *
 * Created on September 1, 2010, 5:34 PM
 */

#ifndef OODL_LOGGER_H
#define	OODL_LOGGER_H

#include <iostream>

#define BOOST_LOG_FOUND
#ifdef BOOST_LOG_FOUND
#include <boost/log/utility/init/to_console.hpp>
#include <boost/log/utility/init/to_file.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/utility/init/from_stream.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/filters.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
//namespace flt = boost::log::filters;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

#endif  /* BOOST_LOG_FOUND */


namespace brics_oodl {

    enum severity_level {
        trace,
        debug,
        info,
        warning,
        oodl_exception,
        error,
        fatal
    };



#ifdef BOOST_LOG_FOUND
    static src::severity_logger< brics_oodl::severity_level > severityLogger;
    #define LOG(level) BOOST_LOG_STREAM_SEV(severityLogger, level)
#else
    #define LOG(level) std::cout
#endif  /* BOOST_LOG_FOUND */

    class Logger {
    private:

        Logger() {
            isInitialized = false;
        }

        ~Logger() {
        }
        Logger(const Logger &); // intentionally undefined
        Logger & operator=(const Logger &); // intentionally undefined

        bool isInitialized;
    public:
        static Logger &getInstance();
        void init();
    };

} // namespace brics_oodl

#endif	/* OODL_LOGGER_HPP */

