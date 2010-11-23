#ifndef BRICS_OODL_ONEDOFGRIPPER_H
#define BRICS_OODL_ONEDOFGRIPPER_H
#include "generic-gripper/Gripper.hpp"
#include "generic-gripper/GripperData.hpp"
#include "generic-gripper/GripperParameter.hpp"
#include "one-dof-gripper/OneDOFGripperData.hpp"


namespace brics_oodl {

class OneDOFGripper : public Gripper {
  public:
    virtual void setConfigurationParameter(const GripperParameter& parameter) = 0;

    virtual void getConfigurationParameter(GripperParameter& parameter) = 0;

    virtual void setData(const OneDOFGripperData& data) = 0;

    virtual void getData(OneDOFGripperData& data) = 0;

};

} // namespace brics_oodl
#endif
