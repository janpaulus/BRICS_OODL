/* 
 * File:   logger.h
 * Author: jan
 *
 * Created on September 1, 2010, 5:34 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

//#define BOOST_LOG_FOUND

#ifndef BOOST_LOG_FOUND
  #define LOG(level) std::cout
#endif  /* BOOST_LOG_FOUND */

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

  static src::severity_logger< severity_level > severityLogger;
  #define LOG(level) BOOST_LOG_STREAM_SEV(severityLogger, level)

#endif  /* BOOST_LOG_FOUND */


class Logger
{
private: 
  Logger() {}
  ~Logger() {} 
  Logger(const Logger &);             // intentionally undefined
  Logger & operator=(const Logger &); // intentionally undefined
 
 
public:
  static Logger &getInstance();
  void init();
};

#endif	/* LOGGER_H */

