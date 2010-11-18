#include <iostream>
#include <vector>
#include <signal.h>
#include "youbot/YouBot.hpp"




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

    YouBot& myYouBot = YouBot::getInstance();

    //  std::cout << myYouBot.getNumberOfJoints() << std::endl;
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

    quantity<si::velocity> longitudinalVel = 0 * meter_per_second;
    quantity<si::velocity> transversalVel = 0 * meter_per_second;
    quantity<si::angular_velocity> angularVel = 0 * radian_per_second;
    quantity<si::length> sensedLongitudinalPos;
    quantity<si::length> sensedTransversalPos;
    quantity<si::plane_angle> sensedAngularPos;

    quantity<si::plane_angle> lastAngle;

    setVel.angularVelocity = 2 * radian_per_second;
    
    double value = 0;;
    myYouBot.getBaseJoint(4).getConfiguration(config);
    config.getMaximumPositioningSpeed(angularVel);
    LOG(trace) << angularVel;
    angularVel = (angularVel.value() + 1) * radian_per_second;
    config.setMaximumPositioningSpeed(angularVel);
    myYouBot.getBaseJoint(4).setConfiguration(config);
    myYouBot.getBaseJoint(4).getConfiguration(config);
    config.getMaximumPositioningSpeed(angularVel);
    LOG(trace) << angularVel;

/*
    while (running) {
/
      for (unsigned int i = 1; i <= myYouBot.getNumberOfJoints(); i++) {
        myYouBot.getBaseJoint(i).getData(temp);
        myYouBot.getBaseJoint(i).getData(angle);
        myYouBot.getBaseJoint(i).getData(vel);
        myYouBot.getBaseJoint(i).getData(current);
        std::cout << "Joint: " << i << " Temp: " << temp.temperature
                << " Angle: " << angle.angle
                << " Vel: " << vel.angularVelocity
                << " Current: " << current.current
                << std::endl;
      }

      SLEEP_MILLISEC(100);
    }
*/
    SLEEP_MILLISEC(500);
    setVel.angularVelocity = 0 * radian_per_second;
    myYouBot.getJoint(1).setData(setVel);
    myYouBot.getJoint(2).setData(setVel);
    myYouBot.getJoint(3).setData(setVel);
    myYouBot.getJoint(4).setData(setVel);

    SLEEP_MILLISEC(500);



  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }


  return 0;
}