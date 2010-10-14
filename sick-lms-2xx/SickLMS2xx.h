#ifndef _SICKLMS2XX_H
#define _SICKLMS2XX_H


#include <string>
#include <vector>
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic/Errors.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "sick-lms-2xx/SickLMS2xxConfiguration.h"

#include "sicklms-1.0/SickLIDAR.hh"
#include "sicklms-1.0/SickException.hh"
#include "sicklms-1.0/SickBufferMonitor.hh"
#include "sicklms-1.0/SickMessage.hh"
#include "sicklms-1.0/SickLMSBufferMonitor.hh"
#include "sicklms-1.0/SickLMSMessage.hh"
#include "sicklms-1.0/SickLMS.hh"
class Errors;
class LaserScannerConfiguration;
class SickLMS2xxConfiguration;
class LaserScannerData;
class LaserScannerDataWithIntensities;

using namespace SickToolbox;
/**
 * \brief 
 *
 */
class SickLMS2xx : public LaserScanner {
  public:
    SickLMS2xx();

    virtual ~SickLMS2xx();

    bool open(Errors& error);

    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool setConfiguration(const SickLMS2xxConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(SickLMS2xxConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice(Errors& error);


  private:
    LaserScannerConfiguration* config;

    bool isConnected;

    SickLMS* sickLMS;

    unsigned int* ranges;

    double* rangeAngles;

    unsigned int* intensities;

};
#endif
