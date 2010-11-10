#ifndef _JOINTCONFIGURATION_H
#define _JOINTCONFIGURATION_H


#include <vector>
#include "generic/Units.hpp"
#include "generic-joint/JointData.hpp"

class JointConfiguration {
  public:
    double GearRatio;

    std::vector<JointDataRange> ValidRanges;


  private:
    std::string JointName;

};
#endif
