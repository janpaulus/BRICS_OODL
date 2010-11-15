
#include "generic-joint/JointConfiguration.hpp"
namespace brics_oodl {

JointConfiguration::JointConfiguration() {
  // Bouml preserved body begin 0004B771
    gearRatio = 1.0;
  // Bouml preserved body end 0004B771
}

JointConfiguration::~JointConfiguration() {
  // Bouml preserved body begin 0004B7F1
  // Bouml preserved body end 0004B7F1
}

double JointConfiguration::getGearRatio() const {
  // Bouml preserved body begin 0004BBF1
    return this->gearRatio;
  // Bouml preserved body end 0004BBF1
}

void JointConfiguration::setGearRatio(double ratio) {
  // Bouml preserved body begin 0004BB71
    if (ratio == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    } else {
      this->gearRatio = ratio;
    }
  // Bouml preserved body end 0004BB71
}


} // namespace brics_oodl
