#include "MonocularCameraConfiguration.h"
#include <string>
#include <iostream>

MonocularCameraConfiguration::MonocularCameraConfiguration() {
  std::cout << "Creating MonocularCameraConfiguration without arguments" << std::endl;
  colExpConfiguration = new ColorExposureConfiguration;
  devConfiguration = new CameraDeviceConfiguration;
  propertyConfig = new unicap_property_t;
}

MonocularCameraConfiguration::MonocularCameraConfiguration(unicap_device_t *device, unicap_handle_t *handle) {
  std::cout << "Creating MonocularCameraConfiguration with arguments" << std::endl;

  deviceConfig = device;
  handleConfig = handle;
  returnStatus = STATUS_FAILURE;
  deviceID = "";
  deviceNodeID = "";
  devicePluginType = "";
  colExpConfiguration = new ColorExposureConfiguration;
  devConfiguration = new CameraDeviceConfiguration;
  propertyConfig = new unicap_property_t;
}

MonocularCameraConfiguration::MonocularCameraConfiguration(MonocularCameraConfiguration &cameraConfig) {
  std::cout << "Creating Copy of MonocularCameraConfiguration" << std::endl;
}

MonocularCameraConfiguration& MonocularCameraConfiguration::operator=(MonocularCameraConfiguration &cameraConfig) {
  if (&cameraConfig != this) {
    std::cout << "Assigning MonocularCameraConfiguration" << std::endl;
    cameraConfig.deviceConfig = this->deviceConfig;
    cameraConfig.handleConfig = this->handleConfig;
    cameraConfig.returnStatus = this->returnStatus;
    cameraConfig.deviceID = this->deviceID;
    cameraConfig.deviceNodeID = this->deviceNodeID;
    cameraConfig.devicePluginType = this->devicePluginType;
    cameraConfig.colExpConfiguration = this->colExpConfiguration;
    cameraConfig.devConfiguration = this->devConfiguration;
    cameraConfig.propertyConfig = this->propertyConfig;
  }

  return *this;
}

bool MonocularCameraConfiguration::getDeviceName(std::string &deviceId) {
  std::cout << "In MonocularCameraConfiguration calling getDeviceName" << std::endl;

  if (SUCCESS(returnStatus)) {
    deviceID = deviceConfig->identifier;
    deviceId = deviceID;
    return true;
  } else {
    returnStatus = unicap_enumerate_devices(NULL, deviceConfig, 0);
    if (SUCCESS(returnStatus)) {
      deviceID = deviceConfig->identifier;
      deviceId = deviceID;
      return true;
    }
    else {
      std::cout << "Can not get device name" << std::endl;
      return false;
    }

  }

}

bool MonocularCameraConfiguration::getDeviceNodeID(std::string &deviceNodeId) {
  std::cout << "In MonocularCameraConfiguration calling getDeviceNodeID" << std::endl;

  if (SUCCESS(returnStatus)) {
    deviceNodeID = deviceConfig->device;
    deviceNodeId = deviceNodeID;
    return true;
  }
  else {
    returnStatus = unicap_enumerate_devices(NULL, deviceConfig, 0);
    if (SUCCESS(returnStatus)) {
      deviceNodeID = deviceConfig->device;
      deviceNodeId = deviceNodeID;
      return true;
    } else {
      std::cout << "Can not get device node ID" << std::endl;
      return false;
    }
  }

}

bool MonocularCameraConfiguration::getDevicePluginType(std::string &pluginName) {
  std::cout << "In MonocularCameraConfiguration calling getDevicePluginType" << std::endl;

  if (SUCCESS(returnStatus)) {
    devicePluginType = deviceConfig->cpi_layer;
    pluginName = devicePluginType;
    return true;
  } else {
    returnStatus = unicap_enumerate_devices(NULL, deviceConfig, 0);
    if (SUCCESS(returnStatus)) {
      devicePluginType = deviceConfig->cpi_layer;
      pluginName = devicePluginType;
      return true;
    }
    else {
      std::cout << "Can not get device node ID" << std::endl;
      return false;
    }
  }

}

