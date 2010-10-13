#include "MonocularCamera.h"
#include <iostream>

int main (int argc, char **argv)
{

 
  MonocularCamera camera;
  MonocularCameraConfiguration config ;

  camera.getConfiguration(config);



  std::string deviceName;
  config.getDeviceName(deviceName);

  std::cout << deviceName<<std::endl;


  return 0;
}
