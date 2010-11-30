
extern "C" {
#include "ethercattype.h"
#include "nicdrv.h"
#include "ethercatbase.h"
#include "ethercatmain.h"
#include "ethercatconfig.h"
#include "ethercatcoe.h"
#include "ethercatdc.h"
#include "ethercatprint.h"
}
#include "youbot/YouBot.hpp"

namespace brics_oodl {

  YouBot* YouBot::instance = 0;

  YouBot::YouBot() {
    // Bouml preserved body begin 00041171

    //Initialize the Logger
    (Logger::getInstance()).init();

    ethernetDevice = "eth0";
    timeTillNextEthercatUpdate = 4; //msec
    mailboxTimeout = 4000; //micro sec
    stopThread = false;
    newDataFlagOne = false;
    newDataFlagTwo = false;

    if (!configfile.load("../config/youbot-configfile.cfg"))
      throw ExceptionOODL("../config/youbot-configfile.cfg file no found");

    configfile.setSection("YouBot");
    ethernetDevice = configfile.getStringValue("EthernetDevice");
    timeTillNextEthercatUpdate = configfile.getIntValue("EtherCATUpdateRate_[msec]");
    mailboxTimeout = configfile.getIntValue("MailboxTimeout_[usec]");


    // Bouml preserved body end 00041171
  }

  YouBot::~YouBot() {
    // Bouml preserved body begin 000411F1
    this->closeEthercat();
    // Bouml preserved body end 000411F1
  }

  YouBot& YouBot::getInstance() {
    // Bouml preserved body begin 00042F71
    if (!instance) {
      instance = new YouBot();
      instance->initializeEthercat();
    }
    return *instance;

    // Bouml preserved body end 00042F71
  }

  void YouBot::destroy() {
    // Bouml preserved body begin 00042FF1
    if (instance) {
      delete instance;
    }
    instance = 0;

    // Bouml preserved body end 00042FF1
  }

  ///return the quantity of joints

  unsigned int YouBot::getNumberOfJoints() const {
    // Bouml preserved body begin 00044A71
    return this->joints.size();
    // Bouml preserved body end 00044A71
  }

  ///return a joint form the base, arm1 or arm2
  ///@param jointNumber 1-4 are the base joints, 5-9 are the arm1 joints, 9-14 are the arm2 joints

  YouBotJoint& YouBot::getJoint(const unsigned int jointNumber) {
    // Bouml preserved body begin 000449F1
    if (jointNumber <= 0 || jointNumber > getNumberOfJoints()) {
      throw ExceptionOODL("Invalid Joint Number");
    }

    return joints[jointNumber - 1];
    // Bouml preserved body end 000449F1
  }

  ///return a joint form the base, arm1 or arm2
  ///@param jointName e.g. BaseLeftFront

  YouBotJoint& YouBot::getJointByName(const std::string jointName) {
    // Bouml preserved body begin 0004F8F1
    int jointNumber = -1;
    JointName jName;
    std::string name;

    for (int i = 0; i < joints.size(); i++) {
      joints[i].getConfigurationParameter(jName);
      jName.getParameter(name);
      if (name == jointName) {
        jointNumber = i;
        break;
      }
    }

    if (jointNumber == -1) {
      throw ExceptionOODL("Joint Name not found");
    }

    return joints[jointNumber];
    // Bouml preserved body end 0004F8F1
  }

  void YouBot::getEthercatDiagnosticInformation(std::vector<ec_slavet>& ethercatSlaveInfos) {
    // Bouml preserved body begin 00061EF1
    ethercatSlaveInfos = this->ethercatSlaveInfo;
    // Bouml preserved body end 00061EF1
  }

