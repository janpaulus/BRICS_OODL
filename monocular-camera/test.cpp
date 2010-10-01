#include "MonocularCamera.h"
#include <iostream>

int main (int argc, char **argv)
{

  MonocularCameraConfiguration config;
  MonocularCamera camera;
  std::string deviceName;
  std::string deviceNodeID;
  std::string devicePluginType;

  config.getDeviceName(deviceName);
  config.getDeviceNodeID(deviceNodeID);
  config.getDevicePluginType(devicePluginType);

  std::cout << deviceName<<std::endl;
  std::cout << deviceNodeID<<std::endl;
  std::cout << devicePluginType<<std::endl;
  

  return 0;
}
