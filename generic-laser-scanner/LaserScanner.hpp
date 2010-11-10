#ifndef _LASERSCANNER_H
#define _LASERSCANNER_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <string>
#include "generic/Errors.hpp"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
class Errors;
class LaserScannerConfiguration;
class LaserScannerData;

class LaserScanner {
  public:
    virtual bool open(Errors& error) = 0;

    virtual bool close(Errors& error) = 0;

    virtual bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getData(LaserScannerData& data, Errors& error) = 0;

    virtual bool resetDevice(Errors& error) = 0;

};
#endif
