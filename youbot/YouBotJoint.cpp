
#include "youbot/YouBotJoint.hpp"
#include "youbot/YouBot.hpp"
namespace brics_oodl {

YouBotJoint::YouBotJoint(unsigned int jointNo) {
  // Bouml preserved body begin 000412F1
    this->jointNumber = jointNo;
    mailboxMsgBuffer  = new YouBotSlaveMailboxMsg(0);
  // Bouml preserved body end 000412F1
}

YouBotJoint::~YouBotJoint() {
  // Bouml preserved body begin 00041371
  // Bouml preserved body end 00041371
}

//please use a YouBotJointConfiguration
void YouBotJoint::setConfiguration(const JointConfiguration& configuration) {
  // Bouml preserved body begin 0004BA71
    throw ExceptionOODL("Please provide a YouBotJointConfiguration");

  // Bouml preserved body end 0004BA71
}

//please use a YouBotJointConfiguration
void YouBotJoint::getConfiguration(JointConfiguration& configuration) {
  // Bouml preserved body begin 0004BAF1

    configuration.setGearRatio(this->config.getGearRatio());
    configuration.jointName = this->config.jointName;
    configuration.validRanges = this->config.validRanges;

  // Bouml preserved body end 0004BAF1
}

//sets the configuration for one joint
//@param configuration the joint configuration
void YouBotJoint::setConfiguration(const YouBotJointConfiguration& configuration) {
  // Bouml preserved body begin 0003C0F1
    this->config = configuration;
    if (config.setPositionReferenceToZero) {
      this->messageBuffer.stctOutput.controllerMode = SET_POSITION_TO_REFERENCE;
      this->messageBuffer.stctOutput.positionOrSpeed = 0;
      YouBot::getInstance().setMsgBuffer(this->messageBuffer, this->jointNumber);
    }
  // Bouml preserved body end 0003C0F1
}

//to get the configuration for one joint
//@param configuration returns the joint configuration by reference
void YouBotJoint::getConfiguration(YouBotJointConfiguration& configuration) {
  // Bouml preserved body begin 0003C171
 /*   mailboxMsgBuffer->stctOutput.commandNumber = 6;
    mailboxMsgBuffer->stctOutput.moduleAddress = 0; //0 : Drive  1 : Gripper
    mailboxMsgBuffer->stctOutput.motorNumber = 0; //(always 0)
    mailboxMsgBuffer->stctOutput.typeNumber = 4;
    mailboxMsgBuffer->stctOutput.value = 1000;
    YouBot::getInstance().setMailboxMsgBuffer(*mailboxMsgBuffer, this->jointNumber);


    YouBot::getInstance().getMailboxMsgBuffer(*mailboxMsgBuffer, this->jointNumber);
    LOG(trace) << "CommandNumber " << (int)mailboxMsgBuffer->stctInput.commandNumber
            << " moduleAddress " << (int)mailboxMsgBuffer->stctInput.moduleAddress
            << " replyAddress " << (int)mailboxMsgBuffer->stctInput.replyAddress
            << " status " << (int)mailboxMsgBuffer->stctInput.status
            << " value " << mailboxMsgBuffer->stctInput.value; */
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

///commands a position or angle to one joint
///@param data the to command position
///@param communicationMode at the moment only non blocking communication is implemented
void YouBotJoint::setData(const JointAngleSetpoint& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C1F1
    this->messageBuffer.stctOutput.controllerMode = POSITION_CONTROL;
    this->messageBuffer.stctOutput.positionOrSpeed = (int32) (data.angle.value() / (2.0 * M_PI) * config.getGearRatio() * config.getEncoderTicksPerRound());

    //jointValue / (2 * M_PI) * (joints[jointID - 1].gearRatio * encoderSteps);

    YouBot::getInstance().setMsgBuffer(this->messageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C1F1
}

///gets the position or angle of one joint with have been calculated for the actual encoder value 
///@param data returns the angle by reference
void YouBotJoint::getData(JointSensedAngle& data) {
  // Bouml preserved body begin 0003DCF1
    this->messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    if (config.getGearRatio() == 0) {
      throw ExceptionOODL("A Gear Ratio of zero is not allowed");
    }
    if (config.getEncoderTicksPerRound() == 0) {
      throw ExceptionOODL("Zero Encoder Ticks per Round are not allowed");
    }

    data.angle = ((double) this->messageBuffer.stctInput.actualPosition /config.getEncoderTicksPerRound()) * config.getGearRatio()* (2.0 * M_PI)  * radian;
  // Bouml preserved body end 0003DCF1
}

///commands a velocity to one joint
///@param data the to command velocity
///@param communicationMode at the moment only non blocking communication is implemented
void YouBotJoint::setData(const JointVelocitySetpoint& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C371

    this->messageBuffer.stctOutput.controllerMode = VELOCITY_CONTROL;

    if (config.getGearRatio() == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    this->messageBuffer.stctOutput.positionOrSpeed = (data.angularVelocity.value() / (config.getGearRatio() * 2.0 * M_PI)) * 60.0;
    YouBot::getInstance().setMsgBuffer(this->messageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C371
}

///gets the velocity of one joint with have been calculated for the actual encoder values
///@param data returns the velocity by reference
void YouBotJoint::getData(JointSensedVelocity& data) {
  // Bouml preserved body begin 0003DD71
    this->messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    if (config.getGearRatio() == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    double motorRPM = this->messageBuffer.stctInput.actualVelocity;
    //convert RPM of the motor to radian per second of the wheel/joint
    data.angularVelocity = ((motorRPM / 60.0) * config.getGearRatio() * 2.0 * M_PI) * radian_per_second;
  // Bouml preserved body end 0003DD71
}

///gets temperature of the motor which have been measured by a thermometer
///@param data returns the actual temperature by reference
void YouBotJoint::getData(JointSensedTemperature& data) {
  // Bouml preserved body begin 0003C271
    this->messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    //the formular is taken from the TMCM-174/841: EtherCAT Communication Protocol
    data.temperature = (25.0 + (((this->messageBuffer.stctInput.driverTemperature - 1.43) / (3.3 * 4095)) / 0.0043)) * boost::units::celsius::degree;

  // Bouml preserved body end 0003C271
}

///gets the motor current of one joint with have been measured by a hal sensor
///@param data returns the actual motor current by reference
void YouBotJoint::getData(JointSensedCurrent& data) {
  // Bouml preserved body begin 0003DDF1
    this->messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();
    //convert mili ampere to ampere
    data.current = this->messageBuffer.stctInput.actualCurrent / 1000.0 * ampere;
  // Bouml preserved body end 0003DDF1
}

void YouBotJoint::parseYouBotErrorFlags() {
  // Bouml preserved body begin 00044AF1
    std::stringstream errorMessageStream;
    errorMessageStream << "Joint " << this->jointNumber << " ";
    std::string errorMessage;
    errorMessage = errorMessageStream.str();


    if (this->messageBuffer.stctInput.errorFlags & OVER_CURRENT) {
      LOG(error) << errorMessage << "got over current";
      //    throw ExceptionOODL(errorMessage + "got over current");
    }

    if (this->messageBuffer.stctInput.errorFlags & UNDER_VOLTAGE) {
      LOG(error) << errorMessage << "got under voltage";
      //    throw ExceptionOODL(errorMessage + "got under voltage");
    }

    if (this->messageBuffer.stctInput.errorFlags & OVER_VOLTAGE) {
      LOG(error) << errorMessage << "got over voltage";
      //   throw ExceptionOODL(errorMessage + "got over voltage");
    }

    if (this->messageBuffer.stctInput.errorFlags & OVER_TEMPERATURE) {
      LOG(error) << errorMessage << "got over temperature";
      //   throw ExceptionOODL(errorMessage + "got over temperature");
    }

    if (this->messageBuffer.stctInput.errorFlags & HALTED) {
      //   LOG(error) << errorMessage << "is halted";
      //   throw ExceptionOODL(errorMessage + "is halted");
    }

    if (this->messageBuffer.stctInput.errorFlags & HALL_SENSOR) {
      LOG(error) << errorMessage << "got hall sensor problem";
      //   throw ExceptionOODL(errorMessage + "got hall sensor problem");
    }

    if (this->messageBuffer.stctInput.errorFlags & ENCODER) {
      LOG(error) << errorMessage << "got encoder problem";
      //   throw ExceptionOODL(errorMessage + "got encoder problem");
    }

    if (this->messageBuffer.stctInput.errorFlags & MOTOR_WINDING) {
      LOG(error) << errorMessage << "got motor winding problem";
      //   throw ExceptionOODL(errorMessage + "got motor winding problem");
    }

    if (this->messageBuffer.stctInput.errorFlags & CYCLE_TIME_VIOLATION) {
      LOG(error) << errorMessage << "the cycle time is violated";
      //   throw ExceptionOODL(errorMessage + "the cycle time is violated");
    }

    if (this->messageBuffer.stctInput.errorFlags & INIT_SIN_COMM) {
      LOG(error) << errorMessage << "need to initialize the sinus commutation";
      //   throw ExceptionOODL(errorMessage + "need to initialize the sinus commutation");
    }

  // Bouml preserved body end 00044AF1
}


} // namespace brics_oodl
