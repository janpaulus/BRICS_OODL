#ifndef _SICKLDCONFIGURATION_H
#define _SICKLDCONFIGURATION_H


#include "generic-laser-scanner/LaserScannerConfiguration.h"
#include "generic/Units.h"
#include "generic/Logger.h"
class SickLDConfiguration : public LaserScannerConfiguration {
  public:
    SickLDConfiguration();

    virtual ~SickLDConfiguration();

    SickLDConfiguration(const SickLDConfiguration & source);

    virtual SickLDConfiguration & operator=(const SickLDConfiguration & source);

    quantity<frequency> motorSpeed;

    unsigned int numSectors;

};
#endif
