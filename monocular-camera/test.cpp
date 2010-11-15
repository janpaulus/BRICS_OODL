#include "MonocularCamera.hpp"
#include <iostream>


int main (int argc, char **argv)
{

 
  MonocularCameraConfiguration config ;
  MonocularCamera camera(1);
  
  std::string x ="RGB";
  std::string deviceName;

  ImageFormat format(x);
  camera.open(); //always open first

  camera.getConfiguration(config);
  config.getDeviceName(deviceName);
  std::cout << deviceName<<std::endl;

  double hue = 0;
  (config.getColorExposureConfiguration())->getBrightnessValue(hue);

// set image format and start capturing  
  camera.getImageFormat(format) ;
  std::string formatName;
  format.getImageFormatStringName(formatName);
  std::cout << formatName << std::endl;

  unsigned int fourcc = 0;
  format.getImageFormatFOURCC(fourcc);

  int width(0);
  int height(0);
  format.getImageFormatResolution(width, height);
  std::cout << width << std::endl;
  std::cout << height << std::endl;

  format.getImageFormatColorModel(formatName);
  std::cout << formatName << std::endl;

  Image2dData data(width, height);
  camera.capture(data);
  camera.close();


  return 0;
}
