#ifndef _SICKLD_H
#define _SICKLD_H

/**
 * \file 
 *
 * \author
 * \date
 */
#include <vector>
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic/Errors.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "sick-ld/SickLDConfiguration.h"

#include <sickld-1.0/SickLD.hh>
class Errors;
class LaserScannerConfiguration;
class SickLDConfiguration;
class LaserScannerData;
class LaserScannerDataWithIntensities;

/**
 * \brief 
 *
 */
class SickLD {
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

    double* ranges;

    double* rangeAngles;

    unsigned int* intensities;

};
#endif
