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

    void setGearRatio(const double ratio);

    std::vector<JointDataRange> validRanges;

    std::string jointName;


  private:
    double gearRatio;

};

} // namespace brics_oodl
#endif
