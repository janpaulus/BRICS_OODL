#include "MonocularCamera.h"
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

  double hue = 0.0;
  (config.getColorExposureConfiguration())->getHueValue(hue);
  std::cout << hue <<std::endl;

  double brightness = 0.0;
  (config.getColorExposureConfiguration())->getBrightnessValue(brightness);
  std::cout << brightness <<std::endl;

  double saturation = 0.0;
  (config.getColorExposureConfiguration())->getSaturationValue(saturation);
  std::cout << saturation <<std::endl;


  return 0;
}
