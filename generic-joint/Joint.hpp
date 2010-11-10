#ifndef _JOINT_H
#define _JOINT_H


#include <vector>
#include "generic/Units.hpp"
#include "generic-joint/JointData.hpp"
#include "generic-joint/JointConfiguration.hpp"

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
#endif
