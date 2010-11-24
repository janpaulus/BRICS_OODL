#include <iostream>
#include <vector>
#include <signal.h>
#include "youbot/YouBot.hpp"
#include "youbot/YouBotJointParameter.hpp"
#include "youbot/YouBotGripper.hpp"




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


 
   
    MaximumPositioningSpeed test;


    YouBotGripper gripper = myYouBot.getArm1Gripper();
    

    
    GripperBarSpacingSetPoint gripperSetPoint;

    gripperSetPoint.barSpacing = 0.01 *meter;
    gripper.setData(gripperSetPoint);
    SLEEP_MILLISEC(2000);

    gripperSetPoint.barSpacing = 0.024 *meter;
    gripper.setData(gripperSetPoint);
    SLEEP_MILLISEC(2000);

    gripperSetPoint.barSpacing = 0.015 *meter;
    gripper.setData(gripperSetPoint);
    SLEEP_MILLISEC(2000);


    JointAngleSetpoint jAngle;
    jAngle.angle = -10.0*M_PI/180.0 *radian;

 //   SLEEP_MILLISEC(5000);

    myYouBot.getArm1Joint(1).setData(jAngle);

    SLEEP_MILLISEC(5000);

    
    GearRatio name;
    double jname;
    myYouBot.getArm1Joint(2).getConfigurationParameter(name);
    name.getParameter(jname);
    LOG(trace) << jname;

    myYouBot.getBaseJoint(3).getConfigurationParameter(test);
    test.getParameter(angularVel);
    LOG(trace) << angularVel;
    angularVel = (angularVel.value() + 1) * radian_per_second;
    test.setParameter(angularVel);
    myYouBot.getBaseJoint(3).setConfigurationParameter(test);
    myYouBot.getBaseJoint(3).getConfigurationParameter(test);
    test.getParameter(angularVel);
    LOG(trace) << angularVel;


    /*
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
*/
/*
    while (running) {

      for (unsigned int i = 1; i <= 4; i++) {
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

    SLEEP_MILLISEC(500);
    setVel.angularVelocity = 0 * radian_per_second;
    myYouBot.getJoint(1).setData(setVel);
    myYouBot.getJoint(2).setData(setVel);
    myYouBot.getJoint(3).setData(setVel);
    myYouBot.getJoint(4).setData(setVel);

    SLEEP_MILLISEC(500);
*/


  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }


  return 0;
}