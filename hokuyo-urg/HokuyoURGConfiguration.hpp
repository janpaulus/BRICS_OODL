#ifndef BRICS_OODL_HOKUYOURGCONFIGURATION_H
#define BRICS_OODL_HOKUYOURGCONFIGURATION_H


#include "generic-laser-scanner/LaserScannerConfiguration.hpp"
#include "generic/Units.hpp"
#include "generic/Logger.hpp"
namespace brics_oodl {

class HokuyoURGConfiguration : public LaserScannerConfiguration {
  public:
    HokuyoURGConfiguration();

    virtual ~HokuyoURGConfiguration();

    HokuyoURGConfiguration(const HokuyoURGConfiguration & source);

    virtual HokuyoURGConfiguration & operator=(const HokuyoURGConfiguration & source);

};

} // namespace brics_oodl
#endif
