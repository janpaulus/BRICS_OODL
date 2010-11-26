
#include "youbot/YouBotJointParameter.hpp"
namespace brics_oodl {

YouBotJointParameter::YouBotJointParameter() {
  // Bouml preserved body begin 0005BB71
  // Bouml preserved body end 0005BB71
}

YouBotJointParameter::~YouBotJointParameter() {
  // Bouml preserved body begin 0005BBF1
  // Bouml preserved body end 0005BBF1
}

JointName::JointName() {
  // Bouml preserved body begin 0005C0F1
    this->name = "JointName";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 0005C0F1
}

JointName::~JointName() {
  // Bouml preserved body begin 0005C171
  // Bouml preserved body end 0005C171
}

void JointName::getParameter(std::string& parameter) const {
  // Bouml preserved body begin 0005C1F1
    parameter = this->value;
  // Bouml preserved body end 0005C1F1
}

void JointName::setParameter(const std::string parameter) {
  // Bouml preserved body begin 0005C271
    this->value = parameter;
  // Bouml preserved body end 0005C271
}

GearRatio::GearRatio() {
  // Bouml preserved body begin 0005BDF1
    this->name = "GearRatio";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 0005BDF1
}

GearRatio::~GearRatio() {
  // Bouml preserved body begin 0005BE71
  // Bouml preserved body end 0005BE71
}

void GearRatio::getParameter(double& parameter) const {
  // Bouml preserved body begin 0005BEF1
    parameter = this->value;
  // Bouml preserved body end 0005BEF1
}

void GearRatio::setParameter(const double parameter) {
  // Bouml preserved body begin 0005BF71
    if (parameter == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    this->value = parameter;
  // Bouml preserved body end 0005BF71
}

EncoderTicksPerRound::EncoderTicksPerRound() {
  // Bouml preserved body begin 0005C3F1
    this->name = "EncoderTicksPerRound";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 0005C3F1
}

EncoderTicksPerRound::~EncoderTicksPerRound() {
  // Bouml preserved body begin 0005C471
  // Bouml preserved body end 0005C471
}

void EncoderTicksPerRound::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0005C4F1
    parameter = this->value;
  // Bouml preserved body end 0005C4F1
}

void EncoderTicksPerRound::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0005C571
    if (parameter == 0) {
      throw ExceptionOODL("Zero Encoder Ticks per Round are not allowed");
    }
    this->value = parameter;
  // Bouml preserved body end 0005C571
}

InverseMovementDirection::InverseMovementDirection() {
  // Bouml preserved body begin 0005C6F1
    this->name = "InverseMovementDirection";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 0005C6F1
}

InverseMovementDirection::~InverseMovementDirection() {
  // Bouml preserved body begin 0005C771
  // Bouml preserved body end 0005C771
}

void InverseMovementDirection::getParameter(bool& parameter) const {
  // Bouml preserved body begin 0005C7F1
    parameter = this->value;
  // Bouml preserved body end 0005C7F1
}

void InverseMovementDirection::setParameter(const bool parameter) {
  // Bouml preserved body begin 0005C871
    this->value = parameter;
  // Bouml preserved body end 0005C871
}

MaximumPositioningSpeed::MaximumPositioningSpeed() {
  // Bouml preserved body begin 0005A171
    this->name = "MaximumPositioningSpeed";
    this->lowerLimit = 0 * radian_per_second;
    this->upperLimit = 500 * radian_per_second;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0005A171
}

MaximumPositioningSpeed::~MaximumPositioningSpeed() {
  // Bouml preserved body begin 0005A1F1
  // Bouml preserved body end 0005A1F1
}

void MaximumPositioningSpeed::getParameter(quantity<angular_velocity>& parameter) const {
  // Bouml preserved body begin 00059CF1
    parameter = this->value;
  // Bouml preserved body end 00059CF1
}

void MaximumPositioningSpeed::setParameter(const quantity<angular_velocity>& parameter) {
  // Bouml preserved body begin 00059C71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 00059C71
}

void MaximumPositioningSpeed::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0005A0F1

  if(msgType == SET_MESSAGE){
    message.stctOutput.commandNumber = SAP;
  }else if(msgType == GET_MESSAGE){
    message.stctOutput.commandNumber = GAP;
  }
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 4; //maximum positioning speed
    message.stctOutput.value = (int) value.value(); //TODO do convertion in to radian_per_second

  // Bouml preserved body end 0005A0F1
}

