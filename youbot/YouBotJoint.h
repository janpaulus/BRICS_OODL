#ifndef _YOUBOTJOINT_H
#define _YOUBOTJOINT_H


#include "Joint.h"

class JointConfiguration;
class JointSensorAngle;
class JointSensorVelocity;
class JointSensorTemperature;

class YouBotJoint : public Joint {
  public:
    void setConfiguration(const JointConfiguration& configuration);

    void getConfiguration(JointConfiguration& configuration);

    void setData(const JointSensorAngle& data, SyncMode communicationMode);

    void setData(const JointSensorVelocity& data, SyncMode communicationMode);

    void getData(JointSensorTemperature& data);

};
#endif
