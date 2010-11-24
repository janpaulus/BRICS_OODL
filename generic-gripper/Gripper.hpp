#ifndef BRICS_OODL_GRIPPER_H
#define BRICS_OODL_GRIPPER_H


#include "generic-gripper/GripperData.hpp"
#include "generic-gripper/GripperParameter.hpp"
namespace brics_oodl {

class Gripper {
  public:
    virtual void setConfigurationParameter(const GripperParameter& parameter) = 0;

    virtual void getConfigurationParameter(GripperParameter& parameter) = 0;

    virtual void setData(const GripperData& data) = 0;

    virtual void getData(const GripperData& data) = 0;

};

} // namespace brics_oodl
#endif
