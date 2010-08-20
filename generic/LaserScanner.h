#ifndef _LASERSCANNER_H
#define _LASERSCANNER_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <string>
#include "LaserScannerConfiguration.h"
#include "LaserScannerData.h"
#include "Errors.h"
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