  void YouBot::initializeEthercat() {
    // Bouml preserved body begin 000410F1

    /* initialise SOEM, bind socket to ifname */
    if (ec_init(ethernetDevice.c_str())) {
      LOG(trace) << "Initializing EtherCAT on " << ethernetDevice;
      /* find and auto-config slaves */
      if (ec_config(TRUE, &IOmap_) > 0) {


        //copy nr of slaves to class variable
        nr_slaves_ = ec_slavecount;
        LOG(trace) << ec_slavecount << " slaves found and configured.";

        /* wait for all slaves to reach Pre OP state */
        /*ec_statecheck(0, EC_STATE_PRE_OP,  EC_TIMEOUTSTATE);
        if (ec_slave[0].state != EC_STATE_PRE_OP )
        {
        printf("Not all slaves reached prae operational state.\n");
        ec_readstate();
        //If not all slaves operational find out which one
          for(int i = 1; i<=ec_slavecount ; i++)
          {
            if(ec_slave[i].state != EC_STATE_PRE_OP)
            {
              printf("Slave %d State=%2x StatusCode=%4x : %s\n",
              i, ec_slave[i].state, ec_slave[i].ALstatuscode, ec_ALstatuscode2string(ec_slave[i].ALstatuscode));
            }
          }
        }*/


        /* wait for all slaves to reach SAFE_OP state */
        ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE);
        if (ec_slave[0].state != EC_STATE_SAFE_OP) {
          LOG(info) << "Not all slaves reached safe operational state.";
          ec_readstate();
          //If not all slaves operational find out which one
          for (int i = 1; i <= ec_slavecount; i++) {
            if (ec_slave[i].state != EC_STATE_SAFE_OP) {
              LOG(info) << "Slave " << i << " State=" << ec_slave[i].state << " StatusCode=" << ec_slave[i].ALstatuscode << " : " << ec_ALstatuscode2string(ec_slave[i].ALstatuscode);

            }
          }
        }

        //Configure distributed clock
        //ec_configdc();
        //Read the state of all slaves
        //ec_readstate();

        LOG(trace) << "Request operational state for all slaves";

        ec_slave[0].state = EC_STATE_OPERATIONAL;
        // request OP state for all slaves
        /* send one valid process data to make outputs in slaves happy*/
        ec_send_processdata();
        ec_receive_processdata(EC_TIMEOUTRET);
        /* request OP state for all slaves */
        ec_writestate(0);
        // wait for all slaves to reach OP state

        ec_statecheck(0, EC_STATE_OPERATIONAL, EC_TIMEOUTSTATE);
        if (ec_slave[0].state == EC_STATE_OPERATIONAL) {
          LOG(trace) << "Operational state reached for all slaves.";
        } else {
          throw ExceptionOODL("Not all slaves reached operational state.");

        }
      } else {
        throw ExceptionOODL("No slaves found!");
      }

    } else {
      throw ExceptionOODL("No socket connection on " + ethernetDevice + "\nExcecute as root");
    }



    std::string baseJointControllerName = "TMCM-174";
    std::string manipulatorJointControllerName = "TMCM-174";
    std::string actualSlaveName;
    nrOfSlaves = 0;
    YouBotSlaveMsg emptySlaveMsg;

    baseJointControllerName = configfile.getStringValue("BaseJointControllerName");
    manipulatorJointControllerName = configfile.getStringValue("ManipulatorJointControllerName");

    //reserve memory for all joints
    for (unsigned int cnt = 1; cnt <= ec_slavecount; cnt++) {
      //   printf("Slave:%d Name:%s Output size:%3dbits Input size:%3dbits State:%2d delay:%d.%d\n",
      //           cnt, ec_slave[cnt].name, ec_slave[cnt].Obits, ec_slave[cnt].Ibits,
      //           ec_slave[cnt].state, (int) ec_slave[cnt].pdelay, ec_slave[cnt].hasdc);

      ethercatSlaveInfo.push_back(ec_slave[cnt]);

      actualSlaveName = ec_slave[cnt].name;
      if ((actualSlaveName == baseJointControllerName || actualSlaveName == manipulatorJointControllerName) && ec_slave[cnt].Obits > 0 && ec_slave[cnt].Ibits > 0) {
        nrOfSlaves++;
        joints.push_back(YouBotJoint(nrOfSlaves));

        firstBufferVector.push_back(emptySlaveMsg);
        secondBufferVector.push_back(emptySlaveMsg);
        ethercatOutputBufferVector.push_back((OutputBuffer*) (ec_slave[cnt].outputs));
        ethercatInputBufferVector.push_back((InputBuffer*) (ec_slave[cnt].inputs));
        YouBotSlaveMailboxMsg emptyMailboxSlaveMsg(cnt);
        firstMailboxBufferVector.push_back(emptyMailboxSlaveMsg);
        secondMailboxBufferVector.push_back(emptyMailboxSlaveMsg);
        newOutputDataFlagOne.push_back(false);
        newOutputDataFlagTwo.push_back(false);
        newMailboxDataFlagOne.push_back(false);
        newMailboxDataFlagTwo.push_back(false);
        newMailboxInputDataFlagOne.push_back(false);
        newMailboxInputDataFlagTwo.push_back(false);
      }

    }

    if (nrOfSlaves > 0) {
      LOG(info) << "Number of YouBot Joints found: " << nrOfSlaves;
    } else {
      throw ExceptionOODL("No Ethercat slave could be found");
      return;
    }

