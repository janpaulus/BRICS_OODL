#ifndef BRICS_OODL_SICKLDCONFIGURATION_H
#define BRICS_OODL_SICKLDCONFIGURATION_H


#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "generic/Units.hpp"
#include "generic/Logger.hpp"
namespace brics_oodl {

class SickLDConfiguration : public LaserScannerConfiguration {
  public:
    SickLDConfiguration();

    virtual ~SickLDConfiguration();

    SickLDConfiguration(const SickLDConfiguration & source);

    virtual SickLDConfiguration & operator=(const SickLDConfiguration & source);

    quantity<frequency> motorSpeed;

    unsigned int numSectors;

};

} // namespace brics_oodl
#endif
