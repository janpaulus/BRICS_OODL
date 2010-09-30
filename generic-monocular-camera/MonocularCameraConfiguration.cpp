#include "MonocularCameraConfiguration.h"
#include <string>
#include <iostream>




MonocularCameraConfiguration::MonocularCameraConfiguration()
{
   deviceConfig = new unicap_property_t;
   deviceGeneralInfo = new unicap_device_t;
   returnStatus = STATUS_SUCCESS;

}


MonocularCameraConfiguration::~MonocularCameraConfiguration()
{
  delete deviceConfig;
  delete deviceGeneralInfo;

}


bool MonocularCameraConfiguration::getDeviceInfo(std::string deviceInfo[], int index)
{
  returnStatus = unicap_enumerate_devices(NULL, deviceGeneralInfo,0);
  if(SUCCESS(returnStatus))
  {
    deviceInf[0] = deviceGeneralInfo->identifier;
    deviceInfo[0] = deviceInf[0]; 
  }
  else
    std::cout << "Can not enumerate devices"<<std::endl;

}
