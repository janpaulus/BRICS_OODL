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
                                                                                                              deviceID (""), deviceNodeID (""), devicePluginType("") ,
                                                                                                              deviceConfig (device), handleConfig(handle)
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


CameraDeviceConfiguration::CameraDeviceConfiguration(): returnStatus(STATUS_FAILURE), deviceCameraDevConf(NULL),
                                                        handleCameraDevConf(NULL), deviceConfPropertyCounter(0)
{
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
}


CameraDeviceConfiguration::CameraDeviceConfiguration(unicap_device_t *device, unicap_handle_t *handle): returnStatus(STATUS_FAILURE), 
                                                                                                        deviceCameraDevConf(device),
                                                                                                        handleCameraDevConf(handle), 
                                                                                                        deviceConfPropertyCounter(0) 
{
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
}

//copy constructor
CameraDeviceConfiguration::CameraDeviceConfiguration(CameraDeviceConfiguration& cameradevconf) 
{

}

CameraDeviceConfiguration& CameraDeviceConfiguration::operator=(CameraDeviceConfiguration& cameradevconf) 
{
  if(&cameradevconf != this)
  {
    std::cout << "Inside CameraDeviceConfiguration assignment operator"<<std::endl;
  }
  return *this;
}



CameraDeviceConfiguration::~CameraDeviceConfiguration() {

  std::cout << "Destroying CameraDeviceConfiguration with arguments" << std::endl;

}


bool CameraDeviceConfiguration::getListOfDeviceProperties() {
  std::cout << "Inside CameraDeviceConfiguration getListOfDeviceProperties" << std::endl;

  //number of properties allocated is 30 for now, change it to const or make it dynamic
  for( int propertyCounter = 0; propertyCounter < 30 ; propertyCounter++ ) 
  {
    returnStatus = unicap_enumerate_properties( *handleCameraDevConf, NULL, &listOfProperties[propertyCounter], 
                                                propertyCounter);
    if( SUCCESS(returnStatus) )
    {
      std::cout << listOfProperties[propertyCounter].identifier<<std::endl;
      continue;
    }
    else
    {
      deviceConfPropertyCounter = propertyCounter;
      std::cout << "Number of properties" << propertyCounter<<std::endl;
      break;
    }
  }

  if(listOfProperties != NULL )
  {
    return true;
  }
  else
  {
    std::cout << "Property list is empty"<<std::endl;
    return false;
  }
 
}


// Make more efficient, so that I don't need to call enumerate_properties for each of the properties
// as it is done in if condition
bool CameraDeviceConfiguration::getVideoFrameRate(double &rate) 
{
  std::cout << "Inside CameraDeviceConfiguration getVideoFrameRate" << std::endl;
  const std::string propertyName ="frame rate";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties != NULL))
  {
   //here member variable deviceConfProperty is a total number of 
   //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
    //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
    //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
       //if range then check it for correct ID
        charID = listOfProperties[propertyCounter].identifier;
        //if ID == frame rate (as defined in unicap API) then return its current value
        if (charID == propertyName)
        {
          //check if the call succeeds 
          int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
          if( SUCCESS(returnValue) )
          {
            rate = listOfProperties[propertyCounter].value;
            //   std::cout << rate << std::endl;
            return true;
          }
        }
      }
     //if property is not of type "range" go to the beginning of the loop
      else
        continue;
    }
  }
 // if property list was not obtained successfully or was not filled in before through 
 //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties != NULL)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
        {
          charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
          {
            int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
            if( SUCCESS(returnValue) )
            {
              rate = listOfProperties[propertyCounter].value;
              return true;
            }
          }
        }
        //if property is not of type "range" go to the beginning of the loop
        else
          continue;
      }
    }
    std::cout << "Property list is empty"<< std::endl;
    return false;
  }
 // if neither of the above return error message
  else 
  {    
    std::cout << "Property list is empty"<< std::endl;
    return false;
  }
  
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




ColorExposureConfiguration::ColorExposureConfiguration(): deviceColorExposureDev(NULL), handleColorExposureDev(NULL),
                                                          colorConfPropertyCounter(0)
{
  std::cout << "Creating ColorExposureConfiguration without arguments" << std::endl;

}


ColorExposureConfiguration::ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle) {
  std::cout << "Creating ColorExposureConfiguration with arguments" << std::endl;
  deviceColorExposureDev = device;
  handleColorExposureDev = handle;
  colorConfPropertyCounter = 0;
}


ColorExposureConfiguration::ColorExposureConfiguration(ColorExposureConfiguration &colorconfig)
{


}

