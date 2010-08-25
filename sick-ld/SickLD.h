#ifndef _SICKLD_H
#define _SICKLD_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include "Errors.h"
#include "LaserScannerConfiguration.h"
#include "SickLDConfiguration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "LaserScanner.h"

#include <vector>
#include <sickld-1.0/SickLD.hh>
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

    bool setConfiguration(const SickLDConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(SickLDConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice();


  private:
    bool open(Errors& error);

    LaserScannerConfiguration* config;

    bool isConnected;

    SickToolbox::SickLD* sickLD;

};
#endif
