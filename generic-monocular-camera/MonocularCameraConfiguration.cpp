#include "MonocularCameraConfiguration.hpp"
#include <string>
#include <iostream>



MonocularCameraConfiguration::MonocularCameraConfiguration(): returnStatus(STATUS_FAILURE), deviceID (""), 
                                                              deviceNodeID (""), devicePluginType("") 
{
     std::cout << "Creating MonocularCameraConfiguration without arguments" << std::endl;
     colExpConfiguration = new ColorExposureConfiguration;
     devConfiguration = new CameraDeviceConfiguration;
     propertyConfig = new unicap_property_t;
}

MonocularCameraConfiguration::MonocularCameraConfiguration(unicap_device_t *device, unicap_handle_t *handle): returnStatus(STATUS_FAILURE), 
                                                                                                              deviceID (""), deviceNodeID (""), 
                                                                                                              devicePluginType("") , 
                                                                                                              deviceConfig (device), 
                                                                                                              handleConfig(handle)
{
     std::cout << "Creating MonocularCameraConfiguration with arguments" << std::endl;
     colExpConfiguration = new ColorExposureConfiguration(deviceConfig, handleConfig);
     devConfiguration = new CameraDeviceConfiguration(deviceConfig, handleConfig);
     propertyConfig = new unicap_property_t;
}

MonocularCameraConfiguration::MonocularCameraConfiguration(MonocularCameraConfiguration &cameraConfig) 
{
     std::cout << "Creating Copy of MonocularCameraConfiguration" << std::endl;
}

MonocularCameraConfiguration& MonocularCameraConfiguration::operator=(MonocularCameraConfiguration &cameraConfig) 
{
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

bool MonocularCameraConfiguration::getDeviceName(std::string &deviceId) 
{
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

bool MonocularCameraConfiguration::getDeviceNodeID(std::string &deviceNodeId) 
{
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

bool MonocularCameraConfiguration::getDevicePluginType(std::string &pluginName) 
{
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


CameraDeviceConfiguration* MonocularCameraConfiguration::getCameraDeviceConfiguration()
{


     return (this->devConfiguration);
}

ColorExposureConfiguration* MonocularCameraConfiguration::getColorExposureConfiguration()
{


     return (this->colExpConfiguration);
}


bool MonocularCameraConfiguration::setCameraDeviceConfiguration(CameraDeviceConfiguration &cameradevconf)
{

     return true;
}


bool MonocularCameraConfiguration::setColorExposureConfiguration(ColorExposureConfiguration &colorexpconf)
{

     return true;
}


