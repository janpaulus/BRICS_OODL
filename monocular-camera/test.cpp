#include "MonocularCamera.hpp"
#include <iostream>


int main (int argc, char **argv)
{

 
  MonocularCameraConfiguration config ;
  MonocularCamera camera(1);
  Image2D image;


  camera.getConfiguration(config);
  camera.open();

  std::string deviceName;
  config.getDeviceName(deviceName);
  std::cout << deviceName<<std::endl;

// set image format and start capturing
  camera.capture(image);
  image.getImageFormat();
  image.getImageData();



  return 0;
}
