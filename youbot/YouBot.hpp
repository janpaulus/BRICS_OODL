#ifndef BRICS_OODL_YOUBOT_H
#define BRICS_OODL_YOUBOT_H


#include <vector>
#include <sstream>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <boost/thread.hpp>
#include "rude/config.h"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "generic/ExceptionOODL.hpp"
#include "youbot/YouBotGripper.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
//#include "youbot/EthercatMaster.hpp"
#include "youbot/YouBotJoint.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.hpp"


extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}

namespace brics_oodl {

//have to be a singleton in the system
class YouBot {
friend class YouBotJoint;
friend class YouBotGripper;
  private:
    static YouBot* instance;

    YouBot();

    YouBot(const YouBot& ) {};

    ~YouBot();


  public:
    static YouBot& getInstance();

    static void destroy();

    ///return the quantity of joints
    unsigned int getNumberOfJoints() const;

    ///return a joint form the base, arm1 or arm2
    ///@param jointNumber 1-4 are the base joints, 5-9 are the arm1 joints, 9-14 are the arm2 joints
    YouBotJoint& getJoint(const unsigned int jointNumber);

    ///return a joint form the base, arm1 or arm2
    ///@param jointName e.g. BaseLeftFront
    YouBotJoint& getJointByName(const std::string jointName);

    void getEthercatDiagnosticInformation(std::vector<ec_slavet>& ethercatSlaveInfos);


  private:
    void initializeEthercat();

    bool closeEthercat();

    void setMsgBuffer(const YouBotSlaveMsg& msgBuffer, const unsigned int jointNumber);

    YouBotSlaveMsg getMsgBuffer(const unsigned int jointNumber);

    void setMailboxMsgBuffer(const YouBotSlaveMailboxMsg& msgBuffer, const unsigned int jointNumber);

    void getMailboxMsgBuffer(YouBotSlaveMailboxMsg& mailboxMsg, const unsigned int jointNumber);

    bool sendMailboxMessage(const YouBotSlaveMailboxMsg& mailboxMsg);

    bool receiveMailboxMessage(YouBotSlaveMailboxMsg& mailboxMsg);

    void updateSensorActorValues();

    std::vector<YouBotJoint> joints;

    std::string ethernetDevice;

    ec_mbxbuft mailboxBuffer;

    //in milliseconds
    unsigned int timeTillNextEthercatUpdate;

    boost::mutex mutexDataOne;

    boost::mutex mutexDataTwo;

    boost::thread_group threads;

    volatile bool stopThread;

    std::vector<YouBotSlaveMsg> firstBufferVector;

    std::vector<YouBotSlaveMsg> secondBufferVector;

    unsigned int nrOfSlaves;

    volatile bool newDataFlagOne;

    volatile bool newDataFlagTwo;

    std::vector<bool> newOutputDataFlagOne;

    std::vector<bool> newOutputDataFlagTwo;

    std::vector<OutputBuffer*> ethercatOutputBufferVector;

    std::vector<InputBuffer*> ethercatInputBufferVector;

    std::vector<YouBotSlaveMailboxMsg> firstMailboxBufferVector;

    std::vector<YouBotSlaveMailboxMsg> secondMailboxBufferVector;

    std::vector<bool> newMailboxDataFlagOne;

    std::vector<bool> newMailboxDataFlagTwo;

    ec_mbxbuft mailboxBufferSend;

    unsigned int mailboxTimeout;

    ec_mbxbuft mailboxBufferReceive;

    std::vector<bool> newMailboxInputDataFlagOne;

    std::vector<bool> newMailboxInputDataFlagTwo;

    rude::Config configfile;

    std::vector<ec_slavet> ethercatSlaveInfo;

    int nr_slaves_;

    char IOmap_[4096];

};

} // namespace brics_oodl
#endif
