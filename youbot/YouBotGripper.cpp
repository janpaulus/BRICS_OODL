
#include "youbot/YouBotGripper.hpp"
#include "youbot/EthercatMaster.hpp"
namespace brics_oodl {

YouBotGripper::YouBotGripper(const unsigned int jointNo) {
  // Bouml preserved body begin 0005EFF1
    this->jointNumber = jointNo;
    this->mailboxMsgRetries = 30;
    this->timeTillNextMailboxUpdate = EthercatMaster::getInstance().timeTillNextEthercatUpdate * 2;
    this->maxTravelDistance = 0.023 * meter;
    this->maxEncoderValue = 67000;
    this->barSpacingOffset = 0 * meter;
    this->lastGripperPosition = 0 * meter;
  // Bouml preserved body end 0005EFF1
}

YouBotGripper::~YouBotGripper() {
  // Bouml preserved body begin 0005F071
  // Bouml preserved body end 0005F071
}

void YouBotGripper::getConfigurationParameter(GripperParameter& parameter) {
  // Bouml preserved body begin 0005FBF1
  throw ExceptionOODL("Please use YouBotGripperParameter");
  // Bouml preserved body end 0005FBF1
}

void YouBotGripper::setConfigurationParameter(const GripperParameter& parameter) {
  // Bouml preserved body begin 0005FA71
  throw ExceptionOODL("Please use YouBotGripperParameter");
  // Bouml preserved body end 0005FA71
}

void YouBotGripper::getConfigurationParameter(YouBotGripperParameter& parameter) {
  // Bouml preserved body begin 000482F1
  // Bouml preserved body end 000482F1
}

void YouBotGripper::setConfigurationParameter(const YouBotGripperParameter& parameter) {
  // Bouml preserved body begin 000617F1
   
  // Bouml preserved body end 000617F1
}

void YouBotGripper::setConfigurationParameter(const CalibrateGripper& parameter) {
  // Bouml preserved body begin 00048271
    
      if (parameter.value) {
        YouBotSlaveMailboxMsg message;

        LOG(trace) << "Calibrate gripper";
        message.stctOutput.moduleAddress = GRIPPER;
        message.stctOutput.commandNumber = MVP;
        message.stctOutput.typeNumber = 1; //move gripper
        message.stctOutput.motorNumber = 0; //always zero
        message.stctOutput.value = this->maxEncoderValue;

        setValueToMotorContoller(message);
        
        SLEEP_MILLISEC(4000); //wait until the gripper ist closed

        //set encoder reference to zero
        YouBotSlaveMsg messageBuffer;
        messageBuffer.stctOutput.controllerMode = MOTOR_STOP;
        messageBuffer.stctOutput.positionOrSpeed = 0;
        EthercatMaster::getInstance().setMsgBuffer(messageBuffer, this->jointNumber);
        this->lastGripperPosition = 0 * meter;

        //stop Gripper motor
        SLEEP_MILLISEC(timeTillNextMailboxUpdate*2);
        message.stctOutput.value = 0;
        setValueToMotorContoller(message);
      }
    
  // Bouml preserved body end 00048271
}

void YouBotGripper::setConfigurationParameter(const BarSpacingOffset& parameter) {
  // Bouml preserved body begin 00061871
      this->barSpacingOffset = parameter.value;
  // Bouml preserved body end 00061871
}

void YouBotGripper::setConfigurationParameter(const MaxTravelDistance& parameter) {
  // Bouml preserved body begin 00061DF1
  this->maxTravelDistance = parameter.value;
  // Bouml preserved body end 00061DF1
}

void YouBotGripper::setConfigurationParameter(const MaxEncoderValue& parameter) {
  // Bouml preserved body begin 00061E71
  this->maxEncoderValue = parameter.value;
  // Bouml preserved body end 00061E71
}

void YouBotGripper::getData(const GripperData& data) {
  // Bouml preserved body begin 0005FB71
    LOG(info) << "Nothing to do";
  // Bouml preserved body end 0005FB71
}

void YouBotGripper::setData(const OneDOFGripperData& data) {
  // Bouml preserved body begin 00048371
    LOG(info) << "Nothing to do";
  // Bouml preserved body end 00048371
}

void YouBotGripper::setData(const GripperData& data) {
  // Bouml preserved body begin 0005FAF1
    LOG(info) << "Nothing to do";
  // Bouml preserved body end 0005FAF1
}

void YouBotGripper::getData(OneDOFGripperData& data) {
  // Bouml preserved body begin 000483F1
    LOG(info) << "Nothing to do";
  // Bouml preserved body end 000483F1
}

void YouBotGripper::setData(const GripperBarSpacingSetPoint& barSpacing) {
  // Bouml preserved body begin 0005F8F1

  if(barSpacing.barSpacing > (maxTravelDistance + barSpacingOffset) || barSpacing.barSpacing < 0 * meter){
    std::stringstream errorMessageStream;
    errorMessageStream << "The bar spacing is not allowd to be less than 0 m or higher than " << (maxTravelDistance + barSpacingOffset);
    throw ExceptionOODL(errorMessageStream.str());
  }
    YouBotSlaveMailboxMsg message;
    message.stctOutput.moduleAddress = GRIPPER;
    message.stctOutput.commandNumber = MVP;
    message.stctOutput.typeNumber = 1; //move gripper
    message.stctOutput.motorNumber = 0; //always zero
    message.stctOutput.value = (int)(((this->lastGripperPosition - barSpacing.barSpacing)+barSpacingOffset)/maxTravelDistance * maxEncoderValue);

    this->lastGripperPosition = barSpacing.barSpacing;
    setValueToMotorContoller(message);

  // Bouml preserved body end 0005F8F1
}

void YouBotGripper::getData(GripperBarSpacingSetPoint& barSpacing) {
  // Bouml preserved body begin 0005F971
   LOG(info) << "At the moment it is not possible to get the sensed position of the gripper";
  // Bouml preserved body end 0005F971
}

bool YouBotGripper::setValueToMotorContoller(const YouBotSlaveMailboxMsg& mailboxMsg) {
  // Bouml preserved body begin 0005EF71

    YouBotSlaveMailboxMsg mailboxMsgBuffer;
    mailboxMsgBuffer = mailboxMsg;
    bool unvalid = true;
    unsigned int retry = 0;

    EthercatMaster::getInstance().setMailboxMsgBuffer(mailboxMsgBuffer, this->jointNumber);

    SLEEP_MILLISEC(timeTillNextMailboxUpdate);

    do {
      EthercatMaster::getInstance().getMailboxMsgBuffer(mailboxMsgBuffer, this->jointNumber);
      /*    LOG(trace) << "CommandNumber " << (int) mailboxMsgBuffer.stctInput.commandNumber
                  << " moduleAddress " << (int) mailboxMsgBuffer.stctInput.moduleAddress
                  << " replyAddress " << (int) mailboxMsgBuffer.stctInput.replyAddress
                  << " status " << (int) mailboxMsgBuffer.stctInput.status
                  << " value " << mailboxMsgBuffer.stctInput.value;
       */
      if (mailboxMsgBuffer.stctOutput.commandNumber == mailboxMsgBuffer.stctInput.commandNumber &&
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

  // Bouml preserved body end 0005EF71
}

bool YouBotGripper::retrieveValueFromMotorContoller(YouBotSlaveMailboxMsg& message) {
  // Bouml preserved body begin 0005EEF1

    bool unvalid = true;
    unsigned int retry = 0;

    EthercatMaster::getInstance().setMailboxMsgBuffer(message, this->jointNumber);

    SLEEP_MILLISEC(timeTillNextMailboxUpdate);

    do {
      EthercatMaster::getInstance().getMailboxMsgBuffer(message, this->jointNumber);
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

  // Bouml preserved body end 0005EEF1
}


} // namespace brics_oodl
