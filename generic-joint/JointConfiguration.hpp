#ifndef BRICS_OODL_JOINTCONFIGURATION_H
#define BRICS_OODL_JOINTCONFIGURATION_H


#include <vector>
#include "generic/Units.hpp"
#include "generic-joint/JointData.hpp"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"

namespace brics_oodl {

class JointConfiguration {
  public:
    JointConfiguration();

    virtual ~JointConfiguration();

    double getGearRatio() const;

    void setGearRatio(double ratio);

    std::vector<JointDataRange> ValidRanges;

    std::string JointName;


  private:
    double GearRatio;

};

} // namespace brics_oodl
#endif
