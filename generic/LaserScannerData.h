#ifndef _LASERSCANNERDATA_H
#define _LASERSCANNERDATA_H


#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>

using namespace std;
using namespace boost::units;
using namespace boost::units::si;
/**
 * \brief 
 *
 */
class LaserScannerData {
  public:
    LaserScannerData(const unsigned int& num_range_measurements_values);

    ~LaserScannerData();

    quantity<length> getRanges() const;

    unsigned int* getRangesPointer();

    quantity<si::time> getTimeStamp() const;

    void setNumMeasurementValues(const unsigned int& num_range_measurements_values);

    unsigned int getNumMeasurementValues();


  protected:
    unsigned int* ranges;

    quantity<si::time> timestamp;

    unsigned int num_range_measurements;

};
#endif
