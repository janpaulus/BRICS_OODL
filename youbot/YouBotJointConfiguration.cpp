
#include "youbot/YouBotJointConfiguration.hpp"
namespace brics_oodl {

YouBotJointConfiguration::YouBotJointConfiguration() {
  // Bouml preserved body begin 0004B871
    this->gearRatio = 1;
    this->encoderTicksPerRound = 0;
  // Bouml preserved body end 0004B871
}

YouBotJointConfiguration::~YouBotJointConfiguration() {
  // Bouml preserved body begin 0004B8F1
  // Bouml preserved body end 0004B8F1
}

void YouBotJointConfiguration::setGearRatio(const double ratio) {
  // Bouml preserved body begin 0004BC71
  if(ratio == 0){
    throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
  }else{
    this->gearRatio = ratio;
  }
  // Bouml preserved body end 0004BC71
}

double YouBotJointConfiguration::getGearRatio() const {
  // Bouml preserved body begin 0004BCF1
  return this->gearRatio;
  // Bouml preserved body end 0004BCF1
}

unsigned int YouBotJointConfiguration::getEncoderTicksPerRound() const {
  // Bouml preserved body begin 0004BD71
  return this->encoderTicksPerRound;
  // Bouml preserved body end 0004BD71
}

void YouBotJointConfiguration::setEncoderTicksPerRound(const unsigned int ticksPerRound) {
  // Bouml preserved body begin 0004BDF1
  this->encoderTicksPerRound = ticksPerRound;
  // Bouml preserved body end 0004BDF1
}

void YouBotJointConfiguration::setMaximumPositioningSpeed(const quantity<angular_velocity>& maximumPositioningSpeed) {
  // Bouml preserved body begin 00052E71
  YouBotSlaveMailboxMsg mailboxMsgBuffer;
  mailboxMsgBuffer.stctOutput.commandNumber = SAP;
  mailboxMsgBuffer.stctOutput.moduleAddress = DRIVE;
  mailboxMsgBuffer.stctOutput.typeNumber = 4; //maximum positioning speed
  mailboxMsgBuffer.stctOutput.value = (int)maximumPositioningSpeed.value(); //TODO do convertion in to radian_per_second
  mailboxMsgVector.push_back(mailboxMsgBuffer);
  // Bouml preserved body end 00052E71
}

void YouBotJointConfiguration::getMaximumPositioningSpeed(quantity<angular_velocity>& maxPositioningSpeed) {
  // Bouml preserved body begin 00052EF1
  maxPositioningSpeed = this->maximumPositioningSpeed;
  // Bouml preserved body end 00052EF1
}

void YouBotJointConfiguration::getPParameterFirstParametersPositionControl(double& PParameter) {
  // Bouml preserved body begin 00054971
  PParameter = this->PParameterFirstParametersPositionControl;
  // Bouml preserved body end 00054971
}


} // namespace brics_oodl
