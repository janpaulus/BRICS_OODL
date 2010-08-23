#ifndef _LASERSCANNERDATA_H
#define _LASERSCANNERDATA_H


#include <vector>
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

    void getRanges(std::vector< quantity<length> >& ranges, std::vector< quantity<plane_angle> >& range_angles) const;

    void setRanges(const std::vector< quantity<length> >& ranges, const std::vector< quantity<plane_angle> >& range_angles);

    void setRanges(double* ranges, unsigned int num_ranges, const boost::units::si::length& unit);

    void setRanges(unsigned int* ranges, unsigned int num_ranges, const boost::units::si::length& unit);

    quantity<si::time> getTimeStamp() const;

    void setNumMeasurementValues(const unsigned int& num_range_measurements_values);

    unsigned int getNumMeasurementValues();


  protected:
    std::vector< quantity<length> > _ranges;

    std::vector< quantity<plane_angle> > _range_angles;

    quantity<si::time> timestamp;

    unsigned int num_range_measurements;

};
#endif
