#ifndef _SICKLDCONFIGURATION_H
#define _SICKLDCONFIGURATION_H


#include "LaserScannerConfiguration.h"

#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>

using namespace std;
using namespace boost::units;
using namespace boost::units::si;

class SickLDConfiguration : public LaserScannerConfiguration {
  public:
    SickLDConfiguration();

    virtual ~SickLDConfiguration();

    SickLDConfiguration(const SickLDConfiguration & source);

    virtual SickLDConfiguration & operator=(const SickLDConfiguration & source);

    quantity<frequency> motor_speed;

    unsigned int num_sectors;

};
#endif
