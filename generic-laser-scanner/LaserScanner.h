#ifndef _LASERSCANNER_H
#define _LASERSCANNER_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <string>
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic/Errors.h"
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

    /// @brief Close the connection to the laser scanner.
    virtual bool close(Errors& error) = 0;

    /**
     * 
     */
    virtual bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getData(LaserScannerData& data, Errors& error) = 0;

    virtual bool resetDevice() = 0;

};
#endif
