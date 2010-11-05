#ifndef _YOUBOTJOINT_H
#define _YOUBOTJOINT_H


#include <vector>
#include <boost/thread.hpp>
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-joint/Joint.h"
#include "generic-joint/JointData.h"
#include "generic-joint/JointConfiguration.h"
#include "YouBotSlaveMsg.h"

class YouBotJoint : public Joint {
  public:
    YouBotJoint();

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
    YouBotSlaveMsg MessageBuffer;

};
#endif
