#ifndef BRICS_OODL_YOUBOTGRIPPER_H
#define BRICS_OODL_YOUBOTGRIPPER_H


#include <vector>
#include <sstream>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "generic/ExceptionOODL.hpp"
#include "youbot/ProtocolDefinitions.hpp"

#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
#include "generic-gripper/Gripper.hpp"
#include "generic-gripper/GripperData.hpp"
#include "generic-gripper/GripperParameter.hpp"
#include "one-dof-gripper/OneDOFGripper.hpp"
#include "one-dof-gripper/OneDOFGripperData.hpp"
#include "youbot/YouBotGripperParameter.hpp"


namespace brics_oodl {

class YouBotGripper : public OneDOFGripper {
  public:
    YouBotGripper(const unsigned int jointNo);

    virtual ~YouBotGripper();


  protected:
    virtual void getConfigurationParameter(GripperParameter& parameter);

    virtual void setConfigurationParameter(const GripperParameter& parameter);


  public:
    void getConfigurationParameter(YouBotGripperParameter& parameter);

    void setConfigurationParameter(const YouBotGripperParameter& parameter);

    void setConfigurationParameter(const CalibrateGripper& parameter);

    void setConfigurationParameter(const BarSpacingOffset& parameter);

    void setConfigurationParameter(const MaxTravelDistance& parameter);

    void setConfigurationParameter(const MaxEncoderValue& parameter);


  protected:
    void getData(const GripperData& data);

    virtual void setData(const GripperData& data);

    void getData(OneDOFGripperData& data);

    void setData(const OneDOFGripperData& data);


  public:
    void setData(const GripperBarSpacingSetPoint& barSpacing);

    void getData(GripperBarSpacingSetPoint& barSpacing);


  private:
    bool setValueToMotorContoller(const YouBotSlaveMailboxMsg& mailboxMsg);

    bool retrieveValueFromMotorContoller(YouBotSlaveMailboxMsg& message);

    unsigned int timeTillNextMailboxUpdate;

    unsigned int mailboxMsgRetries;

    unsigned int jointNumber;

    unsigned int maxEncoderValue;

    quantity<si::length> maxTravelDistance;

    quantity<si::length> barSpacingOffset;

    quantity<si::length> lastGripperPosition;

};

} // namespace brics_oodl
#endif
