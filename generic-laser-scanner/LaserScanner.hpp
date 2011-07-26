#ifndef BRICS_OODL_LASERSCANNER_H
#define BRICS_OODL_LASERSCANNER_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <string>
#include "Errors.hpp"
#include "Logger.hpp"
#include "Units.hpp"
#include "LaserScannerConfiguration.hpp"
#include "LaserScannerData.hpp"
#include "LaserScannerDataWithIntensities.hpp"
namespace brics_oodl { class Errors; } 
namespace brics_oodl { class LaserScannerConfiguration; } 
namespace brics_oodl { class LaserScannerData; } 

namespace brics_oodl {

class LaserScanner {
  public:
    virtual bool open(Errors& error) = 0;

    virtual bool close(Errors& error) = 0;

    virtual bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error) = 0;

    virtual bool getData(LaserScannerData& data, Errors& error) = 0;

    virtual bool resetDevice(Errors& error) = 0;

};

} // namespace brics_oodl
#endif
