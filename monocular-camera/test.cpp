#include "MonocularCamera.hpp"
#include <iostream>

int main (int argc, char **argv)
{

 
  MonocularCameraConfiguration config ;
  MonocularCamera camera(1);
  camera.getConfiguration(config);
  camera.open();


  std::string deviceName;
  config.getDeviceName(deviceName);
  std::cout << deviceName<<std::endl;

  double framerate = 0.0;
  (config.getCameraDeviceConfiguration())->getVideoFrameRate(framerate);
  std::cout << framerate <<std::endl;

  double gamma = 0.0;
  (config.getCameraDeviceConfiguration())->getVideoGammaValue(gamma);
  std::cout << gamma <<std::endl;

  double sharpness = 0.0;
  (config.getCameraDeviceConfiguration())->getVideoSharpnessValue(sharpness);
  std::cout << sharpness <<std::endl;


 


  return 0;
}
