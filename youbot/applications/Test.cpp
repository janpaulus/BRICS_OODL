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
    quantity<si::angular_velocity> angularVelocity = 0 * radian_per_second;
    quantity<si::velocity> sensedLongitudinalVelocity;
    quantity<si::velocity> sensedTransversalVelocity;
    quantity<si::angular_velocity> sensedAngularVelocity;


    while (running) {

      for (unsigned int i = 1; i <= youbot4.getNumberOfJoints(); i++) {
        youbot4.getBaseJoint(i).getData(temp);
        youbot4.getBaseJoint(i).getData(angle);
        youbot4.getBaseJoint(i).getData(vel);
        youbot4.getBaseJoint(i).getData(current);
    //    std::cout << "Joint: " << i << " Temp: " << temp.temperature
    //            << " Angle: " << angle.angle
    //            << " Vel: " << vel.angularVelocity
    //            << " Current: " << current.current
     //           << std::endl;
      }

  //    youbot4.getJoint(1).setData(setVel);
  //    youbot4.getJoint(2).setData(setVel);
  //    youbot4.getJoint(3).setData(setVel);
  //    youbot4.getJoint(4).setData(setVel);
      youbot4.setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
      youbot4.getBaseVelocity(sensedLongitudinalVelocity, sensedTransversalVelocity, sensedAngularVelocity);
      std::cout << "Vel: Longi: " << sensedLongitudinalVelocity
                << " Trans: " << sensedTransversalVelocity
                << " Angular: " << sensedAngularVelocity << std::endl;


      // youbot4.getJoint(3).getConfiguration(config);
      boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }

    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    setVel.angularVelocity = 0 * radian_per_second;
    youbot4.getJoint(1).setData(setVel);
    youbot4.getJoint(2).setData(setVel);
    youbot4.getJoint(3).setData(setVel);
    youbot4.getJoint(4).setData(setVel);

    boost::this_thread::sleep(boost::posix_time::milliseconds(500));


  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }


  return 0;
}