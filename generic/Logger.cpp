#include "generic/Logger.hpp"


Logger& Logger::getInstance()
{
  static Logger instance;
  return instance;
}

void Logger::init(){
#ifdef BOOST_LOG_FOUND
  // Initialize logging to std::cout
  logging::init_log_to_console(std::cout);
  // Initialize logging to the "test.log" file
  logging::init_log_to_file("log.txt");
#endif  /* BOOST_LOG_FOUND */
  
}

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
