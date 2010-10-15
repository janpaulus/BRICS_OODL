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
  config.getDeviceNodeID(deviceName);
  std::cout << deviceName<<std::endl;
  config.getDevicePluginType(deviceName);
  std::cout << deviceName<<std::endl;



  config.getCameraDeviceConfiguration().getListOfDeviceProperties();
/*  double framerate;
  config.getCameraDeviceConfiguration().getVideoFrameRate(framerate);
  config.getCameraDeviceConfiguration().getVideoGammaValue(framerate); 
  config.getCameraDeviceConfiguration().getVideoSharpnessValue(framerate);
  config.getCameraDeviceConfiguration().getLensFocus(framerate);
  config.getCameraDeviceConfiguration().getLensZoom(framerate); 
  config.getCameraDeviceConfiguration().getLensIris(framerate); 


  config.getCameraDeviceConfiguration().setVideoFrameRate(framerate);
  config.getCameraDeviceConfiguration().setVideoGammaValue(framerate); 
  config.getCameraDeviceConfiguration().setVideoSharpnessValue(framerate);
  config.getCameraDeviceConfiguration().setLensFocus(framerate);
  config.getCameraDeviceConfiguration().setLensZoom(framerate); 
  config.getCameraDeviceConfiguration().setLensIris(framerate); 

*/

  return 0;
}
