/* 
 * File:   logger.h
 * Author: jan
 *
 * Created on September 1, 2010, 5:34 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <iostream>

enum severity_level
{
    trace,
    debug,
    info,
    warning,
    oodl_exception,
    error,
    fatal
};

//#define BOOST_LOG_FOUND

#if BOOST_LOG_FOUND
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
#else
  #define LOG(level) std::cout
#endif  /* BOOST_LOG_FOUND */


class Logger
{
private: 
  Logger() {isInitialized = false;}
  ~Logger() {} 
  Logger(const Logger &);             // intentionally undefined
  Logger & operator=(const Logger &); // intentionally undefined
 
  bool isInitialized;
public:
  static Logger &getInstance();
  void init();
};

#endif	/* LOGGER_H */

