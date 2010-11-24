#include "MonocularCamera.hpp"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>
#include <cstdio>

int main (int argc, char **argv)
{

  MonocularCameraConfiguration config ;
  ImageFormat format;
  MonocularCamera camera(1);



  camera.open(); //always open first

  camera.getConfiguration(config);
  double gain = 0.0;
  config.getColorExposureConfiguration()->getGainControlValue(gain);
  std::cout << gain << std::endl;

  double rate = 0;
  config.getCameraDeviceConfiguration()->getVideoFrameRate(rate);
  std::cout << rate << std::endl;

  // set image format and start capturing  
  camera.getImageFormat(format) ;

  int width(0);
  int height(0);
  format.getImageFormatResolution(width, height);
  format.getImageFormatResolutionList();
  camera.setImageFormat(format) ;
  camera.capture();

  while(1)
    camera.getImageData(width,height)->getBuffer();


/*
  SDL_Surface *screen;
  SDL_Surface *rgb_surface;
//  Initialise SDL
  
if (SDL_Init (SDL_INIT_VIDEO) < 0) {
fprintf (stderr, "Failed to initialize SDL:  %s\n", SDL_GetError());
exit (1);
}
screen = SDL_SetVideoMode (640, 480, 16 , SDL_SWSURFACE|SDL_ANYFORMAT);
if (screen == NULL) {
fprintf (stderr, "Unable to set video mode: %s\n", SDL_GetError ());
SDL_Quit ();
exit (1);
}

  
//here in the loop should include send request first and then receive, when peer is in client consumer mode
//otherise when subscriber consumer mode it just receives.
int quitSignal = 0;
while(!quitSignal)
{
std::cout << camera.getImageData()->getBufferSize() << std::endl;
SDL_Event event;
rgb_surface = SDL_CreateRGBSurfaceFrom (
camera.getImageData()->getBuffer(),           //  Pixel data
640,     //  Widtha
480,    //  Height
16,//dest_format.bpp,            //  Depth
1920,//dest_format.size.width * 3, //  Scanline pitch
0, 0, 0, 0);                //  TODO RGBA mask 
   
//  Blit surface to screen
    
SDL_BlitSurface (rgb_surface, NULL, screen, NULL);
SDL_UpdateRect (screen, 0, 0, 0, 0);
SDL_FreeSurface (rgb_surface);
    
while (SDL_PollEvent (&event))
{
if (event.type == SDL_QUIT)
quitSignal = 1;
}    

}
    
SDL_Quit();

*/


  camera.close();


  return 0;
}
