#include "MonocularCamera.hpp"
#include <iostream>


int main (int argc, char **argv)
{

 
  MonocularCameraConfiguration config ;
  MonocularCamera camera(1);
  ImageFormat format("RGB");


  camera.getConfiguration(config);
  std::string deviceName;
  config.getDeviceName(deviceName);
  std::cout << deviceName<<std::endl;

// set image format and start capturing  
  camera.open();
  camera.getImageFormat(format) ;
  camera.setImageFormat(format);
  camera.capture();
  camera.close();


  return 0;
}
