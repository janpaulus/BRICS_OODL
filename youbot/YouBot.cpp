
#include "youbot/YouBot.h"
YouBot* YouBot::instance = 0;
YouBot::YouBot() {
  // Bouml preserved body begin 00041171
  {
    boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
    ethercatMaster == NULL;
  }
  ethernetDeviceName = "eth0";
  stopThread = false;
  newDataFlagOne = false;
  newDataFlagTwo = false;

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

void YouBot::setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber) {
  // Bouml preserved body begin 000414F1

  if (newDataFlagOne == true) {
    {
      boost::mutex::scoped_lock dataMutex1(mutexDataOne);
      firstBufferVector[jointNumber - 1] = msgBuffer;
    }
  } else if (newDataFlagTwo == true) {
    {
      boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
      secondBufferVector[jointNumber - 1] = msgBuffer;
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

bool YouBot::initializeEthercat() {
  // Bouml preserved body begin 000410F1
  {
    boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
    ethercatMaster = new soem_ethercat_drivers::SoemMaster();

    if (!ethercatMaster->init(ethernetDeviceName.c_str())) {
      LOG(error) << "could not initialize Ethercat!";
      return false;
    }
    nrOfSlaves = ethercatMaster->drivers_.size();

    for (unsigned int i = 0; i < nrOfSlaves; i++) {
      Joints.push_back(YouBotJoint(i + 1));

      firstBufferVector.push_back(YouBotSlaveMsg());
      secondBufferVector.push_back(YouBotSlaveMsg());
    }


    //TODO: Calibrate YouBot Manipulator

    //TODO: Switch to Velocity control because of "Sinuskommutierung"

    //TODO: Auf Positionskontrolle setzen und NULLEN

    //TODO: Initilize Gripper

    stopThread = false;

    threads.create_thread(boost::bind(&YouBot::updateSensorActorValues, this));
  }
  // Bouml preserved body end 000410F1
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

  std::vector<outputBuffer*> ethercatOutputBufferVector;
  std::vector<inputBuffer*> ethercatinputBufferVector;

  {
    boost::mutex::scoped_lock lock_it(mutexEthercatMaster);

    for (unsigned int i = 0; i < nrOfSlaves; i++) {
      ethercatOutputBufferVector.push_back((outputBuffer*) (ec_slave[i].outputs));
      ethercatinputBufferVector.push_back((inputBuffer*) (ec_slave[i].inputs));
    }



    while (!stopThread) {
      if (newDataFlagOne == false) {
        {
          boost::mutex::scoped_lock dataMutex1(mutexDataOne);
          for (unsigned int i = 0; i < nrOfSlaves; i++) {
            *(ethercatOutputBufferVector[i]) = (firstBufferVector[i]).stctOutput;
            (firstBufferVector[i]).stctInput = *(ethercatinputBufferVector[i]);
          }

        }

        newDataFlagOne = true;
        newDataFlagTwo = false;

      } else if (newDataFlagTwo == false) {
        {
          boost::mutex::scoped_lock dataMutex2(mutexDataTwo);
          for (unsigned int i = 0; i < nrOfSlaves; i++) {
            *(ethercatOutputBufferVector[i]) = (secondBufferVector[i]).stctOutput;
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

