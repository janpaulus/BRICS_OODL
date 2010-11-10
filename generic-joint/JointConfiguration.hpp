#ifndef BRICS_OODL_JOINTCONFIGURATION_H
#define BRICS_OODL_JOINTCONFIGURATION_H


#include <vector>
#include "generic/Units.hpp"
#include "generic-joint/JointData.hpp"

namespace brics_oodl {

class JointConfiguration {
  public:
    double GearRatio;

    std::vector<JointDataRange> ValidRanges;


  private:
    std::string JointName;

};

} // namespace brics_oodl
#endif
