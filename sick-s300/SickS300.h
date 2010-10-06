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
#include "sick-s300/SickS300Configuration.h"

#include "ScannerSickS300.h"
class Errors;
class LaserScannerConfiguration;
class SickS300Configuration;
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

    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool setConfiguration(const SickS300Configuration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(SickS300Configuration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice(Errors& error);


private:
    bool open(Errors& error);

    // do in BOUML
    void receiveScan();

    LaserScannerConfiguration* config;

    bool isConnected;



    // do in BOUML

    boost::thread_group threads;

    boost::mutex mutex;
    boost::mutex mutexSickS300;


    std::vector<double> distance1;
    std::vector<double> angle1;
    std::vector<double> intensity1;

    std::vector<double> distance2;
    std::vector<double> angle2;
    std::vector<double> intensity2;

    std::vector<double>* pDistance;
    std::vector<double>* pAngle;
    std::vector<double>* pIntensity;

    volatile bool stopThread;
    ScannerSickS300* sickS300;




};
#endif
