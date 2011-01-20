
#include "youbot/YouBotJointParameterReadOnly.hpp"
namespace brics_oodl {

YouBotJointParameterReadOnly::YouBotJointParameterReadOnly() {
  // Bouml preserved body begin 0006FDF1
  // Bouml preserved body end 0006FDF1
}

YouBotJointParameterReadOnly::~YouBotJointParameterReadOnly() {
  // Bouml preserved body begin 0006FE71
  // Bouml preserved body end 0006FE71
}

ArePIDcontrollersActive::ArePIDcontrollersActive() {
  // Bouml preserved body begin 000700F1
    this->name = "ArePIDcontrollersActive";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000700F1
}

ArePIDcontrollersActive::~ArePIDcontrollersActive() {
  // Bouml preserved body begin 00070171
  // Bouml preserved body end 00070171
}

void ArePIDcontrollersActive::getParameter(bool& parameter) const {
  // Bouml preserved body begin 000701F1
    parameter = this->value;
  // Bouml preserved body end 000701F1
}

void ArePIDcontrollersActive::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 000702F1

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 147; //ArePIDcontrollersActive
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 000702F1
}

void ArePIDcontrollersActive::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 00070371
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 00070371
}

CommutationMode::CommutationMode() {
  // Bouml preserved body begin 000704F1
    this->name = "CommutationMode";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000704F1
}

CommutationMode::~CommutationMode() {
  // Bouml preserved body begin 00070571
  // Bouml preserved body end 00070571
}

void CommutationMode::getParameter(int& parameter) const {
  // Bouml preserved body begin 000705F1
    parameter = this->value;
  // Bouml preserved body end 000705F1
}

void CommutationMode::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00070671

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 159; //CommutationMode
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00070671
}

void CommutationMode::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 000720F1
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 000720F1
}

PWMSchemeBlockCommutation::PWMSchemeBlockCommutation() {
  // Bouml preserved body begin 000707F1
    this->name = "PWMSchemeBlockCommutation";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000707F1
}

PWMSchemeBlockCommutation::~PWMSchemeBlockCommutation() {
  // Bouml preserved body begin 00070871
  // Bouml preserved body end 00070871
}

void PWMSchemeBlockCommutation::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 000708F1
    parameter = this->value;
  // Bouml preserved body end 000708F1
}

void PWMSchemeBlockCommutation::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00070971

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 167; //PWMSchemeBlockCommutation
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00070971
}

void PWMSchemeBlockCommutation::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 00072171
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 00072171
}

MotorContollerGearRatio::MotorContollerGearRatio() {
  // Bouml preserved body begin 00070AF1
    this->name = "MotorContollerGearRatio";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 00070AF1
}

MotorContollerGearRatio::~MotorContollerGearRatio() {
  // Bouml preserved body begin 00070B71
  // Bouml preserved body end 00070B71
}

void MotorContollerGearRatio::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 00070BF1
    parameter = this->value;
  // Bouml preserved body end 00070BF1
}

void MotorContollerGearRatio::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00070C71

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 211; //MotorContollerGearRatio
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00070C71
}

void MotorContollerGearRatio::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 000721F1
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 000721F1
}

MotorCoilResistance::MotorCoilResistance() {
  // Bouml preserved body begin 00070DF1
    this->name = "MotorCoilResistance";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 00070DF1
}

MotorCoilResistance::~MotorCoilResistance() {
  // Bouml preserved body begin 00070E71
  // Bouml preserved body end 00070E71
}

void MotorCoilResistance::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 00070EF1
    parameter = this->value;
  // Bouml preserved body end 00070EF1
}

void MotorCoilResistance::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00070F71

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 240; //MotorCoilResistance
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00070F71
}

void MotorCoilResistance::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 00072271
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 00072271
}

InitializationMode::InitializationMode() {
  // Bouml preserved body begin 000710F1
    this->name = "InitializationMode";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000710F1
}

InitializationMode::~InitializationMode() {
  // Bouml preserved body begin 00071171
  // Bouml preserved body end 00071171
}

void InitializationMode::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 000711F1
    parameter = this->value;
  // Bouml preserved body end 000711F1
}

void InitializationMode::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00071271

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 249; //InitializationMode
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00071271
}

void InitializationMode::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 000722F1
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 000722F1
}

EncoderResolution::EncoderResolution() {
  // Bouml preserved body begin 000713F1
    this->name = "EncoderResolution";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000713F1
}

EncoderResolution::~EncoderResolution() {
  // Bouml preserved body begin 00071471
  // Bouml preserved body end 00071471
}

void EncoderResolution::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 000714F1
    parameter = this->value;
  // Bouml preserved body end 000714F1
}

void EncoderResolution::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00071571

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 250; //EncoderResolution
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00071571
}

void EncoderResolution::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 00072371
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 00072371
}

ReversingEncoderDirection::ReversingEncoderDirection() {
  // Bouml preserved body begin 000716F1
    this->name = "ReversingEncoderDirection";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000716F1
}

ReversingEncoderDirection::~ReversingEncoderDirection() {
  // Bouml preserved body begin 00071771
  // Bouml preserved body end 00071771
}

void ReversingEncoderDirection::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 000717F1
    parameter = this->value;
  // Bouml preserved body end 000717F1
}

void ReversingEncoderDirection::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00071871

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 251; //ReversingEncoderDirection
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00071871
}

void ReversingEncoderDirection::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 000723F1
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 000723F1
}

MotorPoles::MotorPoles() {
  // Bouml preserved body begin 000719F1
    this->name = "MotorPoles";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 000719F1
}

MotorPoles::~MotorPoles() {
  // Bouml preserved body begin 00071A71
  // Bouml preserved body end 00071A71
}

void MotorPoles::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 00071AF1
    parameter = this->value;
  // Bouml preserved body end 00071AF1
}

void MotorPoles::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00071B71
    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 253; //MotorPoles
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00071B71
}

void MotorPoles::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 00072471
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 00072471
}

HallSensorPolarityReversal::HallSensorPolarityReversal() {
  // Bouml preserved body begin 00071CF1
    this->name = "HallSensorPolarityReversal";
    this->parameterType = MOTOR_CONTOLLER_PARAMETER;
  // Bouml preserved body end 00071CF1
}

HallSensorPolarityReversal::~HallSensorPolarityReversal() {
  // Bouml preserved body begin 00071D71
  // Bouml preserved body end 00071D71
}

void HallSensorPolarityReversal::getParameter(unsigned int& parameter) const {
  // Bouml preserved body begin 00071DF1
    parameter = this->value;
  // Bouml preserved body end 00071DF1
}

void HallSensorPolarityReversal::getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {
  // Bouml preserved body begin 00071E71

    message.stctOutput.commandNumber = msgType;
    message.stctOutput.moduleAddress = DRIVE;
    message.stctOutput.typeNumber = 254; //RampGeneratorSpeedAndPositionControl
    message.stctOutput.value = value; //TODO do convertion

  // Bouml preserved body end 00071E71
}

void HallSensorPolarityReversal::setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {
  // Bouml preserved body begin 000724F1
    if (message.stctOutput.commandNumber == message.stctInput.commandNumber && message.stctInput.status == NO_ERROR) {
      this->value = message.stctInput.value; //TODO do convertion
    }
  // Bouml preserved body end 000724F1
}


} // namespace brics_oodl
