
#include "generic-tof-camera/ToFCameraConfiguration.hpp"
namespace brics_oodl {

ToFCameraConfiguration::ToFCameraConfiguration(){
  // Bouml preserved body begin 00031BF1
  // Bouml preserved body end 00031BF1
}

ToFCameraConfiguration::~ToFCameraConfiguration(){
  // Bouml preserved body begin 00031C71
  // Bouml preserved body end 00031C71
}

ToFCameraConfiguration::ToFCameraConfiguration(const ToFCameraConfiguration & source) {
  // Bouml preserved body begin 00031CF1
  *this = source;
  // Bouml preserved body end 00031CF1
}

ToFCameraConfiguration & ToFCameraConfiguration::operator=(const ToFCameraConfiguration & source) {
  // Bouml preserved body begin 00031D71


  this->devicePath = source.devicePath;
  this->firmware = source.firmware;

  this->model = source.model;

  this->product = source.product;
  this->protocol = source.protocol;

  this->serialNumber = source.serialNumber;
  this->vendor = source.vendor;

  return *this;

  // Bouml preserved body end 00031D71
}


} // namespace brics_oodl
