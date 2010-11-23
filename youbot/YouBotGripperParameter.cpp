
#include "youbot/YouBotGripperParameter.hpp"
namespace brics_oodl {

YouBotGripperParameter::YouBotGripperParameter() {
  // Bouml preserved body begin 0005F0F1
  // Bouml preserved body end 0005F0F1
}

YouBotGripperParameter::~YouBotGripperParameter() {
  // Bouml preserved body begin 0005F171
  // Bouml preserved body end 0005F171
}

CalibrateGripper::CalibrateGripper() {
  // Bouml preserved body begin 0005F3F1
    this->name = "CalibrateGripper";
  // Bouml preserved body end 0005F3F1
}

CalibrateGripper::~CalibrateGripper() {
  // Bouml preserved body begin 0005F471
  // Bouml preserved body end 0005F471
}

void CalibrateGripper::getParameter(bool& parameter) const {
  // Bouml preserved body begin 0005F4F1
    parameter = this->value;
  // Bouml preserved body end 0005F4F1
}

void CalibrateGripper::setParameter(const bool parameter) {
  // Bouml preserved body begin 0005F571
    this->value = parameter;
  // Bouml preserved body end 0005F571
}

BarSpacingOffset::BarSpacingOffset() {
  // Bouml preserved body begin 0005FC71
    this->name = "BarSpacingOffset";
  // Bouml preserved body end 0005FC71
}

BarSpacingOffset::~BarSpacingOffset() {
  // Bouml preserved body begin 0005FCF1
  // Bouml preserved body end 0005FCF1
}

void BarSpacingOffset::getParameter(quantity<si::length>& parameter) const {
  // Bouml preserved body begin 0005FD71
    parameter = this->value;
  // Bouml preserved body end 0005FD71
}

void BarSpacingOffset::setParameter(const quantity<si::length>& parameter) {
  // Bouml preserved body begin 0005FDF1
  if(parameter > 1 *meter || parameter < 0 *meter){
    throw ExceptionOODL("Wrong BarSpacingOffset parameter");
  }
    this->value = parameter;
  // Bouml preserved body end 0005FDF1
}


} // namespace brics_oodl
