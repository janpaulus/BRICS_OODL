#include "MonocularCameraConfiguration.h"
#include <string>
#include <iostream>




DeviceConfiguration:: DeviceConfiguration()
{
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


DeviceConfiguration::~DeviceConfiguration()
{

}
 

bool DeviceConfiguration::getVideoFrameRate(double &rate)
{
 
  

}


bool DeviceConfiguration::getVideoGammaValue(double &gamma)
{

}

bool DeviceConfiguration::getVideoSharpnessValue(double &sharpness)
{

}

bool DeviceConfiguration::getLensFocus(double &focus)
{


}

bool DeviceConfiguration::getLensZoom(double &zoom)
{


}

bool DeviceConfiguration::getLensIris(double &iris)
{


}


bool DeviceConfiguration::setVideoFrameRate(double &rate)
{


}


bool DeviceConfiguration::setVideoGammaValue(double &gamma)
{


}

bool DeviceConfiguration::setVideoSharpnessValue(double &sharpness)
{


}


bool DeviceConfiguration::setLensFocus(double &focus)
{


}


bool DeviceConfiguration::setLensZoom(double &zoom)
{


}

bool DeviceConfiguration::setLensIris(double &iris)
{


}



ColorExposureConfiguration::ColorExposureConfiguration()
{

}

ColorExposureConfiguration::~ColorExposureConfiguration()
{


}
 
bool ColorExposureConfiguration::getHueValue(double &hue)
{

}

bool ColorExposureConfiguration::getChromaValue(double &chroma)
{

}


bool ColorExposureConfiguration::getSaturationValue(double &saturation)
{

}

bool ColorExposureConfiguration::getColorTemperatureValue(double &temp)
{

}

bool ColorExposureConfiguration::getWhiteBalanceUValue(double &uValue)
{

}

bool ColorExposureConfiguration::getWhiteBalanceVValue(double &vValue)
{

}

bool ColorExposureConfiguration::getBrightnessValue(double &brightness)
{

}

bool ColorExposureConfiguration::getGainControlValue(double &gain)
{

}

bool ColorExposureConfiguration::getShutterTime(double &sTime)
{

}

bool ColorExposureConfiguration::getExposureTime(double &eTime)
{

}

bool ColorExposureConfiguration::setHueValue(double &hue)
{

}

bool ColorExposureConfiguration::setChromaValue(double &chroma)
{

}

bool ColorExposureConfiguration::setSaturationValue(double &saturation)
{

}

bool ColorExposureConfiguration::setColorTemperatureValue(double &temp)
{

}

bool ColorExposureConfiguration::setWhiteBalanceUValue(double &uValue)
{

}

bool ColorExposureConfiguration::setWhiteBalanceVValue(double &vValue)
{

}

bool ColorExposureConfiguration::setBrightnessValue(double &brightness)
{

}

bool ColorExposureConfiguration::setGainControlValue(double &gain)
{

}

bool ColorExposureConfiguration::setShutterTime(double &sTime)
{

}

bool ColorExposureConfiguration::setExposureTime(double &eTime)
{

}



MonocularCameraConfiguration::MonocularCameraConfiguration()
{
  
 
}


MonocularCameraConfiguration::MonocularCameraConfiguration(unicap_device_t *device, unicap_handle_t *handle)
{
  deviceConfig = device;
  handleConfig = handle;
  returnStatus = STATUS_FAILURE;
  deviceID = "";
  deviceNodeID = "";
  devicePluginType = "";
  colExpConfiguration = new ColorExposureConfiguration;
  devConfiguration = new DeviceConfiguration;
  propertyConfig = new unicap_property_t;
}

bool MonocularCameraConfiguration::getDeviceName(std::string &deviceId)
{
  if(SUCCESS(returnStatus))
  {
    deviceID = deviceConfig->identifier;
    deviceId = deviceID;
    return true;
  }
  else
  {
    returnStatus = unicap_enumerate_devices(NULL, deviceConfig,0);
    if(SUCCESS(returnStatus))
    {
      deviceID = deviceConfig->identifier;
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
    deviceNodeID = deviceConfig->device;
    deviceNodeId = deviceNodeID; 
    return true;
  }

  else
  {
    returnStatus = unicap_enumerate_devices(NULL, deviceConfig,0); 
    if(SUCCESS(returnStatus))
    {
      deviceNodeID = deviceConfig->device;
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
    devicePluginType = deviceConfig->cpi_layer;
    pluginName = devicePluginType; 
    return true;
  }
  else
  {
    returnStatus = unicap_enumerate_devices(NULL, deviceConfig,0);
    if(SUCCESS(returnStatus))
    {
      devicePluginType = deviceConfig->cpi_layer;
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
  returnStatus = unicap_enumerate_devices(NULL, deviceConfig, 0);

}

MonocularCameraConfiguration::~MonocularCameraConfiguration()
{
  delete colExpConfiguration;
  delete devConfiguration;
  delete propertyConfig;

}
