
#include "youbot/YouBotJoint.h"
#include "youbot/YouBot.h"
YouBotJoint::YouBotJoint(unsigned int jointNo) {
  // Bouml preserved body begin 000412F1
  this->jointNumber = jointNo;
  // Bouml preserved body end 000412F1
}

YouBotJoint::~YouBotJoint() {
  // Bouml preserved body begin 00041371
  // Bouml preserved body end 00041371
}

void YouBotJoint::setConfiguration(const JointConfiguration& configuration) {
  // Bouml preserved body begin 0003C0F1
  this->configuration = configuration;
  // Bouml preserved body end 0003C0F1
}

void YouBotJoint::getConfiguration(JointConfiguration& configuration) {
  // Bouml preserved body begin 0003C171
  configuration = this->configuration;
  // Bouml preserved body end 0003C171
}

void YouBotJoint::setData(const JointSetpointAngle& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C1F1
  this->MessageBuffer.stctOutput.controllerMode = POSITION_CONTROL;
  this->MessageBuffer.stctOutput.positionOrSpeed = data.angle.value(); //TODO do right convertion

  YouBot::getInstance().setMsgBuffer(this->MessageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C1F1
}

void YouBotJoint::setData(const JointSetpointVelocity& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C371

  this->MessageBuffer.stctOutput.controllerMode = VELOCITY_CONTROL;
  this->MessageBuffer.stctOutput.positionOrSpeed = data.angularVelocity.value(); //TODO do right convertion

  YouBot::getInstance().setMsgBuffer(this->MessageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C371
}

void YouBotJoint::getData(JointSensorTemperature& data) {
  // Bouml preserved body begin 0003C271
  this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);


  data.temperature = (25.0 + ( this->MessageBuffer.stctInput.driverTemperature - 1.43/3.3*4095) / 0.0043) * boost::units::celsius::degree;

  // Bouml preserved body end 0003C271
}

void YouBotJoint::getData(JointSensorAngle& data) {
  // Bouml preserved body begin 0003DCF1
  this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
  data.angle = this->MessageBuffer.stctInput.actualPosition * radian; //TODO do right convertion
  // Bouml preserved body end 0003DCF1
}

void YouBotJoint::getData(JointSensorVelocity& data) {
  // Bouml preserved body begin 0003DD71
  this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);

  double motorRPM = this->MessageBuffer.stctInput.actualVelocity;

  data.angularVelocity =  ((motorRPM/60.0)*configuration.GearRatio) * radian_per_second;
}

void YouBotJoint::getData(JointSensorCurrent& data) {
  // Bouml preserved body begin 0003DDF1
  this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
  //get mili ampere from YouBot convert it o ampere
  data.current = this->MessageBuffer.stctInput.actualCurrent/1000.0 * ampere; 
  // Bouml preserved body end 0003DDF1
}

