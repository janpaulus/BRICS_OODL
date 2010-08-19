#ifndef _SICKLD_H
#define _SICKLD_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include "LaserScanner.h"

class Errors;
class LaserScannerConfiguration;
class SickLMS2xxConfiguration;
class LaserScannerData;
class LaserScannerDataWithIntensities;

/**
 * \brief 
 *
 */
class SickLD : public LaserScanner {
  public:
    SickLD();

    virtual ~SickLD();

    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool setConfiguration(const SickLMS2xxConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(SickLMS2xxConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice();


  private:
    bool open(Errors& error);

    LaserScannerConfiguration* config;

    bool isConnected;

    SickLMS* sick_lms;

};
#endif
