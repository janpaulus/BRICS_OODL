#ifndef _HOKUYOURGCONFIGURATION_H
#define _HOKUYOURGCONFIGURATION_H


#include "LaserScannerConfiguration.h"

class HokuyoURGConfiguration : public LaserScannerConfiguration {
  public:
    HokuyoURGConfiguration();

    virtual ~HokuyoURGConfiguration();

    HokuyoURGConfiguration(const HokuyoURGConfiguration & source);

    virtual HokuyoURGConfiguration & operator=(const HokuyoURGConfiguration & source);

};
#endif
