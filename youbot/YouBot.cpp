
#include "youbot/YouBot.hpp"

namespace brics_oodl {

YouBot* YouBot::instance = 0;
YouBot::YouBot() {
  // Bouml preserved body begin 00041171
    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
      ethercatMaster == NULL;
    }
    ethernetDevice = "eth0";
    stopThread = false;
    newDataFlagOne = false;
    newDataFlagTwo = false;
    mailboxSendTimeout = 4000;
    if (!configfile.load("youbot/config/youbot-configfile.cfg"))
      throw ExceptionOODL("config/youbot-configfile.cfg file no found");


  // Bouml preserved body end 00041171
}

YouBot::~YouBot() {
  // Bouml preserved body begin 000411F1
    this->closeEthercat();
  // Bouml preserved body end 000411F1
}

YouBot& YouBot::getInstance(std::string ethernetDeviceName)
{
  // Bouml preserved body begin 00042F71
    if (!instance) {
      ethernetDevice = ethernetDeviceName;
      instance = new YouBot();
      instance->initializeEthercat();
      instance->initializeJoints();
      instance->initializeKinematic();
    }
    return *instance;

  // Bouml preserved body end 00042F71
}

void YouBot::destroy()
{
  // Bouml preserved body begin 00042FF1
    if (instance) {
      delete instance;
    }
    instance = 0;

  // Bouml preserved body end 00042FF1
}

unsigned int YouBot::getNumberOfJoints() {
  // Bouml preserved body begin 00044A71
    return this->Joints.size();
  // Bouml preserved body end 00044A71
}

YouBotJoint& YouBot::getJoint(unsigned int jointNumber) {
  // Bouml preserved body begin 000449F1
    if (jointNumber <= 0 || jointNumber > (this->Joints.size() + 1)) {
      throw ExceptionOODL("Invalid Joint Number");
    }

    return Joints[jointNumber - 1];
  // Bouml preserved body end 000449F1
}

void YouBot::setBaseVelocity(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 0004DD71


    std::vector<quantity<angular_velocity> > wheelVelocities;
    JointVelocitySetpoint setVel;

    YouBotBaseKinematic.cartesianVelocityToWheelVelocities(longitudinalVelocity, transversalVelocity, angularVelocity, wheelVelocities);
    setVel.angularVelocity = wheelVelocities[0];
    this->getJoint(1).setData(setVel, NON_BLOCKING);
    setVel.angularVelocity = wheelVelocities[1];
    this->getJoint(2).setData(setVel, NON_BLOCKING);
    setVel.angularVelocity = wheelVelocities[2];
    this->getJoint(3).setData(setVel, NON_BLOCKING);
    setVel.angularVelocity = wheelVelocities[3];
    this->getJoint(4).setData(setVel, NON_BLOCKING);
  // Bouml preserved body end 0004DD71
}

