#ifndef BRICS_OODL_YOUBOT_H
#define BRICS_OODL_YOUBOT_H


#include <vector>
#include <string>
#include <boost/thread.hpp>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/EthercatMaster.hpp"
#include "youbot/YouBotJoint.hpp"
extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}

namespace brics_oodl {

//have to be a singleton in the system
class YouBot {
friend class YouBotJoint;
  private:
    static YouBot* instance;

    YouBot();

    YouBot(const YouBot& ) {};

    ~YouBot();


  public:
    static YouBot& getInstance(std::string ethernetDeviceName = "eth0");

    static void destroy();

    unsigned int getNumberOfJoints();

    YouBotJoint& getJoint(unsigned int jointNumber);


  private:
    void setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber);

    YouBotSlaveMsg getMsgBuffer(unsigned int jointNumber);

    void initializeEthercat();

    void initializeJoints();

    bool closeEthercat();

    void updateSensorActorValues();

    std::vector<YouBotJoint> Joints;

    EthercatMaster* ethercatMaster;

    static std::string ethernetDevice;

    ec_mbxbuft mailboxBuffer;

    //in milliseconds
    static const unsigned int timeTillNextEthercatUpdate = 4;

    boost::mutex mutexDataOne;

    boost::mutex mutexDataTwo;

    boost::thread_group threads;

    volatile bool stopThread;

    boost::mutex mutexEthercatMaster;

    std::vector<YouBotSlaveMsg> firstBufferVector;

    std::vector<YouBotSlaveMsg> secondBufferVector;

    unsigned int nrOfSlaves;

    volatile bool newDataFlagOne;

    volatile bool newDataFlagTwo;

    volatile bool newOutputDataFlagOne;

    volatile bool newOutputDataFlagTwo;

    std::vector<outputBuffer*> ethercatOutputBufferVector;

    std::vector<inputBuffer*> ethercatinputBufferVector;

};

} // namespace brics_oodl
#endif
