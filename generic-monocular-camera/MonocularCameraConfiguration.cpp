#include "MonocularCameraConfiguration.h"
#include <string>
#include <iostream>



MonocularCameraConfiguration::MonocularCameraConfiguration()
{
   deviceConfig = new unicap_property_t;
   device = new unicap_device_t;
   returnStatus = STATUS_FAILURE;
   deviceID = "";
   deviceNodeID = "";
   devicePluginType = "";
 
}


bool MonocularCameraConfiguration::getDeviceName(std::string &deviceId)
{
  if(SUCCESS(returnStatus))
  {
    deviceID = device->identifier;
    deviceId = deviceID;
    return true;
  }
  else
  {
    returnStatus = unicap_enumerate_devices(NULL, device,0);
    if(SUCCESS(returnStatus))
    {
      deviceID = device->identifier;
      deviceId = deviceID; 
      return true;
    }
    
    else
    {
      std::cout << "Can not get device name"<<std::endl;
      return false;
    }

  }

}


bool MonocularCameraConfiguration::getDeviceNodeID(std::string &deviceNodeId)
{
  if(SUCCESS(returnStatus))
  {
    deviceNodeID = device->device;
    deviceNodeId = deviceNodeID; 
    return true;
  }

  else
  {
    returnStatus = unicap_enumerate_devices(NULL, device,0); 
    if(SUCCESS(returnStatus))
    {
      deviceNodeID = device->device;
      deviceNodeId = deviceNodeID; 
      return true;
    }
    else
    {
      std::cout << "Can not get device node ID"<<std::endl;
      return false;
    }
  }

}


bool MonocularCameraConfiguration::getDevicePluginType(std::string &pluginName)
{

  if(SUCCESS(returnStatus))
  {
    devicePluginType = device->cpi_layer;
    pluginName = devicePluginType; 
    return true;
  }
  else
  {
    returnStatus = unicap_enumerate_devices(NULL, device,0);
    if(SUCCESS(returnStatus))
    {
      devicePluginType = device->cpi_layer;
      pluginName = devicePluginType; 
      return true;
    }
    
    else
    {
      std::cout << "Can not get device node ID"<<std::endl;
      return false;
    }
  }

}


bool MonocularCameraConfiguration::getDeviceFullInfoVector()
{
  returnStatus = unicap_enumerate_devices(NULL, device, 0);

}

MonocularCameraConfiguration::~MonocularCameraConfiguration()
{
  delete deviceConfig;
  delete device;
}
