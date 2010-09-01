#ifndef _LASERSCANNERCONFIGURATION_H
#define _LASERSCANNERCONFIGURATION_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <vector>
#include <iostream>
#include <string>
#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>

using namespace std;
using namespace boost::units;
using namespace boost::units::si;

typedef boost::units::make_scaled_unit<si::length, boost::units::scale<10, boost::units::static_rational<-3> > >::type millimeter;
//BOOST_UNITS_STATIC_CONSTANT(millimeters, millimeter);


enum baud_rate {
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_115200,
  BAUD_500K,
  BAUD_UNKNOWN

};
/**
 * \brief 
 *
 */
class LaserScannerConfiguration {
  public:
    LaserScannerConfiguration();

    virtual ~LaserScannerConfiguration();

    LaserScannerConfiguration(const LaserScannerConfiguration & source);

    virtual LaserScannerConfiguration & operator=(const LaserScannerConfiguration & source);

    /// Vendor name.
    std::string vendor;

    /// Product name.
    std::string product;

    /// Firmware version.
    std::string firmware;

    std::string protocol;

    std::string serialNumber;

    std::string model;

    quantity<plane_angle> scanAngleStart;

    quantity<plane_angle> scanAngleStop;

    quantity<plane_angle> scanResolution;

    quantity<length> minRangeDistance;

    quantity<length> maxRangeDistance;

    baud_rate baud;

    std::string devicePath;

};
#endif