void MaximumPositioningSpeed::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0005A071
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == TMCL_STATUS_OK) {
      this->value = message.stctInput.value * radian_per_second; //TODO do convertion in to radian_per_second
    }
  // Bouml preserved body end 0005A071
}

PParameterFirstParametersPositionControl::PParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 0005C9F1
    this->name = "MaximumPositioningSpeed";
    this->lowerLimit = 0;
    this->upperLimit = 5000 ;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0005C9F1
}

PParameterFirstParametersPositionControl::~PParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 0005CA71
  // Bouml preserved body end 0005CA71
}

void PParameterFirstParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0005CAF1
    parameter = this->value;
  // Bouml preserved body end 0005CAF1
}

void PParameterFirstParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0005CB71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0005CB71
}

void PParameterFirstParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0005CBF1

  if(msgType == SET_MESSAGE){
    message.stctOutput.commandNumber = SAP;
  }else if(msgType == GET_MESSAGE){
    message.stctOutput.commandNumber = GAP;
  }
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 130; //PParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0005CBF1
}

void PParameterFirstParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0005CC71
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == TMCL_STATUS_OK) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 0005CC71
}

CalibrateJoint::CalibrateJoint() {
  // Bouml preserved body begin 00061F71
    this->name = "CalibrateJoint";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 00061F71
}

CalibrateJoint::~CalibrateJoint() {
  // Bouml preserved body begin 00061FF1
  // Bouml preserved body end 00061FF1
}

void CalibrateJoint::getParameter(bool& doCalibration, CalibrationDirection& calibrationDirection, quantity<si::current>& maxCurrent) const {
  // Bouml preserved body begin 00062071
    doCalibration = this->doCalibration;
    calibrationDirection = this->calibrationDirection;
    maxCurrent = this->maxCurrent;
  // Bouml preserved body end 00062071
}

void CalibrateJoint::setParameter(const bool doCalibration, CalibrationDirection calibrationDirection, const quantity<si::current>& maxCurrent) {
  // Bouml preserved body begin 000620F1
    this->doCalibration = doCalibration;
    this->calibrationDirection = calibrationDirection;
    this->maxCurrent = maxCurrent;
  // Bouml preserved body end 000620F1
}

JointLimits::JointLimits() {
  // Bouml preserved body begin 00063EF1
    this->name = "JointLimits";
    this->parameterType = API_PARAMETER;
    this->lowerLimit = 0;
    this->upperLimit = 0;
  // Bouml preserved body end 00063EF1
}

JointLimits::~JointLimits() {
  // Bouml preserved body begin 00063F71
  // Bouml preserved body end 00063F71
}

void JointLimits::getParameter(int& lowerLimit, int& upperLimit) const {
  // Bouml preserved body begin 00063FF1
    lowerLimit = this->lowerLimit;
    upperLimit = this->upperLimit;
  // Bouml preserved body end 00063FF1
}

void JointLimits::setParameter(const int lowerLimit, const int upperLimit) {
  // Bouml preserved body begin 00064071
    this->lowerLimit = lowerLimit;
    this->upperLimit = upperLimit;
  // Bouml preserved body end 00064071
}

StopJoint::StopJoint() {
  // Bouml preserved body begin 00065C71
    this->name = "StopJoint";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 00065C71
}

StopJoint::~StopJoint() {
  // Bouml preserved body begin 00065CF1
  // Bouml preserved body end 00065CF1
}

void StopJoint::getParameter(bool& parameter) const {
  // Bouml preserved body begin 00065D71
    parameter = this->value;
  // Bouml preserved body end 00065D71
}

void StopJoint::setParameter(const bool parameter) {
  // Bouml preserved body begin 00065DF1
    this->value = parameter;
  // Bouml preserved body end 00065DF1
}

NoMoreAction::NoMoreAction() {
  // Bouml preserved body begin 00066071
    this->name = "NoMoreAction";
    this->parameterType = API_PARAMETER;
  // Bouml preserved body end 00066071
}

NoMoreAction::~NoMoreAction() {
  // Bouml preserved body begin 000660F1
  // Bouml preserved body end 000660F1
}

void NoMoreAction::getParameter(bool& parameter) const {
  // Bouml preserved body begin 00066171
    parameter = this->value;
  // Bouml preserved body end 00066171
}

void NoMoreAction::setParameter(const bool parameter) {
  // Bouml preserved body begin 000661F1
    this->value = parameter;
  // Bouml preserved body end 000661F1
}


} // namespace brics_oodl