bool MonocularCameraConfiguration::getDeviceFullInfoVector() {
  std::cout << "In MonocularCameraConfiguration calling getDeviceFullInfoVector" << std::endl;

  returnStatus = unicap_enumerate_devices(NULL, deviceConfig, 0);

}

MonocularCameraConfiguration::~MonocularCameraConfiguration() {
  std::cout << "Destroying MonocularCameraConfiguration" << std::endl;

  delete colExpConfiguration;
  delete devConfiguration;
  delete propertyConfig;

}

CameraDeviceConfiguration::CameraDeviceConfiguration() {
  std::cout << "Creating CameraDeviceConfiguration with arguments" << std::endl;
  videoFrameRate.min = 0.0;
  videoFrameRate.max = 0.0;
  videoGammaValue.min = 0.0;
  videoGammaValue.max = 0.0;
  videoSharpnessValue.min = 0.0;
  videoSharpnessValue.max = 0.0;
  lensFocus.min = 0.0;
  lensFocus.max = 0.0;
  lensZoom.min = 0.0;
  lensZoom.max = 0.0;
  lensIris.min = 0.0;
  lensIris.max = 0.0;
  returnStatus = STATUS_FAILURE;
}

CameraDeviceConfiguration::~CameraDeviceConfiguration() {
  std::cout << "Destroying CameraDeviceConfiguration with arguments" << std::endl;
}

bool CameraDeviceConfiguration::getVideoFrameRate(double &rate) {



}

bool CameraDeviceConfiguration::getVideoGammaValue(double &gamma) {

}

bool CameraDeviceConfiguration::getVideoSharpnessValue(double &sharpness) {

}

bool CameraDeviceConfiguration::getLensFocus(double &focus) {


}

bool CameraDeviceConfiguration::getLensZoom(double &zoom) {


}

bool CameraDeviceConfiguration::getLensIris(double &iris) {


}

bool CameraDeviceConfiguration::setVideoFrameRate(double &rate) {


}

bool CameraDeviceConfiguration::setVideoGammaValue(double &gamma) {


}

bool CameraDeviceConfiguration::setVideoSharpnessValue(double &sharpness) {


}

bool CameraDeviceConfiguration::setLensFocus(double &focus) {


}

bool CameraDeviceConfiguration::setLensZoom(double &zoom) {


}

bool CameraDeviceConfiguration::setLensIris(double &iris) {


}

ColorExposureConfiguration::ColorExposureConfiguration() {
  std::cout << "Creating ColorExposureConfiguration with arguments" << std::endl;
}

ColorExposureConfiguration::~ColorExposureConfiguration() {
  std::cout << "Destroying ColorExposureConfiguration with arguments" << std::endl;

}

bool ColorExposureConfiguration::getHueValue(double &hue) {

}

bool ColorExposureConfiguration::getChromaValue(double &chroma) {

}

bool ColorExposureConfiguration::getSaturationValue(double &saturation) {

}

bool ColorExposureConfiguration::getColorTemperatureValue(double &temp) {

}

bool ColorExposureConfiguration::getWhiteBalanceUValue(double &uValue) {

}

bool ColorExposureConfiguration::getWhiteBalanceVValue(double &vValue) {

}

bool ColorExposureConfiguration::getBrightnessValue(double &brightness) {

}

bool ColorExposureConfiguration::getGainControlValue(double &gain) {

}

bool ColorExposureConfiguration::getShutterTime(double &sTime) {

}

bool ColorExposureConfiguration::getExposureTime(double &eTime) {

}

bool ColorExposureConfiguration::setHueValue(double &hue) {

}

bool ColorExposureConfiguration::setChromaValue(double &chroma) {

}

bool ColorExposureConfiguration::setSaturationValue(double &saturation) {

}

bool ColorExposureConfiguration::setColorTemperatureValue(double &temp) {

}

bool ColorExposureConfiguration::setWhiteBalanceUValue(double &uValue) {

}

bool ColorExposureConfiguration::setWhiteBalanceVValue(double &vValue) {

}

bool ColorExposureConfiguration::setBrightnessValue(double &brightness) {

}

bool ColorExposureConfiguration::setGainControlValue(double &gain) {

}

bool ColorExposureConfiguration::setShutterTime(double &sTime) {

}

bool ColorExposureConfiguration::setExposureTime(double &eTime) {

}


