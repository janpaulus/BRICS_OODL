#ifndef _HOKUYOURGCONFIGURATION_H
#define _HOKUYOURGCONFIGURATION_H


#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic/Units.h"
#include "generic/Logger.h"
class HokuyoURGConfiguration : public LaserScannerConfiguration {
  public:
    HokuyoURGConfiguration();

    virtual ~HokuyoURGConfiguration();

    HokuyoURGConfiguration(const HokuyoURGConfiguration & source);

    virtual HokuyoURGConfiguration & operator=(const HokuyoURGConfiguration & source);

};
#endif
