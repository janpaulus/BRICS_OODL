
#include "youbot/YouBotJoint.hpp"
#include "youbot/YouBot.hpp"
namespace brics_oodl {

YouBotJoint::YouBotJoint(unsigned int jointNo) {
  // Bouml preserved body begin 000412F1
    this->jointNumber = jointNo;
    timeTillNextMailboxUpdate = YouBot::getInstance().timeTillNextEthercatUpdate * 2;
    mailboxMsgRetries = 30;
  // Bouml preserved body end 000412F1
}

YouBotJoint::~YouBotJoint() {
  // Bouml preserved body begin 00041371
  // Bouml preserved body end 00041371
}

void YouBotJoint::setConfigurationParameter(const JointParameter& parameter) {
  // Bouml preserved body begin 0005CDF1
  throw ExceptionOODL("Please use YouBotJointParameters");
  // Bouml preserved body end 0005CDF1
}

void YouBotJoint::getConfigurationParameter(JointParameter& parameter) {
  // Bouml preserved body begin 0005CE71
  throw ExceptionOODL("Please use YouBotJointParameters");
  // Bouml preserved body end 0005CE71
}

void YouBotJoint::setConfigurationParameter(const YouBotJointParameter& parameter) {
  // Bouml preserved body begin 0005BC71
    if (parameter.getType() == API_PARAMETER) {
      if (parameter.getName() == "JointName") {
        this->jointName = static_cast<const JointName&> (parameter).value;
      } else if (parameter.getName() == "GearRatio") {
        this->gearRatio = static_cast<const GearRatio&> (parameter).value;
      } else if (parameter.getName() == "EncoderTicksPerRound") {
        this->encoderTicksPerRound = static_cast<const EncoderTicksPerRound&> (parameter).value;
      } else if (parameter.getName() == "PositionReferenceToZero") {
        this->positionReferenceToZero = static_cast<const PositionReferenceToZero&> (parameter).value;
        if (this->positionReferenceToZero) {
          YouBotSlaveMsg messageBuffer;
          messageBuffer.stctOutput.controllerMode = SET_POSITION_TO_REFERENCE;
          messageBuffer.stctOutput.positionOrSpeed = 0;
          YouBot::getInstance().setMsgBuffer(messageBuffer, this->jointNumber);
          this->positionReferenceToZero = false;
        }
      }
    } else if (parameter.getType() == MOTOR_CONTOLLER_PARAMETER) {

      YouBotSlaveMailboxMsg message;
      parameter.getYouBotMailboxMsg(message, SET_MESSAGE);

      if (!setValueToMotorContoller(message)) {
        throw ExceptionOODL("Unable to set parameter: " + parameter.getName() + " to joint: " + this->jointName);
      }
    }
  // Bouml preserved body end 0005BC71
}

void YouBotJoint::getConfigurationParameter(YouBotJointParameter& parameter) {
  // Bouml preserved body begin 0005BCF1
    if (parameter.getType() == API_PARAMETER) {
      if (parameter.getName() == "JointName") {
        static_cast<JointName&> (parameter).setParameter(this->jointName);
      } else if (parameter.getName() == "GearRatio") {
        static_cast<GearRatio&> (parameter).setParameter(this->gearRatio);
      } else if (parameter.getName() == "EncoderTicksPerRound") {
        static_cast<EncoderTicksPerRound&> (parameter).setParameter(this->encoderTicksPerRound);
      } else if (parameter.getName() == "PositionReferenceToZero") {
        static_cast<PositionReferenceToZero&> (parameter).setParameter(this->positionReferenceToZero);
      }
    } else if (parameter.getType() == MOTOR_CONTOLLER_PARAMETER) {

      YouBotSlaveMailboxMsg message;
      parameter.getYouBotMailboxMsg(message, GET_MESSAGE);

      if (retrieveValueFromMotorContoller(message)) {
        parameter.setYouBotMailboxMsg(message);
      } else {
        throw ExceptionOODL("Unable to get parameter: " + parameter.getName() + " to joint: " + this->jointName);
      }
    }
  // Bouml preserved body end 0005BCF1
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
    YouBotSlaveMsg messageBuffer;
    messageBuffer.stctOutput.controllerMode = POSITION_CONTROL;
    messageBuffer.stctOutput.positionOrSpeed = (int32) (data.angle.value() / (2.0 * M_PI) * gearRatio * encoderTicksPerRound);

    //jointValue / (2 * M_PI) * (joints[jointID - 1].gearRatio * encoderSteps);

    YouBot::getInstance().setMsgBuffer(messageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C1F1
}

///gets the position or angle of one joint with have been calculated for the actual encoder value 
///@param data returns the angle by reference
void YouBotJoint::getData(JointSensedAngle& data) {
  // Bouml preserved body begin 0003DCF1
    YouBotSlaveMsg messageBuffer;
    messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    if (gearRatio == 0) {
      throw ExceptionOODL("A Gear Ratio of zero is not allowed");
    }
    if (encoderTicksPerRound == 0) {
      throw ExceptionOODL("Zero Encoder Ticks per Round are not allowed");
    }

    data.angle = ((double) messageBuffer.stctInput.actualPosition / encoderTicksPerRound) * gearRatio * (2.0 * M_PI) * radian;
  // Bouml preserved body end 0003DCF1
}

///commands a velocity to one joint
///@param data the to command velocity
///@param communicationMode at the moment only non blocking communication is implemented
void YouBotJoint::setData(const JointVelocitySetpoint& data, SyncMode communicationMode) {
  // Bouml preserved body begin 0003C371
    YouBotSlaveMsg messageBuffer;
    messageBuffer.stctOutput.controllerMode = VELOCITY_CONTROL;

    if (gearRatio == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    messageBuffer.stctOutput.positionOrSpeed = (data.angularVelocity.value() / (gearRatio * 2.0 * M_PI)) * 60.0;
    YouBot::getInstance().setMsgBuffer(messageBuffer, this->jointNumber);
  // Bouml preserved body end 0003C371
}

///gets the velocity of one joint with have been calculated for the actual encoder values
///@param data returns the velocity by reference
void YouBotJoint::getData(JointSensedVelocity& data) {
  // Bouml preserved body begin 0003DD71
    YouBotSlaveMsg messageBuffer;
    messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    if (gearRatio == 0) {
      throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
    }
    double motorRPM = messageBuffer.stctInput.actualVelocity;
    //convert RPM of the motor to radian per second of the wheel/joint
    data.angularVelocity = ((motorRPM / 60.0) * gearRatio * 2.0 * M_PI) * radian_per_second;
  // Bouml preserved body end 0003DD71
}

///gets temperature of the motor which have been measured by a thermometer
///@param data returns the actual temperature by reference
void YouBotJoint::getData(JointSensedTemperature& data) {
  // Bouml preserved body begin 0003C271
    YouBotSlaveMsg messageBuffer;
    messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();

    //the formular is taken from the TMCM-174/841: EtherCAT Communication Protocol
    data.temperature = (25.0 + (((messageBuffer.stctInput.driverTemperature - 1.43) / (3.3 * 4095)) / 0.0043)) * boost::units::celsius::degree;

  // Bouml preserved body end 0003C271
}

///gets the motor current of one joint with have been measured by a hal sensor
///@param data returns the actual motor current by reference
void YouBotJoint::getData(JointSensedCurrent& data) {
  // Bouml preserved body begin 0003DDF1
    YouBotSlaveMsg messageBuffer;
    messageBuffer = YouBot::getInstance().getMsgBuffer(this->jointNumber);
    this->parseYouBotErrorFlags();
    //convert mili ampere to ampere
    data.current = messageBuffer.stctInput.actualCurrent / 1000.0 * ampere;
  // Bouml preserved body end 0003DDF1
}

void YouBotJoint::parseYouBotErrorFlags() {
  // Bouml preserved body begin 00044AF1
    YouBotSlaveMsg messageBuffer;
    std::stringstream errorMessageStream;
    errorMessageStream << "Joint " << this->jointNumber << " ";
    std::string errorMessage;
    errorMessage = errorMessageStream.str();


    if (messageBuffer.stctInput.errorFlags & OVER_CURRENT) {
      LOG(error) << errorMessage << "got over current";
      //    throw ExceptionOODL(errorMessage + "got over current");
    }

    if (messageBuffer.stctInput.errorFlags & UNDER_VOLTAGE) {
      LOG(error) << errorMessage << "got under voltage";
      //    throw ExceptionOODL(errorMessage + "got under voltage");
    }

    if (messageBuffer.stctInput.errorFlags & OVER_VOLTAGE) {
      LOG(error) << errorMessage << "got over voltage";
      //   throw ExceptionOODL(errorMessage + "got over voltage");
    }

    if (messageBuffer.stctInput.errorFlags & OVER_TEMPERATURE) {
      LOG(error) << errorMessage << "got over temperature";
      //   throw ExceptionOODL(errorMessage + "got over temperature");
    }

    if (messageBuffer.stctInput.errorFlags & HALTED) {
      //   LOG(error) << errorMessage << "is halted";
      //   throw ExceptionOODL(errorMessage + "is halted");
    }

    if (messageBuffer.stctInput.errorFlags & HALL_SENSOR) {
      LOG(error) << errorMessage << "got hall sensor problem";
      //   throw ExceptionOODL(errorMessage + "got hall sensor problem");
    }

    if (messageBuffer.stctInput.errorFlags & ENCODER) {
      LOG(error) << errorMessage << "got encoder problem";
      //   throw ExceptionOODL(errorMessage + "got encoder problem");
    }

    if (messageBuffer.stctInput.errorFlags & MOTOR_WINDING) {
      LOG(error) << errorMessage << "got motor winding problem";
      //   throw ExceptionOODL(errorMessage + "got motor winding problem");
    }

    if (messageBuffer.stctInput.errorFlags & CYCLE_TIME_VIOLATION) {
      LOG(error) << errorMessage << "the cycle time is violated";
      //   throw ExceptionOODL(errorMessage + "the cycle time is violated");
    }

    if (messageBuffer.stctInput.errorFlags & INIT_SIN_COMM) {
      LOG(error) << errorMessage << "need to initialize the sinus commutation";
      //   throw ExceptionOODL(errorMessage + "need to initialize the sinus commutation");
    }

  // Bouml preserved body end 00044AF1
}

bool YouBotJoint::retrieveValueFromMotorContoller(YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0005BD71

    bool unvalid = true;
    unsigned int retry = 0;

    YouBot::getInstance().setMailboxMsgBuffer(message, this->jointNumber);

    SLEEP_MILLISEC(timeTillNextMailboxUpdate);

    do {
      YouBot::getInstance().getMailboxMsgBuffer(message, this->jointNumber);
   /*   LOG(trace) << "CommandNumber " << (int) message.stctInput.commandNumber
              << " moduleAddress " << (int) message.stctInput.moduleAddress
              << " replyAddress " << (int) message.stctInput.replyAddress
              << " status " << (int) message.stctInput.status
              << " value " << message.stctInput.value;
*/
      if (message.stctOutput.commandNumber == message.stctInput.commandNumber &&
              message.stctInput.status == TMCL_STATUS_OK) {
        unvalid = false;
      } else {
        SLEEP_MILLISEC(timeTillNextMailboxUpdate);
        retry++;
      }
    } while (retry < mailboxMsgRetries && unvalid);

    if (unvalid) {
      return false;
    } else {
      return true;
    }

  // Bouml preserved body end 0005BD71
}

bool YouBotJoint::setValueToMotorContoller(const YouBotSlaveMailboxMsg& mailboxMsg) {
  // Bouml preserved body begin 00054AF1

    YouBotSlaveMailboxMsg mailboxMsgBuffer;
    mailboxMsgBuffer = mailboxMsg;
    bool unvalid = true;
    unsigned int retry = 0;

    YouBot::getInstance().setMailboxMsgBuffer(mailboxMsgBuffer, this->jointNumber);

    SLEEP_MILLISEC(timeTillNextMailboxUpdate);

    do {
      YouBot::getInstance().getMailboxMsgBuffer(mailboxMsgBuffer, this->jointNumber);
  /*    LOG(trace) << "CommandNumber " << (int) mailboxMsgBuffer.stctInput.commandNumber
              << " moduleAddress " << (int) mailboxMsgBuffer.stctInput.moduleAddress
              << " replyAddress " << (int) mailboxMsgBuffer.stctInput.replyAddress
              << " status " << (int) mailboxMsgBuffer.stctInput.status
              << " value " << mailboxMsgBuffer.stctInput.value;
*/
      if (mailboxMsgBuffer.stctOutput.commandNumber == mailboxMsgBuffer.stctInput.commandNumber &&
              mailboxMsgBuffer.stctOutput.value == mailboxMsgBuffer.stctInput.value &&
              mailboxMsgBuffer.stctInput.status == TMCL_STATUS_OK) {
        unvalid = false;
      } else {
        SLEEP_MILLISEC(timeTillNextMailboxUpdate);
        retry++;
      }
    } while (retry < mailboxMsgRetries && unvalid);

    if (unvalid) {
      return false;
    } else {
      return true;
    }

  // Bouml preserved body end 00054AF1
}


} // namespace brics_oodl
