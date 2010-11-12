#ifndef BRICS_OODL_ONEDOFGRIPPER_H
#define BRICS_OODL_ONEDOFGRIPPER_H
#include "generic-gripper/Gripper.hpp"
#include "generic-gripper/GripperData.hpp"
#include "generic-gripper/GripperConfiguration.hpp"
#include "one-dof-gripper/OneDOFGripperData.hpp"
#include "one-dof-gripper/OneDOFGripperConfiguration.hpp"


namespace brics_oodl {

class OneDOFGripper : public Gripper {
  public:
    void setConfiguration(const OneDOFGripperConfiguration& configuration);

    void getConfiguration(OneDOFGripperConfiguration& configuration);

    void setData(const OneDOFGripperData& data);

    void getData(OneDOFGripperData& data);

};

} // namespace brics_oodl
#endif
