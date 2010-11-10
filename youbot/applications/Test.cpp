#include <iostream>
#include <vector>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "generic-joint/JointData.hpp"
#include "youbot/YouBot.hpp"
#include "youbot/YouBotJoint.hpp"


using namespace boost::posix_time;
using namespace std;
using namespace brics_oodl;

bool running = true;

void sigintHandler(int signal) {
  running = false;
}

int main() {

  try{
  (Logger::getInstance()).init();

  YouBot& youbot4 = YouBot::getInstance();

  //  std::cout << youbot4.getNumberOfJoints() << std::endl;
  JointSensedTemperature temp;
  JointSensedAngle angle;
  JointSensedVelocity vel;
  JointSensedCurrent current;
  JointVelocitySetpoint setVel;
  JointConfiguration config;
  setVel.angularVelocity = 00 *radian_per_second;

  while (running) {

    for (unsigned int i = 1; i <= youbot4.getNumberOfJoints(); i++) {
      youbot4.getJoint(i).getData(temp);
      youbot4.getJoint(i).getData(angle);
      youbot4.getJoint(i).getData(vel);
      youbot4.getJoint(i).getData(current);
      std::cout << "J " << i << " Temp: " << temp.temperature
              << " Angle: " << angle.angle
              << " Vel: " << vel.angularVelocity
              << " Current: " << current.current
              << std::endl;
    }
    youbot4.getJoint(1).setData(setVel,NON_BLOCKING);
    youbot4.getJoint(2).setData(setVel,NON_BLOCKING);
    youbot4.getJoint(3).setData(setVel,NON_BLOCKING);
    youbot4.getJoint(4).setData(setVel,NON_BLOCKING);
  
  
 // youbot4.getJoint(3).getConfiguration(config);
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
  }

  }catch(std::exception e){
    LOG(fatal) << e.what();
  }catch(...){
    LOG(fatal) << "unhandled exception";
  }


  return 0;
}