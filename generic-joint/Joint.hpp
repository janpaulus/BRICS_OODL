#ifndef BRICS_OODL_JOINT_H
#define BRICS_OODL_JOINT_H


#include <vector>
#include "generic/Units.hpp"
#include "generic-joint/JointData.hpp"
#include "generic-joint/JointParameter.hpp"

namespace brics_oodl {

enum SyncMode {
  NON_BLOCKING

};
class Joint {
  public:
    virtual void setData(const JointDataSetpoint& data, SyncMode communicationMode) = 0;

    virtual void getData(JointData& data) = 0;

    virtual void setConfigurationParameter(const JointParameter& parameter) = 0;

    virtual void getConfigurationParameter(JointParameter& parameter) = 0;

};

} // namespace brics_oodl
#endif
