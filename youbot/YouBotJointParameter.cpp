
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
    if (lowerLimit > upperLimit) {
      throw ExceptionOODL("The lower joint limit it not allowed to be bigger than the upper limit");
    }
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

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 4; //maximum positioning speed
    message.stctOutput.value = (int) value.value(); //TODO do convertion in to radian_per_second

  // Bouml preserved body end 0005A0F1
}

void MaximumPositioningSpeed::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0005A071
    this->value = message.stctInput.value * radian_per_second; //TODO do convertion in to radian_per_second
  // Bouml preserved body end 0005A071
}

MaximumMotorCurrent::MaximumMotorCurrent() {
  // Bouml preserved body begin 0006A5F1
    this->name = "MaximumMotorCurrent";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006A5F1
}

MaximumMotorCurrent::~MaximumMotorCurrent() {
  // Bouml preserved body begin 0006A671
  // Bouml preserved body end 0006A671
}

void MaximumMotorCurrent::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006A6F1
    parameter = this->value;
  // Bouml preserved body end 0006A6F1
}

void MaximumMotorCurrent::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006A771
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006A771
}

void MaximumMotorCurrent::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006A7F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 6; //MaximumMotorCurrent
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006A7F1
}

void MaximumMotorCurrent::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006A871
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006A871
}

SpeedControlSwitchingThreshold::SpeedControlSwitchingThreshold() {
  // Bouml preserved body begin 0006A1F1
    this->name = "SpeedControlSwitchingThreshold";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006A1F1
}

SpeedControlSwitchingThreshold::~SpeedControlSwitchingThreshold() {
  // Bouml preserved body begin 0006A271
  // Bouml preserved body end 0006A271
}

void SpeedControlSwitchingThreshold::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006A2F1
    parameter = this->value;
  // Bouml preserved body end 0006A2F1
}

void SpeedControlSwitchingThreshold::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006A371
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006A371
}

void SpeedControlSwitchingThreshold::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006A3F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 8; //SpeedControlSwitchingThreshold
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006A3F1
}

void SpeedControlSwitchingThreshold::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006A471
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006A471
}

MotorAcceleration::MotorAcceleration() {
  // Bouml preserved body begin 0006A9F1
    this->name = "MotorAcceleration";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006A9F1
}

MotorAcceleration::~MotorAcceleration() {
  // Bouml preserved body begin 0006AA71
  // Bouml preserved body end 0006AA71
}

void MotorAcceleration::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006AAF1
    parameter = this->value;
  // Bouml preserved body end 0006AAF1
}

void MotorAcceleration::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006AB71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006AB71
}

void MotorAcceleration::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006ABF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 11; //MotorAcceleration
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006ABF1
}

void MotorAcceleration::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006AC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006AC71
}

PositionControlSwitchingThreshold::PositionControlSwitchingThreshold() {
  // Bouml preserved body begin 0006F9F1
    this->name = "PositionControlSwitchingThreshold";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006F9F1
}

PositionControlSwitchingThreshold::~PositionControlSwitchingThreshold() {
  // Bouml preserved body begin 0006FA71
  // Bouml preserved body end 0006FA71
}

void PositionControlSwitchingThreshold::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006FAF1
    parameter = this->value;
  // Bouml preserved body end 0006FAF1
}

void PositionControlSwitchingThreshold::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006FB71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006FB71
}

void PositionControlSwitchingThreshold::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006FBF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 12; //PositionControlSwitchingThreshold
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006FBF1
}

void PositionControlSwitchingThreshold::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006FC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006FC71
}

PParameterFirstParametersPositionControl::PParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 0005C9F1
    this->name = "PParameterFirstParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
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

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 130; //PParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0005CBF1
}

void PParameterFirstParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0005CC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0005CC71
}

IParameterFirstParametersPositionControl::IParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 000699F1
    this->name = "IParameterFirstParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000699F1
}

IParameterFirstParametersPositionControl::~IParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 00069A71
  // Bouml preserved body end 00069A71
}

void IParameterFirstParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 00069AF1
    parameter = this->value;
  // Bouml preserved body end 00069AF1
}

void IParameterFirstParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 00069B71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 00069B71
}

void IParameterFirstParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 00069BF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 131; //IParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00069BF1
}

void IParameterFirstParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 00069C71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 00069C71
}

DParameterFirstParametersPositionControl::DParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 00069DF1
    this->name = "DParameterFirstParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 00069DF1
}

DParameterFirstParametersPositionControl::~DParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 00069E71
  // Bouml preserved body end 00069E71
}

void DParameterFirstParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 00069EF1
    parameter = this->value;
  // Bouml preserved body end 00069EF1
}

void DParameterFirstParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 00069F71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 00069F71
}

void DParameterFirstParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 00069FF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 132; //PParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00069FF1
}

void DParameterFirstParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006A071
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006A071
}

PIDControlTime::PIDControlTime() {
  // Bouml preserved body begin 0006ADF1
    this->name = "PIDControlTime";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006ADF1
}

PIDControlTime::~PIDControlTime() {
  // Bouml preserved body begin 0006AE71
  // Bouml preserved body end 0006AE71
}

void PIDControlTime::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006AEF1
    parameter = this->value;
  // Bouml preserved body end 0006AEF1
}

void PIDControlTime::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006AF71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006AF71
}

void PIDControlTime::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006AFF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 133; //PIDControlTime
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006AFF1
}

void PIDControlTime::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006B071
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006B071
}

IClippingParameterFirstParametersPositionControl::IClippingParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 0006B1F1
    this->name = "IClippingParameterFirstParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006B1F1
}

IClippingParameterFirstParametersPositionControl::~IClippingParameterFirstParametersPositionControl() {
  // Bouml preserved body begin 0006B271
  // Bouml preserved body end 0006B271
}

void IClippingParameterFirstParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006B2F1
    parameter = this->value;
  // Bouml preserved body end 0006B2F1
}

void IClippingParameterFirstParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006B371
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006B371
}

void IClippingParameterFirstParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006B3F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 135; //IClippingParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006B3F1
}

void IClippingParameterFirstParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006B471
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006B471
}

PParameterFirstParametersSpeedControl::PParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006B5F1
    this->name = "PParameterFirstParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006B5F1
}

PParameterFirstParametersSpeedControl::~PParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006B671
  // Bouml preserved body end 0006B671
}

void PParameterFirstParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006B6F1
    parameter = this->value;
  // Bouml preserved body end 0006B6F1
}

void PParameterFirstParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006B771
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006B771
}

void PParameterFirstParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006B7F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 140; //PParameterFirstParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006B7F1
}

void PParameterFirstParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006B871
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006B871
}

IParameterFirstParametersSpeedControl::IParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006B9F1
    this->name = "IParameterFirstParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006B9F1
}

IParameterFirstParametersSpeedControl::~IParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006BA71
  // Bouml preserved body end 0006BA71
}

void IParameterFirstParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006BAF1
    parameter = this->value;
  // Bouml preserved body end 0006BAF1
}

void IParameterFirstParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006BB71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006BB71
}

void IParameterFirstParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006BBF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 141; //IParameterFirstParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006BBF1
}

void IParameterFirstParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006BC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006BC71
}

DParameterFirstParametersSpeedControl::DParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006BDF1
    this->name = "DParameterFirstParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006BDF1
}

DParameterFirstParametersSpeedControl::~DParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006BE71
  // Bouml preserved body end 0006BE71
}

void DParameterFirstParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006BEF1
    parameter = this->value;
  // Bouml preserved body end 0006BEF1
}

void DParameterFirstParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006BF71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006BF71
}

void DParameterFirstParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006BFF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 142; //DParameterFirstParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006BFF1
}

void DParameterFirstParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006C071
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006C071
}

IClippingParameterFirstParametersSpeedControl::IClippingParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006C1F1
    this->name = "IClippingParameterFirstParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006C1F1
}

IClippingParameterFirstParametersSpeedControl::~IClippingParameterFirstParametersSpeedControl() {
  // Bouml preserved body begin 0006C271
  // Bouml preserved body end 0006C271
}

void IClippingParameterFirstParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006C2F1
    parameter = this->value;
  // Bouml preserved body end 0006C2F1
}

void IClippingParameterFirstParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006C371
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006C371
}

void IClippingParameterFirstParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006C3F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 143; //IClippingParameterFirstParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006C3F1
}

void IClippingParameterFirstParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006C471
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006C471
}

RampGeneratorSpeedAndPositionControl::RampGeneratorSpeedAndPositionControl() {
  // Bouml preserved body begin 0006C5F1
    this->name = "RampGeneratorSpeedAndPositionControl";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006C5F1
}

RampGeneratorSpeedAndPositionControl::~RampGeneratorSpeedAndPositionControl() {
  // Bouml preserved body begin 0006C671
  // Bouml preserved body end 0006C671
}

void RampGeneratorSpeedAndPositionControl::getParameter(bool& parameter) const {
  // Bouml preserved body begin 0006C6F1
    parameter = this->value;
  // Bouml preserved body end 0006C6F1
}

void RampGeneratorSpeedAndPositionControl::setParameter(const bool parameter) {
  // Bouml preserved body begin 0006C771
    this->value = parameter;
  // Bouml preserved body end 0006C771
}

void RampGeneratorSpeedAndPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006C7F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 146; //RampGeneratorSpeedAndPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006C7F1
}

void RampGeneratorSpeedAndPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006C871
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006C871
}

ReinitializationSinusoidalCommutation::ReinitializationSinusoidalCommutation() {
  // Bouml preserved body begin 0006C9F1
    this->name = "ReinitializationSinusoidalCommutation";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006C9F1
}

ReinitializationSinusoidalCommutation::~ReinitializationSinusoidalCommutation() {
  // Bouml preserved body begin 0006CA71
  // Bouml preserved body end 0006CA71
}

void ReinitializationSinusoidalCommutation::getParameter(bool& parameter) const {
  // Bouml preserved body begin 0006CAF1
    parameter = this->value;
  // Bouml preserved body end 0006CAF1
}

void ReinitializationSinusoidalCommutation::setParameter(const bool parameter) {
  // Bouml preserved body begin 0006CB71
    this->value = parameter;
  // Bouml preserved body end 0006CB71
}

void ReinitializationSinusoidalCommutation::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006CBF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 160; //ReinitializationSinusoidalCommutation
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006CBF1
}

void ReinitializationSinusoidalCommutation::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006CC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006CC71
}

PParameterSecondParametersPositionControl::PParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006CDF1
    this->name = "PParameterSecondParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006CDF1
}

PParameterSecondParametersPositionControl::~PParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006CE71
  // Bouml preserved body end 0006CE71
}

void PParameterSecondParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006CEF1
    parameter = this->value;
  // Bouml preserved body end 0006CEF1
}

void PParameterSecondParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006CF71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006CF71
}

void PParameterSecondParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006CFF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 230; //PParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006CFF1
}

void PParameterSecondParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006D071
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006D071
}

IParameterSecondParametersPositionControl::IParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006D1F1
    this->name = "IParameterSecondParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006D1F1
}

IParameterSecondParametersPositionControl::~IParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006D271
  // Bouml preserved body end 0006D271
}

void IParameterSecondParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006D2F1
    parameter = this->value;
  // Bouml preserved body end 0006D2F1
}

void IParameterSecondParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006D371
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006D371
}

void IParameterSecondParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006D3F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 231; //IParameterSecondParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006D3F1
}

void IParameterSecondParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006D471
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006D471
}

DParameterSecondParametersPositionControl::DParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006D5F1
    this->name = "DParameterSecondParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006D5F1
}

DParameterSecondParametersPositionControl::~DParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006D671
  // Bouml preserved body end 0006D671
}

void DParameterSecondParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006D6F1
    parameter = this->value;
  // Bouml preserved body end 0006D6F1
}

void DParameterSecondParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006D771
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006D771
}

void DParameterSecondParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006D7F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 232; //DParameterSecondParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006D7F1
}

void DParameterSecondParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006D871
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006D871
}

IClippingParameterSecondParametersPositionControl::IClippingParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006D9F1
    this->name = "IClippingParameterSecondParametersPositionControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006D9F1
}

IClippingParameterSecondParametersPositionControl::~IClippingParameterSecondParametersPositionControl() {
  // Bouml preserved body begin 0006DA71
  // Bouml preserved body end 0006DA71
}

void IClippingParameterSecondParametersPositionControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006DAF1
    parameter = this->value;
  // Bouml preserved body end 0006DAF1
}

void IClippingParameterSecondParametersPositionControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006DB71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006DB71
}

void IClippingParameterSecondParametersPositionControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006DBF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 233; //IClippingParameterSecondParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006DBF1
}

void IClippingParameterSecondParametersPositionControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006DC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006DC71
}

PParameterSecondParametersSpeedControl::PParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006DDF1
    this->name = "PParameterSecondParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006DDF1
}

PParameterSecondParametersSpeedControl::~PParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006DE71
  // Bouml preserved body end 0006DE71
}

void PParameterSecondParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006DEF1
    parameter = this->value;
  // Bouml preserved body end 0006DEF1
}

void PParameterSecondParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006DF71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006DF71
}

void PParameterSecondParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006DFF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 234; //PParameterSecondParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006DFF1
}

void PParameterSecondParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006E071
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006E071
}

IParameterSecondParametersSpeedControl::IParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006E1F1
    this->name = "IParameterSecondParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006E1F1
}

IParameterSecondParametersSpeedControl::~IParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006E271
  // Bouml preserved body end 0006E271
}

void IParameterSecondParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006E2F1
    parameter = this->value;
  // Bouml preserved body end 0006E2F1
}

void IParameterSecondParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006E371
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006E371
}

void IParameterSecondParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006E3F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 235; //IParameterFirstParametersPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006E3F1
}

void IParameterSecondParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006E471
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006E471
}

DParameterSecondParametersSpeedControl::DParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006E5F1
    this->name = "DParameterSecondParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006E5F1
}

