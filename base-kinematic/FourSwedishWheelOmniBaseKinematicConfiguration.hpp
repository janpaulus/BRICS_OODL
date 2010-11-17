#ifndef BRICS_OODL_FOURSWEDISHWHEELOMNIBASEKINEMATICCONFIGURATION_H
#define BRICS_OODL_FOURSWEDISHWHEELOMNIBASEKINEMATICCONFIGURATION_H


#include <vector>
#include <string>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
namespace brics_oodl {

class FourSwedishWheelOmniBaseKinematicConfiguration {
  public:
    FourSwedishWheelOmniBaseKinematicConfiguration();

    ~FourSwedishWheelOmniBaseKinematicConfiguration();

    FourSwedishWheelOmniBaseKinematicConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration & source);

    FourSwedishWheelOmniBaseKinematicConfiguration & operator=(const FourSwedishWheelOmniBaseKinematicConfiguration & source);

    quantity<si::length> wheelRadius;

    quantity<si::length> lengthBetweenFrontWheels;

    quantity<si::length> lengthBetweenFrontAndRearWheels;

    //how far sideways in one wheel rotation compared to forward
    double slideRatio;

    double rotationRatio;

};

} // namespace brics_oodl
#endif
