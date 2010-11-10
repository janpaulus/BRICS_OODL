#ifndef BRICS_OODL_JOINT_H
#define BRICS_OODL_JOINT_H


#include <vector>
#include "generic/Units.hpp"
#include "generic-joint/JointData.hpp"
#include "generic-joint/JointConfiguration.hpp"

namespace brics_oodl {

enum SyncMode {
  BLOCKING,
  NON_BLOCKING

};
class Joint {
  public:
    virtual void setConfiguration(const JointConfiguration& configuration) = 0;

    virtual void getConfiguration(JointConfiguration& configuration) = 0;

    virtual void setData(const JointDataSetpoint& data, SyncMode communicationMode) = 0;

    virtual void getData(JointData& data) = 0;

};

} // namespace brics_oodl
#endif
