/* 
 * File:   logger.h
 * Author: jan
 *
 * Created on September 1, 2010, 5:34 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

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

// We define our own severity levels
enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};

/*
void init()
{
    logging::init_log_to_file
    (
        keywords::file_name = "sample_%N.log",                  // file name pattern
        keywords::rotation_size = 10 * 1024 * 1024,             // rotate files every 10 MiB...
                                                                // ...or at midnight
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%]: %_%"                 // log record format
    );

    logging::core::get()->set_filter
    (
        flt::attr< logging::trivial::severity_level >("Severity") >= logging::trivial::info
    );
}

  // Read logging settings from a file
  //  std::ifstream file("log_settings.ini");
 //   logging::init_from_stream(file);
      // Initialize logging to std::cout
    logging::init_log_to_console(std::cout);
    // Initialize logging to the "test.log" file
    logging::init_log_to_file("log.txt");



*/

#endif	/* LOGGER_H */

