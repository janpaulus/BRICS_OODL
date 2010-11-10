#ifndef _HOKUYOURGCONFIGURATION_H
#define _HOKUYOURGCONFIGURATION_H


#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "generic/Units.hpp"
#include "generic/Logger.hpp"
class HokuyoURGConfiguration : public LaserScannerConfiguration {
  public:
    HokuyoURGConfiguration();

    virtual ~HokuyoURGConfiguration();

    HokuyoURGConfiguration(const HokuyoURGConfiguration & source);

    virtual HokuyoURGConfiguration & operator=(const HokuyoURGConfiguration & source);

};
#endif
