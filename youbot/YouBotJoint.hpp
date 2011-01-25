#ifndef BRICS_OODL_YOUBOTJOINT_H
#define BRICS_OODL_YOUBOTJOINT_H


#include <vector>
#include <sstream>
#include <cmath>
#include <boost/thread.hpp>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "rude/config.h"
#include "generic/Exceptions.hpp"
#include "generic-joint/Joint.hpp"
#include "generic-joint/JointData.hpp"
#include "youbot/YouBotJointStorage.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotJointParameter.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"

namespace brics_oodl {

class YouBotJoint : public Joint {
  public:
    YouBotJoint(unsigned int jointNo);

    ~YouBotJoint();


  protected:
    virtual void setConfigurationParameter(const JointParameter& parameter);

    virtual void getConfigurationParameter(JointParameter& parameter);


  public:
    void getConfigurationParameter(YouBotJointParameterReadOnly& parameter);

    void getConfigurationParameter(YouBotJointParameter& parameter);

    void setConfigurationParameter(const YouBotJointParameter& parameter);

    void getConfigurationParameter(JointName& parameter);

    void setConfigurationParameter(const JointName& parameter);

    void getConfigurationParameter(GearRatio& parameter);

    void setConfigurationParameter(const GearRatio& parameter);

    void getConfigurationParameter(EncoderTicksPerRound& parameter);

    void setConfigurationParameter(const EncoderTicksPerRound& parameter);

    void setConfigurationParameter(const CalibrateJoint& parameter);

    void setConfigurationParameter(const InverseMovementDirection& parameter);

    void setConfigurationParameter(const JointLimits& parameter);

    void setConfigurationParameter(const StopJoint& parameter);

    void setConfigurationParameter(const NoMoreAction& parameter);


  protected:
    virtual void setData(const JointDataSetpoint& data, SyncMode communicationMode = NON_BLOCKING);

    virtual void getData(JointData& data);


  public:
    ///commands a position or angle to one joint
    ///@param data the to command position
    ///@param communicationMode at the moment only non blocking communication is implemented
    virtual void setData(const JointAngleSetpoint& data, SyncMode communicationMode = NON_BLOCKING);

    ///gets the position or angle of one joint with have been calculated for the actual encoder value 
    ///@param data returns the angle by reference
    virtual void getData(JointSensedAngle& data);

    ///commands a velocity to one joint
    ///@param data the to command velocity
    ///@param communicationMode at the moment only non blocking communication is implemented
    virtual void setData(const JointVelocitySetpoint& data, SyncMode communicationMode = NON_BLOCKING);

    ///gets the velocity of one joint with have been calculated for the actual encoder values
    ///@param data returns the velocity by reference
    virtual void getData(JointSensedVelocity& data);

    ///gets temperature of the motor which have been measured by a thermometer
    ///@param data returns the actual temperature by reference
    virtual void getData(JointSensedTemperature& data);

    ///gets the motor current of one joint with have been measured by a hal sensor
    ///@param data returns the actual motor current by reference
    virtual void getData(JointSensedCurrent& data);


  private:
    void parseYouBotErrorFlags(const YouBotSlaveMsg& messageBuffer);

    void parseMailboxStatusFlags(const YouBotSlaveMailboxMsg& mailboxMsg);

    bool retrieveValueFromMotorContoller(YouBotSlaveMailboxMsg& message);

    bool setValueToMotorContoller(const YouBotSlaveMailboxMsg& mailboxMsg);

    std::string jointName;

    unsigned int jointNumber;

    bool positionReferenceToZero;

    unsigned int timeTillNextMailboxUpdate;

    unsigned int mailboxMsgRetries;

    YouBotJointStorage storage;

};

} // namespace brics_oodl
#endif
