
#include "base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.hpp"
namespace brics_oodl {

FourSwedishWheelOmniBaseKinematicConfiguration::FourSwedishWheelOmniBaseKinematicConfiguration() {
  // Bouml preserved body begin 0004C271
    this->rotationRatio = 1;
    this->slideRatio = 1;
  // Bouml preserved body end 0004C271
}

FourSwedishWheelOmniBaseKinematicConfiguration::~FourSwedishWheelOmniBaseKinematicConfiguration() {
  // Bouml preserved body begin 0004C2F1
  // Bouml preserved body end 0004C2F1
}

FourSwedishWheelOmniBaseKinematicConfiguration::FourSwedishWheelOmniBaseKinematicConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration & source) {
  // Bouml preserved body begin 0004C371
    this->rotationRatio = source.rotationRatio;
    this->slideRatio = source.slideRatio;
    this->lengthBetweenFrontAndRearWheels = source.lengthBetweenFrontAndRearWheels;
    this->lengthBetweenFrontWheels = source.lengthBetweenFrontWheels;
    this->wheelRadius = source.wheelRadius;
  // Bouml preserved body end 0004C371
}

FourSwedishWheelOmniBaseKinematicConfiguration & FourSwedishWheelOmniBaseKinematicConfiguration::operator=(const FourSwedishWheelOmniBaseKinematicConfiguration & source) {
  // Bouml preserved body begin 0004C3F1
    this->rotationRatio = source.rotationRatio;
    this->slideRatio = source.slideRatio;
    this->lengthBetweenFrontAndRearWheels = source.lengthBetweenFrontAndRearWheels;
    this->lengthBetweenFrontWheels = source.lengthBetweenFrontWheels;
    this->wheelRadius = source.wheelRadius;
  // Bouml preserved body end 0004C3F1
}


} // namespace brics_oodl
