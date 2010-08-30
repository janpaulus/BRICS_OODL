#ifndef _SICKS300_H
#define _SICKS300_H


#include "LaserScanner.h"
#include "Errors.h"
#include "LaserScannerConfiguration.h"
#include "SickS300Configuration.h"
#include "LaserScannerData.h"
#include "LaserScannerDataWithIntensities.h"

#include <vector>
#include "ScannerSickS300.h"
#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>
using namespace boost::units;
using namespace boost::units::si;
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

    bool resetDevice();


  private:
    bool open(Errors& error);

    LaserScannerConfiguration* config;

    bool isConnected;

    ScannerSickS300* sickS300;

};
#endif
