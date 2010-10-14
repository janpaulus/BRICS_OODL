#include "MonocularCamera.h"
#include <iostream>

int main (int argc, char **argv)
{

 
  MonocularCameraConfiguration config ;
  MonocularCamera camera(1);

  camera.getConfiguration(config);



  std::string deviceName;
  config.getDeviceName(deviceName);
  std::cout << deviceName<<std::endl;
  config.getDeviceNodeID(deviceName);
  std::cout << deviceName<<std::endl;
  config.getDevicePluginType(deviceName);
  std::cout << deviceName<<std::endl;


  return 0;
}
