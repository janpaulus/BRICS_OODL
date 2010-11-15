#include <iostream>
#include <vector>
#include <signal.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "youbot/YouBot.hpp"



using namespace boost::posix_time;
using namespace std;
using namespace brics_oodl;

bool running = true;

void sigintHandler(int signal) {
  running = false;

  std::cout << " Interrupt!" << std::endl;

}

int main() {

  signal(SIGINT, sigintHandler);
  signal(SIGQUIT, sigintHandler);
  signal(SIGABRT, sigintHandler);
  signal(SIGTERM, sigintHandler);
  signal(SIGSTOP, sigintHandler);
  signal(SIGTSTP, sigintHandler);
  signal(SIGKILL, sigintHandler);

  try {

    YouBot& youbot4 = YouBot::getInstance();

    //  std::cout << youbot4.getNumberOfJoints() << std::endl;
    JointSensedTemperature temp;
    JointSensedAngle angle;
    JointSensedVelocity vel;
    JointSensedCurrent current;
    JointVelocitySetpoint setVel;
    JointAngleSetpoint setangle;
    YouBotJointConfiguration config;
    setangle.angle = 2.0 * M_PI *radian;
    setVel.angularVelocity = 0 * M_PI *radian_per_second;

    quantity<si::velocity> longitudinalVelocity = 0 * meter_per_second;
    quantity<si::velocity> transversalVelocity = 0 * meter_per_second;
    quantity<si::angular_velocity> angularVelocity = 0.2 * radian_per_second;


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

  //    youbot4.getJoint(1).setData(setVel, NON_BLOCKING);
  //    youbot4.getJoint(2).setData(setVel, NON_BLOCKING);
  //    youbot4.getJoint(3).setData(setVel, NON_BLOCKING);
  //    youbot4.getJoint(4).setData(setVel, NON_BLOCKING);
      youbot4.setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);


      // youbot4.getJoint(3).getConfiguration(config);
      boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    }

    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    setVel.angularVelocity = 0 * radian_per_second;
    youbot4.getJoint(1).setData(setVel, NON_BLOCKING);
    youbot4.getJoint(2).setData(setVel, NON_BLOCKING);
    youbot4.getJoint(3).setData(setVel, NON_BLOCKING);
    youbot4.getJoint(4).setData(setVel, NON_BLOCKING);

    boost::this_thread::sleep(boost::posix_time::milliseconds(2000));

  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }


  return 0;
}