#include "MonocularCamera.hpp"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>
#include <cstdio>

int main (int argc, char **argv)
{

  MonocularCameraConfiguration config ;
  ImageFormat format;
  MonocularCamera camera(0);
  


  camera.open(); //always open first
  camera.getConfiguration(config);
  double gain = 0.0;
  config.getColorExposureConfiguration()->getBrightnessValue(gain);
  std::cout << gain << std::endl;

  gain = 0;
  config.getColorExposureConfiguration()->setBrightnessValue(gain);
//  std::cout << gain << std::endl;
//  double rate = 0;
//  config.getCameraDeviceConfiguration()->getVideoFrameRate(rate);
//  std::cout << rate << std::endl;

  // set image format and start capturing  
  camera.getImageFormat(format) ;

  int width(0);
  int height(0);
  format.getImageFormatResolution(width, height);
  camera.setImageFormat(format) ;
  camera.capture();
/*  
   while(1)
   {
   Image2dData data(width,height);
    camera.getImageData(data);
   }
*/

  SDL_Surface *screen = NULL;
  SDL_Overlay *overlay = NULL;
  SDL_Rect rectArea = {0,0,width,height};
  int quitSignal = 0;

//  Initialise SDL
  if (SDL_Init (SDL_INIT_VIDEO) < 0) 
  {
    fprintf (stderr, "Failed to initialize SDL:  %s\n", SDL_GetError());
    exit (1);
  }

  screen = SDL_SetVideoMode (width, height, 32 , SDL_ANYFORMAT);

  if (screen == NULL) 
  {
    fprintf (stderr, "Unable to set video mode: %s\n", SDL_GetError ());
    SDL_Quit ();
    exit (1);
  }

  overlay = SDL_CreateYUVOverlay (width, height,SDL_YUY2_OVERLAY ,screen);  
  

  while(!quitSignal)
  {
    SDL_Event event;
    Image2dData data(width,height);   
      SDL_LockYUVOverlay(overlay);

    camera.getImageData(data);
    memcpy(overlay->pixels[0], (Uint8*)(data.buffer), data.bufferSize);




    SDL_UnlockYUVOverlay(overlay);
    SDL_DisplayYUVOverlay (overlay, &rectArea);


    
    while (SDL_PollEvent (&event))
    {
      if (event.type == SDL_QUIT)
	quitSignal = 1;
    }    

  }

   SDL_FreeYUVOverlay(overlay);
  SDL_Quit();



  camera.close();


  return 0;
}
