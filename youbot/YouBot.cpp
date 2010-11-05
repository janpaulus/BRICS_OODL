
#include "youbot/YouBot.h"
YouBot::YouBot() {
  // Bouml preserved body begin 00041171
  {
    boost::mutex::scoped_lock lock_it(mutexEthercatMaster);
    ethercatMaster == NULL;
  }
  ethernetDeviceName = "eth0";
  stopThread = false;

  // Bouml preserved body end 00041171
}

YouBot::~YouBot() {
  // Bouml preserved body begin 000411F1
  this->closeEthercat();
  // Bouml preserved body end 000411F1
}

void YouBot::setMsgBuffer(const YouBotSlaveMsg& msgBuffer, unsigned int jointNumber) {
  // Bouml preserved body begin 000414F1

  {
    boost::mutex::scoped_lock dataMutex1(mutexData);
    msgBufferVector[jointNumber - 1] = msgBuffer;
  }

  // Bouml preserved body end 000414F1
}

YouBotSlaveMsg YouBot::getMsgBuffer(unsigned int jointNumber) {
  // Bouml preserved body begin 00041571

  YouBotSlaveMsg returnMsg;

  {
    boost::mutex::scoped_lock dataMutex1(mutexData);
    returnMsg = msgBufferVector[jointNumber - 1];
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


    Joints.assign(nrOfSlaves, YouBotJoint());
    msgBufferVector.assign(nrOfSlaves, YouBotSlaveMsg());




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
  {
    boost::mutex::scoped_lock lock_it(mutexEthercatMaster);

    while (!stopThread) {
      for(unsigned int i = 0; i < nrOfSlaves; i++){
        (ethercatMaster.drivers_[i])->update(&(msgBufferVector[i]));
      }
      ethercatMaster->update();
      boost::this_thread::sleep(boost::posix_time::milliseconds(timeTillNextEthercatUpdate));
    }

  }
  // Bouml preserved body end 0003F771
}

