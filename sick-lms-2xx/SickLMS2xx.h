#ifndef _SICKLMS2XX_H
#define _SICKLMS2XX_H


#include "LaserScanner.h"
#include "SickLMS2xxConfiguration.h"

#include <string>
#include <vector>
#include "LaserScannerConfiguration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"
#include "Errors.h"
#include "sicklms-1.0/SickLIDAR.hh"
#include "sicklms-1.0/SickException.hh"
#include "sicklms-1.0/SickBufferMonitor.hh"
#include "sicklms-1.0/SickMessage.hh"
#include "sicklms-1.0/SickLMSBufferMonitor.hh"
#include "sicklms-1.0/SickLMSMessage.hh"
#include "sicklms-1.0/SickLMS.hh"
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
