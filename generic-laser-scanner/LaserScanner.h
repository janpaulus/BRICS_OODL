#ifndef _LASERSCANNER_H
#define _LASERSCANNER_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <string>
#include "generic/Errors.h"
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
class Errors;
class LaserScannerConfiguration;
class LaserScannerData;

/**
 * \brief 
 *
 */
class LaserScanner {
  public:
    LaserScanner();

    virtual ~LaserScanner();

    virtual bool open(Errors& error) = 0;

    /// @brief Close the connection to the laser scanner.
    virtual bool close(Errors& error) = 0;

    /**
     * 
     */
    virtual bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getData(LaserScannerData& data, Errors& error) = 0;

    virtual bool resetDevice(Errors& error) = 0;

};
#endif
