
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

YouBotJointConfiguration::YouBotJointConfiguration(const YouBotJointConfiguration & source) {
  // Bouml preserved body begin 0004B971
    this->gearRatio = source.gearRatio;
    this->jointName = source.jointName;
    this->validRanges = source.validRanges;
    this->encoderTicksPerRound = source.encoderTicksPerRound;
    this->setPositionReferenceToZero = source.setPositionReferenceToZero;
  // Bouml preserved body end 0004B971
}

YouBotJointConfiguration & YouBotJointConfiguration::operator=(const YouBotJointConfiguration & source) {
  // Bouml preserved body begin 0004B9F1
    this->gearRatio = source.gearRatio;
    this->jointName = source.jointName;
    this->validRanges = source.validRanges;
    this->encoderTicksPerRound = source.encoderTicksPerRound;
    this->setPositionReferenceToZero = source.setPositionReferenceToZero;
  // Bouml preserved body end 0004B9F1
}

void YouBotJointConfiguration::setGearRatio(double ratio) {
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

void YouBotJointConfiguration::setEncoderTicksPerRound(unsigned int ticksPerRound) {
  // Bouml preserved body begin 0004BDF1
  this->encoderTicksPerRound = ticksPerRound;
  // Bouml preserved body end 0004BDF1
}


} // namespace brics_oodl
