#ifndef _JOINTCONFIGURATION_H
#define _JOINTCONFIGURATION_H


#include <vector>
#include "generic/Units.h"
#include "generic-joint/JointData.h"
class JointDataRange;

class JointConfiguration {
  public:
    double GearRatio;

    std::vector<JointDataRange> ValidRanges;


  private:
    std::string JointName;

};
#endif
