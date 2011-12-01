#ifndef BRICS_OODL_SICKS300_H
#define BRICS_OODL_SICKS300_H


#include <vector>
#include <boost/thread.hpp>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Errors.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "ScannerSickS300.hpp"


namespace brics_oodl {

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

} // namespace brics_oodl
#endif