void YouBot::setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber) {
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

YouBotSlaveMsg YouBot::getMsgBuffer(unsigned int jointNumber) {
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

void YouBot::setMailboxMsgBuffer(const YouBotSlaveMailboxMsg& msgBuffer, unsigned int jointNumber) {
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

    } else {
      return;
    }

  // Bouml preserved body end 00049D71
}

YouBotSlaveMailboxMsg YouBot::getMailboxMsgBuffer(unsigned int jointNumber) {
  // Bouml preserved body begin 00049DF1

    YouBotSlaveMailboxMsg returnMsg;

    if (newMailboxInputDataFlagOne[jointNumber - 1] == true) {
      {
        boost::mutex::scoped_lock dataMutex1(mutexDataOne);
        returnMsg = firstMailboxBufferVector[jointNumber - 1];
        newMailboxInputDataFlagOne[jointNumber - 1] = false;
      }
    } else if (newMailboxInputDataFlagTwo[jointNumber - 1] == true) {
      {
        boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
        returnMsg = secondMailboxBufferVector[jointNumber - 1];
        newMailboxInputDataFlagTwo[jointNumber - 1] = false;
      }

    } else {
      return returnMsg;
    }

    return returnMsg;
  // Bouml preserved body end 00049DF1
}

void YouBot::initializeEthercat() {
  // Bouml preserved body begin 000410F1

    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
      ethercatMaster = new EthercatMaster();

      if (!ethercatMaster->init(ethernetDevice.c_str())) {
        throw ExceptionOODL("Could not initialize Ethercat at " + ethernetDevice);
        return;
      }

      std::string desiredSlaveName = "TMCM-174";
      std::string actualSlaveName;
      nrOfSlaves = 0;
      YouBotSlaveMsg emptySlaveMsg;
      YouBotSlaveMailboxMsg emptyMailboxSlaveMsg;

      for (unsigned int cnt = 1; cnt <= ec_slavecount; cnt++) {
        //   printf("Slave:%d Name:%s Output size:%3dbits Input size:%3dbits State:%2d delay:%d.%d\n",
        //           cnt, ec_slave[cnt].name, ec_slave[cnt].Obits, ec_slave[cnt].Ibits,
        //           ec_slave[cnt].state, (int) ec_slave[cnt].pdelay, ec_slave[cnt].hasdc);

        actualSlaveName = ec_slave[cnt].name;
        if (actualSlaveName == desiredSlaveName && ec_slave[cnt].Obits > 0 && ec_slave[cnt].Ibits > 0) {
          nrOfSlaves++;
          Joints.push_back(YouBotJoint(nrOfSlaves));

          firstBufferVector.push_back(emptySlaveMsg);
          secondBufferVector.push_back(emptySlaveMsg);
          ethercatOutputBufferVector.push_back((outputBuffer*) (ec_slave[cnt].outputs));
          ethercatinputBufferVector.push_back((inputBuffer*) (ec_slave[cnt].inputs));
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
    }
    return;
  // Bouml preserved body end 000410F1
}

void YouBot::initializeJoints() {
  // Bouml preserved body begin 000464F1

    LOG(info) << "Initializing Joints";

    //Configure Joint Parameters
    std::string jointName;

    for (unsigned int i = 0; i < nrOfSlaves; i++) {
      std::stringstream jointNameStream;
      jointNameStream << "Joint " << i + 1;
      jointName = jointNameStream.str();
      YouBotJointConfiguration config;
      configfile.setSection(jointName.c_str());
      config.setGearRatio(configfile.getDoubleValue("GearRatio"));
      config.setEncoderTicksPerRound(configfile.getIntValue("EncoderTicksPerRound"));
      config.setPositionReferenceToZero = configfile.getBoolValue("PositionReferenceToZero");

      Joints[i].setConfiguration(config);
    }

    //Switch to Velocity control because of "Sinuskommutierung"
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    JointVelocitySetpoint vel;
    vel.angularVelocity = 0 * radian_per_second;

    for (unsigned int i = 0; i < nrOfSlaves; i++) {
      Joints[i].setData(vel, NON_BLOCKING);
    }




    //TODO: Calibrate YouBot Manipulator


    //TODO: Initilize Gripper
    return;
  // Bouml preserved body end 000464F1
}

void YouBot::initializeKinematic() {
  // Bouml preserved body begin 0004DDF1
    FourSwedishWheelOmniBaseKinematicConfiguration kinematicConfig;

    //read the kinematics parameter from a config file
    configfile.setSection("YouBotKinematic");
    kinematicConfig.RotationRatio = configfile.getIntValue("RotationRatio");
    kinematicConfig.SlideRatio = configfile.getIntValue("SlideRatio");
    kinematicConfig.lengthBetweenFrontAndRearWheels = configfile.getDoubleValue("LengthBetweenFrontAndRearWheels_[meter]") * meter;
    kinematicConfig.lengthBetweenFrontWheels = configfile.getDoubleValue("LengthBetweenFrontWheels_[meter]") * meter;
    kinematicConfig.wheelRadius = configfile.getDoubleValue("WheelRadius_[meter]") * meter;

    YouBotBaseKinematic.setConfiguration(kinematicConfig);
  // Bouml preserved body end 0004DDF1
}

bool YouBot::closeEthercat() {
  // Bouml preserved body begin 00041271
    stopThread = true;

    threads.join_all();

    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
      if (ethercatMaster != NULL)
        delete ethercatMaster;
    }
  // Bouml preserved body end 00041271
}

void YouBot::updateSensorActorValues() {
  // Bouml preserved body begin 0003F771

    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);

      while (!stopThread) {
        if (newDataFlagOne == false) {
          {
            boost::mutex::scoped_lock dataMutex1(mutexDataOne);
            for (unsigned int i = 0; i < nrOfSlaves; i++) {
              if (newOutputDataFlagOne[i]) {
                *(ethercatOutputBufferVector[i]) = (firstBufferVector[i]).stctOutput;
              }
              (firstBufferVector[i]).stctInput = *(ethercatinputBufferVector[i]);

              //send Mailbox Messages
              if (newMailboxDataFlagOne[i]) {
                LOG(trace) << "send mailbox message buffer one";
                mailboxBufferSend[0] = firstMailboxBufferVector[i].stctOutput.moduleAddress;
                mailboxBufferSend[1] = firstMailboxBufferVector[i].stctOutput.commandNumber;
                mailboxBufferSend[2] = firstMailboxBufferVector[i].stctOutput.typeNumber;
                mailboxBufferSend[3] = firstMailboxBufferVector[i].stctOutput.motorNumber;
                mailboxBufferSend[4] = firstMailboxBufferVector[i].stctOutput.value >> 24;
                mailboxBufferSend[5] = firstMailboxBufferVector[i].stctOutput.value >> 16;
                mailboxBufferSend[6] = firstMailboxBufferVector[i].stctOutput.value >> 8;
                mailboxBufferSend[7] = firstMailboxBufferVector[i].stctOutput.value & 0xff;
                ec_mbxsend(i, &mailboxBufferSend, mailboxSendTimeout);
                newMailboxDataFlagOne[i] = false;

                if (ec_mbxreceive(i, &mailboxBufferReceive, mailboxSendTimeout)) {
                  LOG(trace) << "received mailbox message buffer one";
                  firstMailboxBufferVector[i].stctOutput.moduleAddress = mailboxBufferReceive[0];
                  firstMailboxBufferVector[i].stctOutput.commandNumber = mailboxBufferReceive[1];
                  firstMailboxBufferVector[i].stctOutput.typeNumber = mailboxBufferReceive[2];
                  firstMailboxBufferVector[i].stctOutput.motorNumber = mailboxBufferReceive[3];
                  firstMailboxBufferVector[i].stctOutput.value = *((int32*) &(mailboxBufferReceive[4]));
                  newMailboxInputDataFlagOne[i] = true;
                }
              }
            }

          }
          newDataFlagOne = true;
          newDataFlagTwo = false;

        } else if (newDataFlagTwo == false) {
          {
            boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
            for (unsigned int i = 0; i < nrOfSlaves; i++) {
              if (newOutputDataFlagTwo[i]) {
                *(ethercatOutputBufferVector[i]) = (secondBufferVector[i]).stctOutput;
              }
              (secondBufferVector[i]).stctInput = *(ethercatinputBufferVector[i]);

              //send Mailbox Messages
              if (newMailboxDataFlagTwo[i]) {
                LOG(trace) << "send mailbox message buffer two";
                mailboxBufferSend[0] = secondMailboxBufferVector[i].stctOutput.moduleAddress;
                mailboxBufferSend[1] = secondMailboxBufferVector[i].stctOutput.commandNumber;
                mailboxBufferSend[2] = secondMailboxBufferVector[i].stctOutput.typeNumber;
                mailboxBufferSend[3] = secondMailboxBufferVector[i].stctOutput.motorNumber;
                mailboxBufferSend[4] = secondMailboxBufferVector[i].stctOutput.value >> 24;
                mailboxBufferSend[5] = secondMailboxBufferVector[i].stctOutput.value >> 16;
                mailboxBufferSend[6] = secondMailboxBufferVector[i].stctOutput.value >> 8;
                mailboxBufferSend[7] = secondMailboxBufferVector[i].stctOutput.value & 0xff;
                ec_mbxsend(i, &mailboxBufferSend, mailboxSendTimeout);
                newMailboxDataFlagTwo[i] = false;



                if (ec_mbxreceive(i, &mailboxBufferReceive, mailboxSendTimeout)) {
                  LOG(trace) << "received mailbox message buffer two";
                  secondMailboxBufferVector[i].stctOutput.moduleAddress = mailboxBufferReceive[0];
                  secondMailboxBufferVector[i].stctOutput.commandNumber = mailboxBufferReceive[1];
                  secondMailboxBufferVector[i].stctOutput.typeNumber = mailboxBufferReceive[2];
                  secondMailboxBufferVector[i].stctOutput.motorNumber = mailboxBufferReceive[3];
                  secondMailboxBufferVector[i].stctOutput.value = *((int32*) &(mailboxBufferReceive[4]));
                  newMailboxInputDataFlagTwo[i] = true;
                }
              }
            }

          }
          newDataFlagTwo = true;
          newDataFlagOne = false;
        }



        ethercatMaster->update();

        boost::this_thread::sleep(boost::posix_time::milliseconds(timeTillNextEthercatUpdate));
      }

    }
  // Bouml preserved body end 0003F771
}

std::string YouBot::ethernetDevice;


} // namespace brics_oodl
