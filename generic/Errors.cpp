
#include "Errors.h"

Errors::Errors() {
  // Bouml preserved body begin 000211F1
  iter = this->occurredErrors.begin();
  // Bouml preserved body end 000211F1
}

Errors::~Errors() {
  // Bouml preserved body begin 00021271
  this->occurredErrors.clear();
  // Bouml preserved body end 00021271
}

void Errors::getNextError(std::string& name, std::string& description) {
  // Bouml preserved body begin 00022AFC
  iter++;
  name = iter->first;
  description = iter->second;
  // Bouml preserved body end 00022AFC
}

void Errors::getAllErrors(map<std::string, std::string>& allErrors) {
  // Bouml preserved body begin 00022B7C
  allErrors = this->occurredErrors;
  // Bouml preserved body end 00022B7C
}

unsigned int Errors::getAmountOfErrors() {
  // Bouml preserved body begin 00021171
  return this->occurredErrors.size();
  // Bouml preserved body end 00021171
}

void Errors::addError(std::string name, std::string description) {
  // Bouml preserved body begin 000212F1
  this->occurredErrors[name] = description;
  std::cout << "ERROR: " << name << " " << description << std::endl;
 // src::logger lg;
//  ::boost::log::sources::severity_logger<4> lg;

  // The logger implicitly adds a source-specific attribute 'Severity'
// of type 'severity_level' on construction
src::severity_logger< severity_level > lg;

BOOST_LOG_SEV(lg, normal) << "A regular message";
BOOST_LOG_SEV(lg, warning) << "Something bad is going on but I can handle it";
BOOST_LOG_SEV(lg, critical) << "Everything crumbles, shoot me now!";

//    BOOST_LOG(lg) << name;
  // Bouml preserved body end 000212F1
}

void Errors::deleteAllErrors() {
  // Bouml preserved body begin 00021371
  this->occurredErrors.clear();
  // Bouml preserved body end 00021371
}

