#ifndef BRICS_OODL_SICKLMS2XX_H
#define BRICS_OODL_SICKLMS2XX_H


#include <string>
#include <vector>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Errors.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "SickLMS2xxConfiguration.hpp"

#include "sicklms-1.0/SickLIDAR.hh"
#include "sicklms-1.0/SickException.hh"
#include "sicklms-1.0/SickBufferMonitor.hh"
#include "sicklms-1.0/SickMessage.hh"
#include "sicklms-1.0/SickLMSBufferMonitor.hh"
#include "sicklms-1.0/SickLMSMessage.hh"
#include "sicklms-1.0/SickLMS.hh"
using namespace SickToolbox;
namespace brics_oodl {

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

} // namespace brics_oodl
#endif
