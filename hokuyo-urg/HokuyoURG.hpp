#ifndef BRICS_OODL_HOKUYOURG_H
#define BRICS_OODL_HOKUYOURG_H


#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic-laser-scanner/LaserScanner.hpp"
#include "generic/Errors.hpp"
#include "generic-laser-scanner/LaserScannerData.hpp"
#include "generic-laser-scanner/LaserScannerDataWithIntensities.hpp"
#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "hokuyo-urg/HokuyoURGConfiguration.hpp"

#include "UrgCtrl.h"
#include "RangeSensorParameter.h"
namespace brics_oodl { class Errors; } 
namespace brics_oodl { class LaserScannerConfiguration; } 
namespace brics_oodl { class HokuyoURGConfiguration; } 
namespace brics_oodl { class LaserScannerData; } 
namespace brics_oodl { class LaserScannerDataWithIntensities; } 

namespace brics_oodl {

/**
 * \brief 
 *
 */
class HokuyoURG : public LaserScanner {
  public:
    HokuyoURG();

    virtual ~HokuyoURG();

    bool open(Errors& error);

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

} // namespace brics_oodl
#endif
