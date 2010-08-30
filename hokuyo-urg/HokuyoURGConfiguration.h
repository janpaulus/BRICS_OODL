#ifndef _HOKUYOURGCONFIGURATION_H
#define _HOKUYOURGCONFIGURATION_H


#include "LaserScannerConfiguration.h"

#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>
using namespace boost::units;
using namespace boost::units::si;
class HokuyoURGConfiguration : public LaserScannerConfiguration {
  public:
    HokuyoURGConfiguration();

    virtual ~HokuyoURGConfiguration();

    HokuyoURGConfiguration(const HokuyoURGConfiguration & source);

    virtual HokuyoURGConfiguration & operator=(const HokuyoURGConfiguration & source);

};
#endif
