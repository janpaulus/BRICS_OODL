#ifndef _HOKUYOURG_H
#define _HOKUYOURG_H


#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic/Errors.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "hokuyo-urg/HokuyoURGConfiguration.h"

#include "UrgCtrl.h"
#include "RangeSensorParameter.h"
class Errors;
class LaserScannerConfiguration;
class HokuyoURGConfiguration;
class LaserScannerData;
class LaserScannerDataWithIntensities;

/**
 * \brief 
 *
 */
class HokuyoURG : public LaserScanner {
  public:
    HokuyoURG();

    virtual ~HokuyoURG();


  private:
    bool open(Errors& error);


  public:
    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool setConfiguration(const HokuyoURGConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(HokuyoURGConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice(Errors& error);


  private:
    LaserScannerConfiguration* config;

    bool isConnected;

    qrk::UrgCtrl hokuyo;

};
#endif
