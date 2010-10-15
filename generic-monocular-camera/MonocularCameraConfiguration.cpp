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
  colExpConfiguration = new ColorExposureConfiguration(deviceConfig, handleConfig);
  devConfiguration = new CameraDeviceConfiguration(deviceConfig, handleConfig);
  propertyConfig = new unicap_property_t;
}

MonocularCameraConfiguration::MonocularCameraConfiguration(MonocularCameraConfiguration &cameraConfig) {
  std::cout << "Creating Copy of MonocularCameraConfiguration" << std::endl;
}

MonocularCameraConfiguration& MonocularCameraConfiguration::operator=(MonocularCameraConfiguration &cameraConfig) {
  if (&cameraConfig != this) {
    std::cout << "Assigning MonocularCameraConfiguration" << std::endl;
    this->deviceConfig = cameraConfig.deviceConfig;
    this->handleConfig = cameraConfig.handleConfig;
    this->returnStatus = cameraConfig.returnStatus;
    this->deviceID = cameraConfig.deviceID;
    this->deviceNodeID = cameraConfig.deviceNodeID;
    this->devicePluginType = cameraConfig.devicePluginType;
    this->colExpConfiguration = cameraConfig.colExpConfiguration;
    this->devConfiguration = cameraConfig.devConfiguration;
    this->propertyConfig = cameraConfig.propertyConfig;
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


CameraDeviceConfiguration MonocularCameraConfiguration::getCameraDeviceConfiguration()
{


    return *(this->devConfiguration);
}

ColorExposureConfiguration MonocularCameraConfiguration::getColorExposureConfiguration()
{


    return *(this->colExpConfiguration);
}








CameraDeviceConfiguration::CameraDeviceConfiguration() {
  std::cout << "Creating CameraDeviceConfiguration without arguments" << std::endl;
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
  deviceCameraDevConf = NULL;
  handleCameraDevConf = NULL;
}


CameraDeviceConfiguration::CameraDeviceConfiguration(unicap_device_t *device, unicap_handle_t *handle) {
  std::cout << "Creating CameraDeviceConfiguration with arguments" << std::endl;
  deviceCameraDevConf = device;
  handleCameraDevConf = handle;
}

CameraDeviceConfiguration::~CameraDeviceConfiguration() {

  std::cout << "Destroying CameraDeviceConfiguration with arguments" << std::endl;

}

bool CameraDeviceConfiguration::getVideoFrameRate(double &rate) {

  std::cout << "Inside CameraDeviceConfiguration getVideoFrameRate" << std::endl;
  

}

bool CameraDeviceConfiguration::getVideoGammaValue(double &gamma) {

  std::cout << "Inside CameraDeviceConfiguration getVideoGammaValue" << std::endl;

}

bool CameraDeviceConfiguration::getVideoSharpnessValue(double &sharpness) {

  std::cout << "Inside CameraDeviceConfiguration getVideoSharpnessValue" << std::endl;

}

bool CameraDeviceConfiguration::getLensFocus(double &focus) {

  std::cout << "Inside CameraDeviceConfiguration getLensFocus" << std::endl;
}

bool CameraDeviceConfiguration::getLensZoom(double &zoom) {

  std::cout << "Inside CameraDeviceConfiguration getLensZoom" << std::endl;

}

bool CameraDeviceConfiguration::getLensIris(double &iris) {

  std::cout << "Inside CameraDeviceConfiguration getLensIris" << std::endl;

}

bool CameraDeviceConfiguration::setVideoFrameRate(double &rate) {

  std::cout << "Inside CameraDeviceConfiguration setVideoFrameRate" << std::endl;

}

bool CameraDeviceConfiguration::setVideoGammaValue(double &gamma) {

  std::cout << "Inside CameraDeviceConfiguration setVideoGammaValue" << std::endl;
}

bool CameraDeviceConfiguration::setVideoSharpnessValue(double &sharpness) {

  std::cout << "Inside CameraDeviceConfiguration setVideoSharpnessValue" << std::endl;
}

bool CameraDeviceConfiguration::setLensFocus(double &focus) {

  std::cout << "Inside CameraDeviceConfiguration setLensFocus" << std::endl;
}

bool CameraDeviceConfiguration::setLensZoom(double &zoom) {
  std::cout << "Inside CameraDeviceConfiguration setLensZoom" << std::endl;

}

bool CameraDeviceConfiguration::setLensIris(double &iris) {

  std::cout << "Inside CameraDeviceConfiguration setLensIris" << std::endl;
}

bool CameraDeviceConfiguration::getListOfDeviceProperties() {

  std::cout << "Inside CameraDeviceConfiguration getListOfDeviceProperties" << std::endl;
  unicap_property_t propertyList[50];
  int propertyCounter;
  int p = -1;  
  
  for( propertyCounter = 0; propertyCounter < 50 ; propertyCounter++ )
  {
      returnStatus = unicap_enumerate_properties( *handleCameraDevConf, NULL, &propertyList[propertyCounter], propertyCounter);
      if( SUCCESS(returnStatus) )
      {
          if( propertyList[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
          {
              std::cout << propertyList[propertyCounter].identifier << std::endl;
              returnStatus = unicap_get_property( *handleCameraDevConf, &propertyList[p] ); // (3)
              if( SUCCESS(returnStatus) )
              {
                  std::cout << propertyList[p].value<< propertyList[p].range.min <<propertyList[p].range.max << std::endl;
              }
              propertyCounter++;
          }
      }
      else
      {
          continue;
      }
  }
  
  return true;
}




ColorExposureConfiguration::ColorExposureConfiguration() {
  std::cout << "Creating ColorExposureConfiguration without arguments" << std::endl;
  deviceColorExposureDev = NULL;
  handleColorExposureDev = NULL;
}


ColorExposureConfiguration::ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle) {
  std::cout << "Creating ColorExposureConfiguration with arguments" << std::endl;
  deviceColorExposureDev = device;
  handleColorExposureDev = handle;
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


