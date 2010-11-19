
#include "youbot/YouBotJointConfiguration.hpp"
namespace brics_oodl {

YouBotJointConfiguration::YouBotJointConfiguration() {
  // Bouml preserved body begin 0004B871
    this->gearRatio = 1;
    this->encoderTicksPerRound = 0;
    this->encoderTicksPerRoundBeenSet = false;
    this->gearRatioBeenSet = false;
    this->jointNameBeenSet = false;
    this->PositionReferenceToZeroBeenSet = true;
  // Bouml preserved body end 0004B871
}

YouBotJointConfiguration::~YouBotJointConfiguration() {
  // Bouml preserved body begin 0004B8F1
  // Bouml preserved body end 0004B8F1
}

void YouBotJointConfiguration::setGearRatio(const double ratio) {
  // Bouml preserved body begin 0004BC71
    if (ratio == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    } else {
      this->gearRatio = ratio;
      this->gearRatioBeenSet = true;
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
    this->encoderTicksPerRoundBeenSet = true;
  // Bouml preserved body end 0004BDF1
}

void YouBotJointConfiguration::setMaximumPositioningSpeed(const quantity<angular_velocity>& maximumPositioningSpeed) {
  // Bouml preserved body begin 00052E71
    YouBotSlaveMailboxMsg mailboxMsg;
    mailboxMsg.stctOutput.commandNumber = SAP;
    mailboxMsg.stctOutput.moduleAddress = DRIVE;
    mailboxMsg.stctOutput.typeNumber = 4; //maximum positioning speed
    mailboxMsg.stctOutput.value = (int) maximumPositioningSpeed.value(); //TODO do convertion in to radian_per_second
    mailboxMsg.parameterName = "MaximumPositioningSpeed";
    unsigned int i = 0;
    //find existing mailbox message and replace or attach new one
    if(findMailboxMsg(SAP, DRIVE, 4, i)){
      mailboxMsgVector[i] = mailboxMsg;
    }else{
      mailboxMsgVector.push_back(mailboxMsg);
    }
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

void YouBotJointConfiguration::setPositionReferenceToZero(const bool yesOrNo) {
  // Bouml preserved body begin 00056471
    this->PositionReferenceToZero = yesOrNo;
    this->PositionReferenceToZeroBeenSet = true;
  // Bouml preserved body end 00056471
}

void YouBotJointConfiguration::setJointName(const std::string jointName) {
  // Bouml preserved body begin 000564F1
    this->jointName = jointName;
    this->jointNameBeenSet = true;
  // Bouml preserved body end 000564F1
}

void YouBotJointConfiguration::getJointName(std::string& jointName) {
  // Bouml preserved body begin 00056571
    jointName = this->jointName;
  // Bouml preserved body end 00056571
}

bool YouBotJointConfiguration::findMailboxMsg(const uint8& commandNumber, const uint8& moduleAddress, const uint8& typeNumber, unsigned int& vectorIndex) {
  // Bouml preserved body begin 000565F1
    for (unsigned int i = 0; i < mailboxMsgVector.size(); i++) {
      if (mailboxMsgVector[i].stctOutput.typeNumber == typeNumber &&
              mailboxMsgVector[i].stctOutput.moduleAddress == moduleAddress &&
              mailboxMsgVector[i].stctOutput.commandNumber == commandNumber) {
        vectorIndex = i;
        return true;
      }
    }
    return false;
  // Bouml preserved body end 000565F1
}


} // namespace brics_oodl
