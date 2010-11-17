#ifndef BRICS_OODL_TIME_HPP
#define BRICS_OODL_TIME_HPP

#include <boost/thread.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

namespace brics_oodl {

#define SLEEP_MILLISEC(millisec) boost::this_thread::sleep(boost::posix_time::milliseconds((millisec)));

#define SLEEP_SEC(sec) boost::this_thread::sleep(boost::posix_time::seconds((sec)));


} // namespace brics_oodl
#endif //BRICS_OODL_TIME_HPP
