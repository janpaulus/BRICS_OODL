#ifndef BRICS_OODL_ETHERCATMASTER_H
#define BRICS_OODL_ETHERCATMASTER_H


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
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"

extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}

namespace brics_oodl {

//have to be a singleton in the system
class EthercatMaster {
friend class YouBotJoint;
friend class YouBotGripper;
  private:
    static EthercatMaster* instance;

    EthercatMaster();

    EthercatMaster(const EthercatMaster& ) {};

    ~EthercatMaster();


  public:
    static EthercatMaster& getInstance();

    static void destroy();

    ///return the quantity of joints
    unsigned int getNumberOfSlaves() const;

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

    char IOmap_[4096];

};

} // namespace brics_oodl
#endif
