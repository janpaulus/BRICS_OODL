
#include "youbot/YouBotJoint.hpp"
#include "youbot/YouBot.hpp"
namespace brics_oodl {

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
  // Bouml preserved body begin 0004BA71
    throw ExceptionOODL("Please provide a YouBotJointConfiguration");

  // Bouml preserved body end 0004BA71
}

void YouBotJoint::getConfiguration(JointConfiguration& configuration) {
  // Bouml preserved body begin 0004BAF1

    configuration.setGearRatio(this->config.getGearRatio());
    configuration.JointName = this->config.JointName;
    configuration.ValidRanges = this->config.ValidRanges;

  // Bouml preserved body end 0004BAF1
}

void YouBotJoint::setConfiguration(const YouBotJointConfiguration& configuration) {
  // Bouml preserved body begin 0003C0F1
    this->config = configuration;
    if (config.SetPositionReferenceToZero) {
      this->MessageBuffer.stctOutput.controllerMode = SET_POSITION_TO_REFERENCE;
      this->MessageBuffer.stctOutput.positionOrSpeed = 0;
      YouBot::getInstance().setMsgBuffer(this->MessageBuffer, this->jointNumber);
    }
  // Bouml preserved body end 0003C0F1
}

void YouBotJoint::getConfiguration(YouBotJointConfiguration& configuration) {
  // Bouml preserved body begin 0003C171
 /*   YouBotSlaveMailboxMsg msg;
    msg.stctOutput.commandNumber = 5;
    msg.stctOutput.moduleAddress = 0;
    msg.stctOutput.motorNumber = 0;
    msg.stctOutput.typeNumber = 6;
    msg.stctOutput.value = 1000;
    YouBot::getInstance().setMailboxMsgBuffer(msg, this->jointNumber);


    msg = YouBot::getInstance().getMailboxMsgBuffer(this->jointNumber);
    LOG(trace) << "CommandNumber " << msg.stctInput.commandNumber
            << "moduleAddress " << msg.stctInput.moduleAddress
            << "replyAddress " << msg.stctInput.replyAddress
            << "status " << msg.stctInput.status
            << "value " << msg.stctInput.value;*/
    configuration = this->config;

  // Bouml preserved body end 0003C171
}

void YouBotJoint::setData(const JointDataSetpoint& data, SyncMode communicationMode) {
  // Bouml preserved body begin 000413F1
    LOG(info) << "Nothing to do";
  // Bouml preserved body end 000413F1
}

void YouBotJoint::getData(JointData& data) {
  // Bouml preserved body begin 00041471
    LOG(info) << "Nothing to do";
  // Bouml preserved body end 00041471
}

