#include "MonocularCamera.hpp"
#include <iostream>


int main (int argc, char **argv)
{

  MonocularCameraConfiguration config ;
  ImageFormat format;
  MonocularCamera camera(1);



  camera.open(); //always open first

  camera.getConfiguration(config);

  // set image format and start capturing  
  camera.getImageFormat(format) ;

  int width(0);
  int height(0);
  format.getImageFormatResolution(width, height);
  camera.setImageFormat(format) ;
  camera.capture();
  
 std::cout << width << std::endl;
  std::cout << height << std::endl;
  while(1)
    camera.getImageData();
  camera.close();


  return 0;
}
