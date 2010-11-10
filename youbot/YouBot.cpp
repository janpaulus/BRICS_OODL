
#include "youbot/YouBot.hpp"
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
  newOutputDataFlagOne = false;
  newOutputDataFlagTwo = false;



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

void YouBot::setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber) {
  // Bouml preserved body begin 000414F1

  if (newDataFlagOne == true) {
    {
      boost::mutex::scoped_lock dataMutex1(mutexDataOne);
      firstBufferVector[jointNumber - 1].stctOutput = msgBuffer.stctOutput;
      newOutputDataFlagOne = true;
      newOutputDataFlagTwo = false;
    }
  } else if (newDataFlagTwo == true) {
    {
      boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
      secondBufferVector[jointNumber - 1].stctOutput = msgBuffer.stctOutput;
      newOutputDataFlagOne = false;
      newOutputDataFlagTwo = true;
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

void YouBot::initializeEthercat() {
  // Bouml preserved body begin 000410F1
  {
    boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
    ethercatMaster = new EthercatMaster();

    if (!ethercatMaster->init(ethernetDevice.c_str())) {
      throw ExceptionOODL("Could not initialize Ethercat at "+ethernetDevice);
      return;
    }

    std::string desiredSlaveName = "TMCM-174";
    std::string actualSlaveName;
    nrOfSlaves = 0;
    YouBotSlaveMsg emptySlaveMsg;

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
      }

    }

    if(nrOfSlaves > 0){
      LOG(info) << "Number of YouBot Joints found: " << nrOfSlaves;
    }else{
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
      //Switch to Velocity control because of "Sinuskommutierung"
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    JointVelocitySetpoint vel;
    vel.angularVelocity = 0 * radian_per_second;

    for (unsigned int i = 0; i < nrOfSlaves; i++) {
      Joints[i].setData(vel, NON_BLOCKING);
    }


    //TODO: Calibrate YouBot Manipulator

    //TODO: Auf Positionskontrolle setzen und NULLEN

    //TODO: Initilize Gripper
    return;
  // Bouml preserved body end 000464F1
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
            if (newOutputDataFlagOne) {
              *(ethercatOutputBufferVector[i]) = (firstBufferVector[i]).stctOutput;
            }
            (firstBufferVector[i]).stctInput = *(ethercatinputBufferVector[i]);
          }

        }
        newDataFlagOne = true;
        newDataFlagTwo = false;

      } else if (newDataFlagTwo == false) {
        {
          boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
          for (unsigned int i = 0; i < nrOfSlaves; i++) {
            if (newOutputDataFlagTwo) {
              *(ethercatOutputBufferVector[i]) = (secondBufferVector[i]).stctOutput;
            }
            (secondBufferVector[i]).stctInput = *(ethercatinputBufferVector[i]);
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

