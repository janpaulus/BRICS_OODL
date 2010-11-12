
#include "youbot/YouBotJointConfiguration.hpp"
namespace brics_oodl {

YouBotJointConfiguration::YouBotJointConfiguration() {
  // Bouml preserved body begin 0004B871
    this->GearRatio = 1;
    this->EncoderTicksPerRound = 0;
  // Bouml preserved body end 0004B871
}

YouBotJointConfiguration::~YouBotJointConfiguration() {
  // Bouml preserved body begin 0004B8F1
  // Bouml preserved body end 0004B8F1
}

YouBotJointConfiguration::YouBotJointConfiguration(const YouBotJointConfiguration & source) {
  // Bouml preserved body begin 0004B971
    this->GearRatio = source.GearRatio;
    this->JointName = source.JointName;
    this->ValidRanges = source.ValidRanges;
    this->EncoderTicksPerRound = source.EncoderTicksPerRound;
    this->SetPositionReferenceToZero = source.SetPositionReferenceToZero;
  // Bouml preserved body end 0004B971
}

YouBotJointConfiguration & YouBotJointConfiguration::operator=(const YouBotJointConfiguration & source) {
  // Bouml preserved body begin 0004B9F1
    this->GearRatio = source.GearRatio;
    this->JointName = source.JointName;
    this->ValidRanges = source.ValidRanges;
    this->EncoderTicksPerRound = source.EncoderTicksPerRound;
    this->SetPositionReferenceToZero = source.SetPositionReferenceToZero;
  // Bouml preserved body end 0004B9F1
}

void YouBotJointConfiguration::setGearRatio(double ratio) {
  // Bouml preserved body begin 0004BC71
  if(ratio == 0){
    throw ExceptionOODL("A Gear Ratio of 0 is not allowed");
  }else{
    this->GearRatio = ratio;
  }
  // Bouml preserved body end 0004BC71
}

double YouBotJointConfiguration::getGearRatio() const {
  // Bouml preserved body begin 0004BCF1
  return this->GearRatio;
  // Bouml preserved body end 0004BCF1
}

unsigned int YouBotJointConfiguration::getEncoderTicksPerRound() const {
  // Bouml preserved body begin 0004BD71
  return this->EncoderTicksPerRound;
  // Bouml preserved body end 0004BD71
}

void YouBotJointConfiguration::setEncoderTicksPerRound(unsigned int ticksPerRound) {
  // Bouml preserved body begin 0004BDF1
  this->EncoderTicksPerRound = ticksPerRound;
  // Bouml preserved body end 0004BDF1
}


} // namespace brics_oodl
