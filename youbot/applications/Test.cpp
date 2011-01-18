#include <iostream>
#include <vector>
#include <signal.h>
#include "youbot/YouBotJointParameter.hpp"
#include "youbot/YouBotGripper.hpp"
#include "youbot/YouBotBase.hpp"
#include "youbot/YouBotManipulator.hpp"




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

    YouBotManipulator myYouBotManipulator("youbot-manipulator");
    YouBotBase myYouBotBase("youbot-base");

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

    setVel.angularVelocity = 0 * radian_per_second;


    MaximumPositioningSpeed test;


    YouBotGripper& gripper = myYouBotManipulator.getArmGripper();


    SLEEP_MILLISEC(2000);

    int jointNo = 1;

    JointAngleSetpoint jAngle;
    jAngle.angle = 0.5 *radian;

  //  myYouBot.getArm1Joint(5).setData(setVel);
    LOG(trace) << "move to pose: " << jAngle.angle;
    myYouBotManipulator.getArmJoint(jointNo).setData(jAngle);

    EncoderResolution encRes;

    MotorContollerGearRatio gearRatio;

    myYouBotManipulator.getArmJoint(1).getConfigurationParameter(encRes);
    myYouBotManipulator.getArmJoint(1).getConfigurationParameter(gearRatio);
    unsigned int enc;
    unsigned int gear;
 //   encRes.getParameter(enc);
 //   gearRatio.getParameter(gear);
 //   LOG(trace) << "gearRatio " << gear << "encoderResolution " << enc;


    while (running) {


       for (unsigned int i = 1; i <= 4; i++) {
        myYouBotBase.getBaseJoint(i).getData(temp);
        myYouBotBase.getBaseJoint(i).getData(angle);
        myYouBotBase.getBaseJoint(i).getData(vel);
        myYouBotBase.getBaseJoint(i).getData(current);
        std::cout << "Joint: " << i << " Temp: " << temp.temperature
                << " Angle: " << angle.angle
                << " Vel: " << vel.angularVelocity
                << " Current: " << current.current
                << std::endl;
      }

       myYouBotManipulator.getArmJoint(jointNo).getData(angle);

       std::cout << " Angle: " << angle.angle << std::endl;

      SLEEP_MILLISEC(100);
    }







  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "unhandled exception" << std::endl;
  }


  return 0;
}