void YouBotJoint::setData(const JointAngleSetpoint& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C1F1
    this->MessageBuffer.stctOutput.controllerMode = POSITION_CONTROL;
    this->MessageBuffer.stctOutput.positionOrSpeed = (int32) (data.angle.value() / (2.0 * M_PI) * config.getGearRatio() * config.getEncoderTicksPerRound());

    //jointValue / (2 * M_PI) * (joints[jointID - 1].gearRatio * encoderSteps);

    YouBot::getInstance().setMsgBuffer(this->MessageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C1F1
}

void YouBotJoint::getData(JointSensedAngle& data) {
  // Bouml preserved body begin 0003DCF1
    this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    if (config.getGearRatio() == 0) {
      throw ExceptionOODL("A Gear Ratio of zero is not allowed");
    }
    if (config.getEncoderTicksPerRound() == 0) {
      throw ExceptionOODL("Zero Encoder Ticks per Round are not allowed");
    }

    data.angle = ((double) this->MessageBuffer.stctInput.actualPosition / (config.getGearRatio() * config.getEncoderTicksPerRound())) * (2.0 * M_PI) * radian;
  // Bouml preserved body end 0003DCF1
}

void YouBotJoint::setData(const JointVelocitySetpoint& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C371

    this->MessageBuffer.stctOutput.controllerMode = VELOCITY_CONTROL;

    if (config.getGearRatio() == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    this->MessageBuffer.stctOutput.positionOrSpeed = (data.angularVelocity.value() / (config.getGearRatio() * 2.0 * M_PI)) * 60.0;
    YouBot::getInstance().setMsgBuffer(this->MessageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C371
}

void YouBotJoint::getData(JointSensedVelocity& data) {
  // Bouml preserved body begin 0003DD71
    this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    if (config.getGearRatio() == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    double motorRPM = this->MessageBuffer.stctInput.actualVelocity;
    //convert RPM of the motor to radian per second of the wheel/joint
    data.angularVelocity = ((motorRPM / 60.0) * config.getGearRatio() * 2.0 * M_PI) * radian_per_second;
  // Bouml preserved body end 0003DD71
}

void YouBotJoint::getData(JointSensedTemperature& data) {
  // Bouml preserved body begin 0003C271
    this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    //the formular is taken from the TMCM-174/841: EtherCAT Communication Protocol
    data.temperature = (25.0 + (((this->MessageBuffer.stctInput.driverTemperature - 1.43) / (3.3 * 4095)) / 0.0043)) * boost::units::celsius::degree;

  // Bouml preserved body end 0003C271
}

void YouBotJoint::getData(JointSensedCurrent& data) {
  // Bouml preserved body begin 0003DDF1
    this->MessageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();
    //convert mili ampere to ampere
    data.current = this->MessageBuffer.stctInput.actualCurrent / 1000.0 * ampere;
  // Bouml preserved body end 0003DDF1
}

void YouBotJoint::parseYouBotErrorFlags() {
  // Bouml preserved body begin 00044AF1
    std::stringstream errorMessageStream;
    errorMessageStream << "Joint " << this->jointNumber << " ";
    std::string errorMessage;
    errorMessage = errorMessageStream.str();


    if (this->MessageBuffer.stctInput.errorFlags & OVER_CURRENT) {
      LOG(error) << errorMessage << "got over current";
      //    throw ExceptionOODL(errorMessage + "got over current");
    }

    if (this->MessageBuffer.stctInput.errorFlags & UNDER_VOLTAGE) {
      LOG(error) << errorMessage << "got under voltage";
      //    throw ExceptionOODL(errorMessage + "got under voltage");
    }

    if (this->MessageBuffer.stctInput.errorFlags & OVER_VOLTAGE) {
      LOG(error) << errorMessage << "got over voltage";
      //   throw ExceptionOODL(errorMessage + "got over voltage");
    }

    if (this->MessageBuffer.stctInput.errorFlags & OVER_TEMPERATURE) {
      LOG(error) << errorMessage << "got over temperature";
      //   throw ExceptionOODL(errorMessage + "got over temperature");
    }

    if (this->MessageBuffer.stctInput.errorFlags & HALTED) {
      //   LOG(error) << errorMessage << "is halted";
      //   throw ExceptionOODL(errorMessage + "is halted");
    }

    if (this->MessageBuffer.stctInput.errorFlags & HALL_SENSOR) {
      LOG(error) << errorMessage << "got hall sensor problem";
      //   throw ExceptionOODL(errorMessage + "got hall sensor problem");
    }

    if (this->MessageBuffer.stctInput.errorFlags & ENCODER) {
      LOG(error) << errorMessage << "got encoder problem";
      //   throw ExceptionOODL(errorMessage + "got encoder problem");
    }

    if (this->MessageBuffer.stctInput.errorFlags & MOTOR_WINDING) {
      LOG(error) << errorMessage << "got motor winding problem";
      //   throw ExceptionOODL(errorMessage + "got motor winding problem");
    }

    if (this->MessageBuffer.stctInput.errorFlags & CYCLE_TIME_VIOLATION) {
      LOG(error) << errorMessage << "the cycle time is violated";
      //   throw ExceptionOODL(errorMessage + "the cycle time is violated");
    }

    if (this->MessageBuffer.stctInput.errorFlags & INIT_SIN_COMM) {
      LOG(error) << errorMessage << "need to initialize the sinus commutation";
      //   throw ExceptionOODL(errorMessage + "need to initialize the sinus commutation");
    }

  // Bouml preserved body end 00044AF1
}


} // namespace brics_oodl
