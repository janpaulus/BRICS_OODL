#ifndef BRICS_OODL_YOUBOTJOINT_H
#define BRICS_OODL_YOUBOTJOINT_H


#include <vector>
#include <sstream>
#include <boost/thread.hpp>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/Joint.hpp"
#include "generic-joint/JointData.hpp"
#include "generic-joint/JointConfiguration.hpp"
#include "youbot/YouBotJointConfiguration.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"

namespace brics_oodl {

enum YouBotJointControllerMode
 {
  MOTOR_STOP = 0,
  POSITION_CONTROL = 1,
  VELOCITY_CONTROL = 2,
  NO_MORE_ACTION = 3,
  SET_POSITION_TO_REFERENCE = 4

};
enum YouBotErrorFlags {
  OVER_CURRENT = 1,
  UNDER_VOLTAGE = 2,
  OVER_VOLTAGE = 4,
  OVER_TEMPERATURE = 8,
  HALTED = 16,
  HALL_SENSOR = 32,
  ENCODER = 64,
  MOTOR_WINDING = 128,
  CYCLE_TIME_VIOLATION = 256,
  INIT_SIN_COMM = 512

};
class YouBotJoint : public Joint {
  public:
    YouBotJoint(unsigned int jointNo);

    ~YouBotJoint();


  protected:
    //please use a YouBotJointConfiguration
    void setConfiguration(const JointConfiguration& configuration);

    //please use a YouBotJointConfiguration
    void getConfiguration(JointConfiguration& configuration);


  public:
    //sets the configuration for one joint
    //@param configuration the joint configuration
    void setConfiguration(const YouBotJointConfiguration& configuration);

    //to get the configuration for one joint
    //@param configuration returns the joint configuration by reference
    void getConfiguration(YouBotJointConfiguration& configuration);


  protected:
    virtual void setData(const JointDataSetpoint& data, SyncMode communicationMode = NON_BLOCKING);

    virtual void getData(JointData& data);


  public:
    //commands a position or angle to one joint
    //@param data the to command position
    //@param communicationMode at the moment only non blocking communication is implemented
    virtual void setData(const JointAngleSetpoint& data, SyncMode communicationMode = NON_BLOCKING);

    //gets the position or angle of one joint with have been calculated for the actual encoder value 
    //@param data returns the angle by reference
    virtual void getData(JointSensedAngle& data);

    //commands a velocity to one joint
    //@param data the to command velocity
    //@param communicationMode at the moment only non blocking communication is implemented
    virtual void setData(const JointVelocitySetpoint& data, SyncMode communicationMode = NON_BLOCKING);

    //gets the velocity of one joint with have been calculated for the actual encoder values
    //@param data returns the velocity by reference
    virtual void getData(JointSensedVelocity& data);

    //gets temperature of the motor which have been measured by a thermometer
    //@param data returns the actual temperature by reference
    virtual void getData(JointSensedTemperature& data);

    //gets the motor current of one joint with have been measured by a hal sensor
    //@param data returns the actual motor current by reference
    virtual void getData(JointSensedCurrent& data);


  private:
    void parseYouBotErrorFlags();

    unsigned int jointNumber;

    YouBotSlaveMsg messageBuffer;

    YouBotSlaveMailboxMsg mailboxMsgBuffer;

    YouBotJointConfiguration config;

};

} // namespace brics_oodl
#endif
