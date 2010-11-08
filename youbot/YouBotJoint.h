#ifndef _YOUBOTJOINT_H
#define _YOUBOTJOINT_H


#include <vector>
#include <boost/thread.hpp>
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-joint/Joint.h"
#include "generic-joint/JointData.h"
#include "generic-joint/JointConfiguration.h"
#include "youbot/YouBotSlaveMsg.h"

enum YouBotJointControllerMode
 {
  MOTOR_STOP = 0,
  POSITION_CONTROL = 1,
  VELOCITY_CONTROL = 2,
  NO_MORE_ACTION = 3,
  SET_POSITION_TO_REFERENCE = 4

};
class YouBotJoint : public Joint {
  public:
    YouBotJoint(unsigned int jointNo);

    ~YouBotJoint();

    void setConfiguration(const JointConfiguration& configuration);

    void getConfiguration(JointConfiguration& configuration);

    virtual void setData(const JointSetpointData& data, SyncMode communicationMode);

    void setData(const JointSetpointAngle& data, SyncMode communicationMode);

    void setData(const JointSetpointVelocity& data, SyncMode communicationMode);

    virtual void getData(JointData& data);

    void getData(JointSensorTemperature& data);

    void getData(JointSensorAngle& data);

    void getData(JointSensorVelocity& data);

    void getData(JointSensorCurrent& data);


  private:
    unsigned int jointNumber;

    YouBotSlaveMsg MessageBuffer;

    JointConfiguration configuration;

};
#endif
