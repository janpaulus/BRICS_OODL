#include "MonocularCamera.h"
#include <iostream>

int main (int argc, char **argv)
{

  MonocularCameraConfiguration config;
  MonocularCamera camera;
  std::string info[10];

  config.getDeviceInfo(info, 10);
  std::cout << info[0]<<std::endl;
  

  return 0;
}
