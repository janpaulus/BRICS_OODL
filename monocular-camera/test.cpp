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

 double lensfocus = 0.0;
  (config.getCameraDeviceConfiguration())->getLensFocus(lensfocus);
  std::cout << lensfocus <<std::endl;

  double lensiris = 0.0;
  (config.getCameraDeviceConfiguration())->getLensIris(lensiris);
  std::cout << lensiris <<std::endl;

  double hue = 0.0;
  (config.getColorExposureConfiguration())->getHueValue(hue);
  std::cout << hue <<std::endl;

  double contrast = 0.0;
  (config.getColorExposureConfiguration())->getContrastValue(contrast);
  std::cout << contrast <<std::endl;

  double saturation = 0.0;
  (config.getColorExposureConfiguration())->getSaturationValue(saturation);
  std::cout << saturation <<std::endl;

  double wbuvalue = 0.0;
  (config.getColorExposureConfiguration())->getWhiteBalanceUValue(wbuvalue);
  std::cout << wbuvalue <<std::endl;

  double wbvvalue = 0.0;
  (config.getColorExposureConfiguration())->getWhiteBalanceVValue(wbvvalue);
  std::cout << wbvvalue <<std::endl;
 
  double brightness = 0.0;
  (config.getColorExposureConfiguration())->getBrightnessValue(brightness);
  std::cout << brightness <<std::endl;

  double newBrightness = 120;
  (config.getColorExposureConfiguration())->setBrightnessValue(newBrightness);

  (config.getColorExposureConfiguration())->getBrightnessValue(brightness);
  std::cout << brightness <<std::endl;


  double gain = 0.0;
  (config.getColorExposureConfiguration())->getGainControlValue(gain);
  std::cout << gain <<std::endl;

  double newGain = 250;
  (config.getColorExposureConfiguration())->setGainControlValue(newGain);

  (config.getColorExposureConfiguration())->getGainControlValue(gain);
  std::cout << gain <<std::endl;


  return 0;
}