ColorExposureConfiguration& ColorExposureConfiguration::operator=(ColorExposureConfiguration &colorconfig)
{
  if(&colorconfig != this)
  {
    std::cout << "Inside ColorExposureConfiguration assignment" <<std::endl;
  }

  return *this;
}


ColorExposureConfiguration::~ColorExposureConfiguration() {
  std::cout << "Destroying ColorExposureConfiguration with arguments" << std::endl;

}


bool ColorExposureConfiguration::getListOfColorProperties() {
  std::cout << "Inside ColorExposureConfiguration getListOfColorProperties" << std::endl;

  //number of properties allocated is 30 for now, change it to const or make it dynamic
  for( int propertyCounter = 0; propertyCounter < 30 ; propertyCounter++ ) 
  {
    returnStatus = unicap_enumerate_properties( *handleColorExposureDev, NULL, &listOfProperties[propertyCounter], 
                                                propertyCounter);
    if( SUCCESS(returnStatus) )
    {
      std::cout << listOfProperties[propertyCounter].identifier<<std::endl;
      continue;
    }
    else
    {
      colorConfPropertyCounter = propertyCounter;
      std::cout << "Number of properties" << propertyCounter<<std::endl;
      break;
    }
  }

  if(listOfProperties != NULL )
  {
    return true;
  }
  else
  {
    std::cout << "Property list is empty"<<std::endl;
    return false;
  }
 
}

bool ColorExposureConfiguration::getHueValue(double &hue) {

  if (getListOfColorProperties() == true)
  {
    std::cout << "Inside ColorExposureConfiguration getHueValue" << std::endl;
    
    const std::string propertyName ="hue";
    if (listOfProperties != NULL)
    {
      //number of properties allocated is 30 for now, change it to const or make it dynamic
      for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE )
        {
          const std::string charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
            returnStatus = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); 
          if( SUCCESS(returnStatus) )
          {
            hue = listOfProperties[propertyCounter].value;
            std::cout << hue<<std::endl;
            return true;
          }
        }
        else
          continue;
    }
    else
    {
      std::cout << "Property list is empty"<<std::endl;
      return false;
    }
  }


}


bool ColorExposureConfiguration::getChromaValue(double &chroma) {

}

bool ColorExposureConfiguration::getSaturationValue(double &saturation) {
  if (getListOfColorProperties() == true)
  {
    std::cout << "Inside ColorExposureConfiguration getSaturationValue" << std::endl;
    
    const std::string propertyName ="saturation";
    if (listOfProperties != NULL)
    {
      //number of properties allocated is 30 for now, change it to const or make it dynamic
      for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE )
        {
          const std::string charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
            returnStatus = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); 
          if( SUCCESS(returnStatus) )
          {
            saturation = listOfProperties[propertyCounter].value;
            //std::cout << saturation <<std::endl;
            return true;
          }
        }
        else
          continue;
    }
    else
    {
      std::cout << "Property list is empty"<<std::endl;
      return false;
    }
  }

}

bool ColorExposureConfiguration::getColorTemperatureValue(double &temp) {

}

bool ColorExposureConfiguration::getWhiteBalanceUValue(double &uValue) {
  if (getListOfColorProperties() == true)
  {
    std::cout << "Inside ColorExposureConfiguration getWhiteBalanceUValue" << std::endl;
    
    const std::string propertyName ="white_balance_u";
    if (listOfProperties != NULL)
    {
      //number of properties allocated is 30 for now, change it to const or make it dynamic
      for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE )
        {
          const std::string charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
            returnStatus = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); 
          if( SUCCESS(returnStatus) )
          {
            uValue = listOfProperties[propertyCounter].value;
            //std::cout << uValue <<std::endl;
            return true;
          }
        }
        else
          continue;
    }
    else
    {
      std::cout << "Property list is empty"<<std::endl;
      return false;
    }
  }

}

bool ColorExposureConfiguration::getWhiteBalanceVValue(double &vValue) {

}

bool ColorExposureConfiguration::getBrightnessValue(double &brightness) {

  if (getListOfColorProperties() == true)
  {
    std::cout << "Inside ColorExposureConfiguration getBrightnessValue" << std::endl;
    
    const std::string propertyName ="brightness";
    if (listOfProperties != NULL)
    {
      //number of properties allocated is 30 for now, change it to const or make it dynamic
      for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE )
        {
          const std::string charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
            returnStatus = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); 
          if( SUCCESS(returnStatus) )
          {
            brightness = listOfProperties[propertyCounter].value;
            //std::cout << brightness<<std::endl;
            return true;
          }
        }
        else
          continue;
    }
    else
    {
      std::cout << "Property list is empty"<<std::endl;
      return false;
    }
  }

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