    stopThread = false;
    threads.create_thread(boost::bind(&YouBot::updateSensorActorValues, this));

    return;
    // Bouml preserved body end 000410F1
  }

  bool YouBot::closeEthercat() {
    // Bouml preserved body begin 00041271
    stopThread = true;

    threads.join_all();

    //stop SOEM, close socket
    ec_close();

    // Bouml preserved body end 00041271
  }

  void YouBot::setMsgBuffer(const YouBotSlaveMsg& msgBuffer, const unsigned int jointNumber) {
    // Bouml preserved body begin 000414F1

    if (newDataFlagOne == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexDataOne);
        firstBufferVector[jointNumber - 1].stctOutput = msgBuffer.stctOutput;
        newOutputDataFlagOne[jointNumber - 1] = true;
        newOutputDataFlagTwo[jointNumber - 1] = false;
      }
    } else if (newDataFlagTwo == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
        secondBufferVector[jointNumber - 1].stctOutput = msgBuffer.stctOutput;
        newOutputDataFlagOne[jointNumber - 1] = false;
        newOutputDataFlagTwo[jointNumber - 1] = true;
      }

    } else {
      return;
    }

    // Bouml preserved body end 000414F1
  }

  YouBotSlaveMsg YouBot::getMsgBuffer(const unsigned int jointNumber) {
    // Bouml preserved body begin 00041571

    YouBotSlaveMsg returnMsg;

    if (newDataFlagOne == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexDataOne);
        returnMsg = firstBufferVector[jointNumber - 1];
      }
    } else if (newDataFlagTwo == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
        returnMsg = secondBufferVector[jointNumber - 1];
      }

    } else {
      return returnMsg;
    }

    return returnMsg;
    // Bouml preserved body end 00041571
  }

  void YouBot::setMailboxMsgBuffer(const YouBotSlaveMailboxMsg& msgBuffer, const unsigned int jointNumber) {
    // Bouml preserved body begin 00049D71

    if (newDataFlagOne == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexDataOne);
        firstMailboxBufferVector[jointNumber - 1].stctOutput = msgBuffer.stctOutput;
        newMailboxDataFlagOne[jointNumber - 1] = true;
        newMailboxDataFlagTwo[jointNumber - 1] = false;
      }
    } else if (newDataFlagTwo == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
        secondMailboxBufferVector[jointNumber - 1].stctOutput = msgBuffer.stctOutput;
        newMailboxDataFlagOne[jointNumber - 1] = false;
        newMailboxDataFlagTwo[jointNumber - 1] = true;
      }

    }
    return;
    // Bouml preserved body end 00049D71
  }

  void YouBot::getMailboxMsgBuffer(YouBotSlaveMailboxMsg& mailboxMsg, const unsigned int jointNumber) {
    // Bouml preserved body begin 00049DF1


    if (newMailboxInputDataFlagOne[jointNumber - 1] == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexDataOne);
        mailboxMsg = firstMailboxBufferVector[jointNumber - 1];
        newMailboxInputDataFlagOne[jointNumber - 1] = false;
      }
    } else if (newMailboxInputDataFlagTwo[jointNumber - 1] == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
        mailboxMsg = secondMailboxBufferVector[jointNumber - 1];
        newMailboxInputDataFlagTwo[jointNumber - 1] = false;
      }

    }
    return;
    // Bouml preserved body end 00049DF1
  }

  bool YouBot::sendMailboxMessage(const YouBotSlaveMailboxMsg& mailboxMsg) {
    // Bouml preserved body begin 00052F71
    //  LOG(trace) << "send mailbox message (buffer two) slave " << mailboxMsg.getSlaveNo();
    mailboxBufferSend[0] = mailboxMsg.stctOutput.moduleAddress;
    mailboxBufferSend[1] = mailboxMsg.stctOutput.commandNumber;
    mailboxBufferSend[2] = mailboxMsg.stctOutput.typeNumber;
    mailboxBufferSend[3] = mailboxMsg.stctOutput.motorNumber;
    mailboxBufferSend[4] = mailboxMsg.stctOutput.value >> 24;
    mailboxBufferSend[5] = mailboxMsg.stctOutput.value >> 16;
    mailboxBufferSend[6] = mailboxMsg.stctOutput.value >> 8;
    mailboxBufferSend[7] = mailboxMsg.stctOutput.value & 0xff;
    if (ec_mbxsend(mailboxMsg.getSlaveNo(), &mailboxBufferSend, mailboxTimeout)) {
      return true;
    } else {
      return false;
    }
    // Bouml preserved body end 00052F71
  }

  bool YouBot::receiveMailboxMessage(YouBotSlaveMailboxMsg& mailboxMsg) {
    // Bouml preserved body begin 00052FF1
    if (ec_mbxreceive(mailboxMsg.getSlaveNo(), &mailboxBufferReceive, mailboxTimeout)) {
      //    LOG(trace) << "received mailbox message (buffer two) slave " << mailboxMsg.getSlaveNo();
      mailboxMsg.stctInput.replyAddress = (int) mailboxBufferReceive[0];
      mailboxMsg.stctInput.moduleAddress = (int) mailboxBufferReceive[1];
      mailboxMsg.stctInput.status = (int) mailboxBufferReceive[2];
      mailboxMsg.stctInput.commandNumber = (int) mailboxBufferReceive[3];
      mailboxMsg.stctInput.value = (mailboxBufferReceive[4] << 24 | mailboxBufferReceive[5] << 16 | mailboxBufferReceive[6] << 8 | mailboxBufferReceive[7]);
      return true;
    }
    return false;
    // Bouml preserved body end 00052FF1
  }

  void YouBot::updateSensorActorValues() {
    // Bouml preserved body begin 0003F771

    while (!stopThread) {

      if (ec_iserror())
        LOG(info) << "there is an error in the soem driver";

      if (newDataFlagOne == false) {
        {
          boost::mutex::scoped_lock dataMutex1(mutexDataOne);
          for (unsigned int i = 0; i < joints.size(); i++) {
            //fill first output buffer (send data)
            if (newOutputDataFlagOne[i]) {
              *(ethercatOutputBufferVector[i]) = (firstBufferVector[i]).stctOutput;
            }
            //fill first input buffer (receive data)
            (firstBufferVector[i]).stctInput = *(ethercatInputBufferVector[i]);

            //send mailbox messages from first buffer
            if (newMailboxDataFlagOne[i]) {
              sendMailboxMessage(firstMailboxBufferVector[i]);
              newMailboxDataFlagOne[i] = false;
            }
            //receive mailbox messages to first buffer
            if (receiveMailboxMessage(firstMailboxBufferVector[i])) {
              newMailboxInputDataFlagOne[i] = true;
            }
          }

        }
        newDataFlagOne = true;
        newDataFlagTwo = false;

      } else if (newDataFlagTwo == false) {
        {
          boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
          for (unsigned int i = 0; i < joints.size(); i++) {
            //fill second output buffer (send data)
            if (newOutputDataFlagTwo[i]) {
              *(ethercatOutputBufferVector[i]) = (secondBufferVector[i]).stctOutput;
            }
            //fill second input buffer (receive data)
            (secondBufferVector[i]).stctInput = *(ethercatInputBufferVector[i]);

            //send mailbox messages from second buffer
            if (newMailboxDataFlagTwo[i]) {
              sendMailboxMessage(secondMailboxBufferVector[i]);
              newMailboxDataFlagTwo[i] = false;
            }
            //receive mailbox messages to second buffer
            if (receiveMailboxMessage(secondMailboxBufferVector[i])) {
              newMailboxInputDataFlagTwo[i] = true;
            }
          }
        }
        newDataFlagTwo = true;
        newDataFlagOne = false;
      }

      /*
      int timestamp = 0;
      if (ec_slave[7].activeports & PORTM0){
      timestamp = ec_slave[7].DCrtA;
    }
    if (ec_slave[7].activeports & PORTM3){
      timestamp = ec_slave[7].DCrtD;
    }
    if (ec_slave[7].activeports & PORTM1){
      timestamp = ec_slave[7].DCrtB;
    }
    if (ec_slave[7].activeports & PORTM2){
      timestamp = ec_slave[7].DCrtC;
    }
     //  printf("activeports:%i DCrtA:%i DCrtB:%d DCrtC:%d DCrtD:%d\n", (int)ec_slave[cnt].activeports, ec_slave[cnt].DCrtA, ec_slave[cnt].DCrtB, ec_slave[cnt].DCrtC, ec_slave[cnt].DCrtD);
        printf("timestamp Joint 7:%i\n", timestamp);
       */


      //send and receive data from ethercat
      if (ec_send_processdata() == 0)
        throw ExceptionOODL("Sending process data failed");
      if (ec_receive_processdata(EC_TIMEOUTRET) == 0)
        throw ExceptionOODL("Receiving data failed");

      boost::this_thread::sleep(boost::posix_time::milliseconds(timeTillNextEthercatUpdate));
    }
    // Bouml preserved body end 0003F771
  }

} // namespace brics_oodl
