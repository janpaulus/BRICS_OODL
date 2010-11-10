#include "generic/ExceptionOODL.hpp"

ExceptionOODL::ExceptionOODL(const string& message) {
  msg  = message;
  LOG(oodl_exception) << message;
}

ExceptionOODL::~ExceptionOODL() throw() {

}

// Returns a C-style character string describing the general cause of the current error
const char* ExceptionOODL::what() const throw(){
  return msg.c_str();
}
