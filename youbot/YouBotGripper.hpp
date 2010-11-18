#ifndef BRICS_OODL_YOUBOTGRIPPER_H
#define BRICS_OODL_YOUBOTGRIPPER_H


#include "generic-gripper/Gripper.hpp"
#include "generic-gripper/GripperData.hpp"
#include "generic-gripper/GripperConfiguration.hpp"
#include "one-dof-gripper/OneDOFGripper.hpp"
#include "one-dof-gripper/OneDOFGripperData.hpp"
#include "one-dof-gripper/OneDOFGripperConfiguration.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"

namespace brics_oodl {

class YouBotGripper : public OneDOFGripper {
  public:
    void setConfiguration(const OneDOFGripperConfiguration& configuration);

    void getConfiguration(OneDOFGripperConfiguration& configuration);

    void setData(const OneDOFGripperData& data);

    void getData(OneDOFGripperData& data);

};

} // namespace brics_oodl
#endif
