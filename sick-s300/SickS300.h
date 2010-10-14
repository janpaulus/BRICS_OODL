#ifndef _SICKS300_H
#define _SICKS300_H


#include <vector>
#include <boost/thread.hpp>
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-laser-scanner/LaserScanner.h"
#include "generic/Errors.h"
#include "generic-laser-scanner/LaserScannerData.h"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.h"
#include "generic-laser-scanner/LaserScannerConfiguration.h"

#include "ScannerSickS300.h"
class Errors;
class LaserScannerConfiguration;
class LaserScannerData;
class LaserScannerDataWithIntensities;

/**
 * \brief 
 *
 */
class SickS300 : public LaserScanner {
  public:
    SickS300();

    virtual ~SickS300();

    bool open(Errors& error);

    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice(Errors& error);


  private:
    void receiveScan();

    static const unsigned int numberOfScanPoints = 541;

    //in milliseconds
    static const unsigned int timeTillNextPollForData = 20;

    LaserScannerConfiguration* config;

    bool isConnected;

    ScannerSickS300* sickS300;

    std::vector<double> distanceBufferOne;

    std::vector<double> angleBufferOne;

    std::vector<double> intensityBufferOne;

    std::vector<double> distanceBufferTwo;

    std::vector<double> angleBufferTwo;

    std::vector<double> intensityBufferTwo;

    volatile bool stopThread;

    volatile bool newDataFlagOne;

    volatile bool newDataFlagTwo;

    boost::thread_group threads;

    boost::mutex mutexData1;

    boost::mutex mutexData2;

    boost::mutex mutexSickS300;

};
#endif
