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
    quantity<si::length> sensedLongitudinalPos;
    quantity<si::length> sensedTransversalPos;
    quantity<si::plane_angle> sensedAngularPos;

    quantity<si::plane_angle> lastAngle;


setVel.angularVelocity = 2 * radian_per_second;

int i = 0;
    while (i <=10) {

  //    for (unsigned int i = 1; i <= youbot4.getNumberOfJoints(); i++) {
   //     youbot4.getBaseJoint(2).getData(temp);
   //     youbot4.getBaseJoint(2).getData(angle);
   //     youbot4.getBaseJoint(2).getData(vel);
     //   youbot4.getBaseJoint(2).getData(current);
    //    std::cout << "Joint: " << i << " Temp: " << temp.temperature
    //            << " Angle: " << angle.angle
    //            << " Vel: " << vel.angularVelocity
    //            << " Current: " << current.current
     //           << std::endl;
    //  }
      
  //    youbot4.getJoint(2).setData(setVel);

   //   youbot4.getBaseJoint(2).getData(angle);
  //    youbot4.getBaseJoint(2).getData(vel);
   //   youbot4.getJoint(2).setData(setVel);
  //    youbot4.getJoint(2).setData(setVel);
  //    youbot4.getJoint(3).setData(setVel);
  //    youbot4.getJoint(4).setData(setVel);
      youbot4.setBaseVelocity(longitudinalVelocity, transversalVelocity, angularVelocity);
      SLEEP_MILLISEC(1000);
      youbot4.getBasePosition(sensedLongitudinalPos, sensedTransversalPos, sensedAngularPos);
      std::cout << "Pos: Longi: " << sensedLongitudinalPos
                << " Trans: " << sensedTransversalPos
               << " Angular: " << sensedAngularPos << std::endl;

   //   std::cout << " Angle: " << (angle.angle - lastAngle) << " Vel: " << vel.angularVelocity<< std::endl;
   //   lastAngle = angle.angle;

      i++;
      // youbot4.getJoint(3).getConfiguration(config);
      
    }

    SLEEP_MILLISEC(500);
    setVel.angularVelocity = 0 * radian_per_second;
    youbot4.getJoint(1).setData(setVel);
    youbot4.getJoint(2).setData(setVel);
    youbot4.getJoint(3).setData(setVel);
    youbot4.getJoint(4).setData(setVel);

    SLEEP_MILLISEC(500);



  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }


  return 0;
}