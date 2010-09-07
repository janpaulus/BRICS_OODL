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
#include "generic/Units.h"
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
