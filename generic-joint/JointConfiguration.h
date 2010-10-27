#ifndef _JOINTCONFIGURATION_H
#define _JOINTCONFIGURATION_H


#include "generic/Units.h"
class JointConfiguration {
  public:
    double GearRatio;

    std::vector<JointDataRange> ValidRanges;


  private:
    std::string JointName;

};
#endif
