#ifndef _HOKUYOURG_H
#define _HOKUYOURG_H


#include "LaserScanner.h"
#include "Errors.h"
#include "LaserScannerConfiguration.h"
#include "HokuyoURGConfiguration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"

#include "UrgCtrl.h"
#include "RangeSensorParameter.h"
#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>
using namespace boost::units;
using namespace boost::units::si;
/**
 * \brief 
 *
 */
class HokuyoURG : public LaserScanner {
  public:
    HokuyoURG();

    virtual ~HokuyoURG();

    bool close(Errors& error);

    bool setConfiguration(const LaserScannerConfiguration& configuration, Errors& error);

    bool setConfiguration(const HokuyoURGConfiguration& configuration, Errors& error);

    bool getConfiguration(LaserScannerConfiguration& configuration, Errors& error);

    bool getConfiguration(HokuyoURGConfiguration& configuration, Errors& error);

    bool getData(LaserScannerData& data, Errors& error);

    bool getData(LaserScannerDataWithIntensities& data, Errors& error);

    bool resetDevice();


  private:
    bool open(Errors& error);

    LaserScannerConfiguration* config;

    bool isConnected;

    qrk::UrgCtrl hokuyo;

};
#endif
