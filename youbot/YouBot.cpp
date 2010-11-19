
#include "youbot/YouBot.hpp"

namespace brics_oodl {

YouBot* YouBot::instance = 0;
YouBot::YouBot() {
  // Bouml preserved body begin 00041171

    //Initialize the Logger
    (Logger::getInstance()).init();

    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
      ethercatMaster == NULL;
    }
    ethernetDevice = "eth0";
    timeTillNextEthercatUpdate = 4; //msec
    mailboxTimeout = 4000;  //micro sec
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

YouBot& YouBot::getInstance()
{
  // Bouml preserved body begin 00042F71
    if (!instance) {
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
    YouBotJointConfiguration config;
    std::string name;

    for (int i = 0; i < joints.size(); i++) {
      joints[i].getConfiguration(config);
      config.getJointName(name);
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

///return a joint form the base
///@param jointNumber 1-4 for the base joints
YouBotJoint& YouBot::getBaseJoint(const unsigned int baseJointNumber) {
  // Bouml preserved body begin 0004F771
    if (baseJointNumber <= 0 || baseJointNumber > 4 || baseJointNumber > getNumberOfJoints()) {
      throw ExceptionOODL("Invalid Joint Number");
    }
    return joints[baseJointNumber - 1];
  // Bouml preserved body end 0004F771
}

///return a joint form the arm1
///@param jointNumber 1-5 for the arm1 joints
YouBotJoint& YouBot::getArm1Joint(const unsigned int arm1JointNumber) {
  // Bouml preserved body begin 0004F7F1
    unsigned int jointNumber = arm1JointNumber + 4;
    if (jointNumber <= 4 || jointNumber > 9 || jointNumber > getNumberOfJoints()) {
      throw ExceptionOODL("Invalid Joint Number");
    }
    return joints[jointNumber - 1];
  // Bouml preserved body end 0004F7F1
}

///return a joint form the arm2
///@param jointNumber 1-5 for the arm2 joints
YouBotJoint& YouBot::getArm2Joint(const unsigned int arm2JointNumber) {
  // Bouml preserved body begin 0004F871
    unsigned int jointNumber = arm2JointNumber + 4 + 5;
    if (jointNumber <= 9 || jointNumber > 14 || jointNumber > getNumberOfJoints()) {
      throw ExceptionOODL("Invalid Joint Number");
    }
    return joints[jointNumber - 1];
  // Bouml preserved body end 0004F871
}

///commands the base in cartesien velocities
///@param longitudinalVelocity is the forward or backward velocity
///@param transversalVelocity is the sideway velocity
///@param angularVelocity is the rotational velocity around the center of the YouBot
void YouBot::setBaseVelocity(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 0004DD71

    std::vector<quantity<angular_velocity> > wheelVelocities;
    JointVelocitySetpoint setVel;

    youBotBaseKinematic.cartesianVelocityToWheelVelocities(longitudinalVelocity, transversalVelocity, angularVelocity, wheelVelocities);

    if (wheelVelocities.size() < 4)
      throw ExceptionOODL("To less wheel velocities");

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

///gets the cartesien base velocity
///@param longitudinalVelocity is the forward or backward velocity
///@param transversalVelocity is the sideway velocity
///@param angularVelocity is the rotational velocity around the center of the YouBot
void YouBot::getBaseVelocity(quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<si::angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 00051271

    std::vector<quantity<angular_velocity> > wheelVelocities;
    quantity<angular_velocity> dummy;
    JointSensedVelocity sensedVel;
    wheelVelocities.assign(4, dummy);

    this->getJoint(1).getData(sensedVel);
    wheelVelocities[0] = sensedVel.angularVelocity;
    this->getJoint(2).getData(sensedVel);
    wheelVelocities[1] = sensedVel.angularVelocity;
    this->getJoint(3).getData(sensedVel);
    wheelVelocities[2] = sensedVel.angularVelocity;
    this->getJoint(4).getData(sensedVel);
    wheelVelocities[3] = sensedVel.angularVelocity;

    youBotBaseKinematic.wheelVelocitiesToCartesianVelocity(wheelVelocities, longitudinalVelocity, transversalVelocity, angularVelocity);

  // Bouml preserved body end 00051271
}

///gets the cartesien base position which is calculated from the odometry
///@param longitudinalPosition is the forward or backward position
///@param transversalPosition is the sideway position
///@param orientation is the rotation around the center of the YouBot
void YouBot::getBasePosition(quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation) {
  // Bouml preserved body begin 000514F1

    std::vector<quantity<plane_angle> > wheelPositions;
    quantity<plane_angle> dummy;
    JointSensedAngle sensedPos;
    wheelPositions.assign(4, dummy);

    this->getJoint(1).getData(sensedPos);
    wheelPositions[0] = sensedPos.angle;
    this->getJoint(2).getData(sensedPos);
    wheelPositions[1] = sensedPos.angle;
    this->getJoint(3).getData(sensedPos);
    wheelPositions[2] = sensedPos.angle;
    this->getJoint(4).getData(sensedPos);
    wheelPositions[3] = sensedPos.angle;

    youBotBaseKinematic.wheelPositionsToCartesianPosition(wheelPositions, longitudinalPosition, transversalPosition, orientation);
  // Bouml preserved body end 000514F1
}

void YouBot::initializeEthercat() {
  // Bouml preserved body begin 000410F1

    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
      ethercatMaster = new EthercatMaster();

      if (!ethercatMaster->init(ethernetDevice.c_str())) {
        throw ExceptionOODL("Could not initialize EtherCAT at " + ethernetDevice);
        return;
      }

      std::string desiredSlaveName = "TMCM-174";
      std::string actualSlaveName;
      nrOfSlaves = 0;
      YouBotSlaveMsg emptySlaveMsg;

      desiredSlaveName = configfile.getStringValue("JointControllerName");

      //reserve memory for all joints
      for (unsigned int cnt = 1; cnt <= ec_slavecount; cnt++) {
        //   printf("Slave:%d Name:%s Output size:%3dbits Input size:%3dbits State:%2d delay:%d.%d\n",
        //           cnt, ec_slave[cnt].name, ec_slave[cnt].Obits, ec_slave[cnt].Ibits,
        //           ec_slave[cnt].state, (int) ec_slave[cnt].pdelay, ec_slave[cnt].hasdc);

        actualSlaveName = ec_slave[cnt].name;
        if (actualSlaveName == desiredSlaveName && ec_slave[cnt].Obits > 0 && ec_slave[cnt].Ibits > 0) {
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
    }
    return;
  // Bouml preserved body end 000410F1
}

void YouBot::initializeJoints() {
  // Bouml preserved body begin 000464F1

    LOG(info) << "Initializing Joints";

    //Configure Joint Parameters
    std::string jointName;

    for (unsigned int i = 0; i < joints.size(); i++) {
      std::stringstream jointNameStream;
      jointNameStream << "Joint " << i + 1;
      jointName = jointNameStream.str();
      YouBotJointConfiguration config;
      configfile.setSection(jointName.c_str());
      config.setJointName(configfile.getStringValue("JointName"));
      config.setGearRatio(configfile.getDoubleValue("GearRatio"));
      config.setEncoderTicksPerRound(configfile.getIntValue("EncoderTicksPerRound"));
      config.setPositionReferenceToZero(configfile.getBoolValue("PositionReferenceToZero"));

      joints[i].setConfiguration(config);
    }

    //Switch to Velocity control because of "Sinuskommutierung"
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    JointVelocitySetpoint vel;
    vel.angularVelocity = 0 * radian_per_second;

    for (unsigned int i = 0; i < joints.size(); i++) {
      joints[i].setData(vel, NON_BLOCKING);
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
    kinematicConfig.rotationRatio = configfile.getIntValue("RotationRatio");
    kinematicConfig.slideRatio = configfile.getIntValue("SlideRatio");
    kinematicConfig.lengthBetweenFrontAndRearWheels = configfile.getDoubleValue("LengthBetweenFrontAndRearWheels_[meter]") * meter;
    kinematicConfig.lengthBetweenFrontWheels = configfile.getDoubleValue("LengthBetweenFrontWheels_[meter]") * meter;
    kinematicConfig.wheelRadius = configfile.getDoubleValue("WheelRadius_[meter]") * meter;

    youBotBaseKinematic.setConfiguration(kinematicConfig);
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
    if(ec_mbxsend(mailboxMsg.getSlaveNo(), &mailboxBufferSend, mailboxTimeout)){
      return true;
    }else{
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

    {
      boost::mutex::scoped_lock lock_it(mutexEthercatMaster);

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

        ethercatMaster->update();

        boost::this_thread::sleep(boost::posix_time::milliseconds(timeTillNextEthercatUpdate));
      }

    }
  // Bouml preserved body end 0003F771
}


} // namespace brics_oodl
