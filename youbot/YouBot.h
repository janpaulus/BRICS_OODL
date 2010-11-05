#ifndef _YOUBOT_H
#define _YOUBOT_H


#include <vector>
#include <string>
#include <boost/thread.hpp>
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic/Errors.h"
extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}
#include "youbot/ethercat-master/soem_driver.h"
#include "youbot/ethercat-master/soem_master.h"
#include "youbot/YouBotJoint.h"
//have to be a singleton in the system
class YouBot {
  public:
    YouBot();

    ~YouBot();

    std::vector<YouBotJoint> Joints;

    void setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber);

    YouBotSlaveMsg getMsgBuffer(unsigned int jointNumber);


  private:
    bool initializeEthercat();

    bool closeEthercat();

    void updateSensorActorValues();

    soem_ethercat_drivers::SoemMaster* ethercatMaster;

    std::string ethernetDeviceName;

    ec_mbxbuft mailboxBuffer;

    //in milliseconds
    static const unsigned int timeTillNextEthercatUpdate = 4;

    boost::mutex mutexData;

    boost::thread_group threads;

    volatile bool stopThread;

    boost::mutex mutexEthercatMaster;

    std::vector<YouBotSlaveMsg> msgBufferVector;

    unsigned int nrOfSlaves;

};
#endif
