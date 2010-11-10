#ifndef _YOUBOTJOINT_H
#define _YOUBOTJOINT_H


#include <vector>
#include <sstream>
#include <boost/thread.hpp>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/Joint.hpp"
#include "generic-joint/JointData.hpp"
#include "generic-joint/JointConfiguration.hpp"
#include "youbot/YouBotSlaveMsg.hpp"

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

    void setConfiguration(const JointConfiguration& configuration);

    void getConfiguration(JointConfiguration& configuration);

    virtual void setData(const JointDataSetpoint& data, SyncMode communicationMode);

    void setData(const JointAngleSetpoint& data, SyncMode communicationMode);

    void setData(const JointVelocitySetpoint& data, SyncMode communicationMode);

    virtual void getData(JointData& data);

    virtual void getData(JointSensedTemperature& data);

    virtual void getData(JointSensedAngle& data);

    virtual void getData(JointSensedVelocity& data);

    virtual void getData(JointSensedCurrent& data);


  private:
    unsigned int jointNumber;

    YouBotSlaveMsg MessageBuffer;

    JointConfiguration configuration;

    void parseYouBotErrorFlags();

};
#endif