DParameterSecondParametersSpeedControl::~DParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006E671
  // Bouml preserved body end 0006E671
}

void DParameterSecondParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006E6F1
    parameter = this->value;
  // Bouml preserved body end 0006E6F1
}

void DParameterSecondParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006E771
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006E771
}

void DParameterSecondParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006E7F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 236; //DParameterSecondParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006E7F1
}

void DParameterSecondParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006E871
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006E871
}

IClippingParameterSecondParametersSpeedControl::IClippingParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006E9F1
    this->name = "IClippingParameterSecondParametersSpeedControl";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006E9F1
}

IClippingParameterSecondParametersSpeedControl::~IClippingParameterSecondParametersSpeedControl() {
  // Bouml preserved body begin 0006EA71
  // Bouml preserved body end 0006EA71
}

void IClippingParameterSecondParametersSpeedControl::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006EAF1
    parameter = this->value;
  // Bouml preserved body end 0006EAF1
}

void IClippingParameterSecondParametersSpeedControl::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006EB71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006EB71
}

void IClippingParameterSecondParametersSpeedControl::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006EBF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 237; //IClippingParameterSecondParametersSpeedControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006EBF1
}

void IClippingParameterSecondParametersSpeedControl::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006EC71
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006EC71
}

BlockCommutationMaximumSpeed::BlockCommutationMaximumSpeed() {
  // Bouml preserved body begin 0006EDF1
    this->name = "BlockCommutationMaximumSpeed";
    this->lowerLimit = 0 * radian_per_second;
    this->upperLimit = 500 * radian_per_second;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006EDF1
}

BlockCommutationMaximumSpeed::~BlockCommutationMaximumSpeed() {
  // Bouml preserved body begin 0006EE71
  // Bouml preserved body end 0006EE71
}

void BlockCommutationMaximumSpeed::getParameter(quantity<angular_velocity>& parameter) const {
  // Bouml preserved body begin 0006EEF1
    parameter = this->value;
  // Bouml preserved body end 0006EEF1
}

void BlockCommutationMaximumSpeed::setParameter(const quantity<angular_velocity>& parameter) {
  // Bouml preserved body begin 0006EF71
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006EF71
}

void BlockCommutationMaximumSpeed::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006EFF1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 241; //BlockCommutationMaximumSpeed
    message.stctOutput.value = (int) value.value(); //TODO do convertion in to radian_per_second

  // Bouml preserved body end 0006EFF1
}

void BlockCommutationMaximumSpeed::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006F071
    this->value = message.stctInput.value * radian_per_second; //TODO do convertion in to radian_per_second
  // Bouml preserved body end 0006F071
}

CommutationCompensationClockwise::CommutationCompensationClockwise() {
  // Bouml preserved body begin 0006F1F1
    this->name = "CommutationCompensationClockwise";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006F1F1
}

CommutationCompensationClockwise::~CommutationCompensationClockwise() {
  // Bouml preserved body begin 0006F271
  // Bouml preserved body end 0006F271
}

void CommutationCompensationClockwise::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006F2F1
    parameter = this->value;
  // Bouml preserved body end 0006F2F1
}

void CommutationCompensationClockwise::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006F371
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006F371
}

void CommutationCompensationClockwise::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006F3F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 242; //CommutationCompensationClockwise
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006F3F1
}

void CommutationCompensationClockwise::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006F471
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006F471
}

CommutationCompensationCounterClockwise::CommutationCompensationCounterClockwise() {
  // Bouml preserved body begin 0006F5F1
    this->name = "CommutationCompensationCounterClockwise";
    this->lowerLimit = 0;
    this->upperLimit = 5000;
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 0006F5F1
}

CommutationCompensationCounterClockwise::~CommutationCompensationCounterClockwise() {
  // Bouml preserved body begin 0006F671
  // Bouml preserved body end 0006F671
}

void CommutationCompensationCounterClockwise::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 0006F6F1
    parameter = this->value;
  // Bouml preserved body end 0006F6F1
}

void CommutationCompensationCounterClockwise::setParameter(const unsigned int parameter) {
  // Bouml preserved body begin 0006F771
    if (this->lowerLimit > parameter) {
      throw ExceptionOODL("The parameter exceeds the lower limit");
    }
    if (this->upperLimit < parameter) {
      throw ExceptionOODL("The parameter exceeds the upper limit");
    }

    this->value = parameter;
  // Bouml preserved body end 0006F771
}

void CommutationCompensationCounterClockwise::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {
  // Bouml preserved body begin 0006F7F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 243; //CommutationCompensationCounterClockwise
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 0006F7F1
}

void CommutationCompensationCounterClockwise::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0006F871
    this->value = message.stctInput.value; //TODO do convertion
  // Bouml preserved body end 0006F871
}


} // namespace brics_oodl
