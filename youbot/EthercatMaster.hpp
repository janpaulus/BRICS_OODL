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
    ///creates a instance of the singleton EthercatMaster if there is none and returns a reference to it
    ///@param configFile configuration file name incl. the extension
    ///@param configFilePath the path where the configuration is located with a / at the end
    static EthercatMaster& getInstance(const std::string configFile = "youbot-ethercat.cfg", const std::string configFilePath = "../config/");

    /// destroy the singleton instance by calling the destructor
    static void destroy();

    ///return the quantity of ethercat slave which have an input/output buffer
    unsigned int getNumberOfSlaves() const;

    void AutomaticSendOn(const bool enableAutomaticSend);

    ///provides all ethercat slave informations from the SOEM driver
    ///@param ethercatSlaveInfos ethercat slave informations
    void getEthercatDiagnosticInformation(std::vector<ec_slavet>& ethercatSlaveInfos);


  private:
    ///establishes the ethercat connection
    void initializeEthercat();

    ///closes the ethercat connection
    bool closeEthercat();

    ///stores a ethercat message to the buffer
    ///@param msgBuffer ethercat message
    ///@param jointNumber joint number of the sender joint
    void setMsgBuffer(const YouBotSlaveMsg& msgBuffer, const unsigned int jointNumber);

    ///get a ethercat message form the buffer
    ///@param msgBuffer ethercat message
    ///@param jointNumber joint number of the receiver joint
    YouBotSlaveMsg getMsgBuffer(const unsigned int jointNumber);

    ///stores a mailbox message in a buffer which will be sent to the motor controllers
    ///@param msgBuffer ethercat mailbox message
    ///@param jointNumber joint number of the sender joint
    void setMailboxMsgBuffer(const YouBotSlaveMailboxMsg& msgBuffer, const unsigned int jointNumber);

    ///gets a mailbox message form the buffer which came form the motor controllers
    ///@param msgBuffer ethercat mailbox message
    ///@param jointNumber joint number of the receiver joint
    void getMailboxMsgBuffer(YouBotSlaveMailboxMsg& mailboxMsg, const unsigned int jointNumber);

    ///sends the mailbox Messages which have been stored in the buffer
    ///@param mailboxMsg ethercat mailbox message
    bool sendMailboxMessage(const YouBotSlaveMailboxMsg& mailboxMsg);

    ///receives mailbox messages and stores them in the buffer
    ///@param mailboxMsg ethercat mailbox message
    bool receiveMailboxMessage(YouBotSlaveMailboxMsg& mailboxMsg);

    ///sends and receives ethercat messages and mailbox messages to and from the motor controllers
    ///this method is executed in a separate thread
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

    std::vector<YouBotSlaveMsg> automaticSendOffBufferVector;

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

    unsigned int ethercatTimeout;

    static std::string configFileName;

    bool automaticSendOn;

};

} // namespace brics_oodl
#endif
