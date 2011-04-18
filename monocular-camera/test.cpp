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
    config.getColorExposureConfiguration()->getHueValue(gain);
    std::cout << gain << std::endl;

    gain = 1;
    config.getColorExposureConfiguration()->setHueValue(gain);
    std::cout << gain << std::endl;

    config.getColorExposureConfiguration()->getGainControlValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config.getColorExposureConfiguration()->setGainControlValue(gain);
    std::cout << gain << std::endl;

    config.getColorExposureConfiguration()->getBrightnessValue(gain);
    std::cout << gain << std::endl;

    gain = 0;
    config.getColorExposureConfiguration()->setBrightnessValue(gain);
    std::cout << gain << std::endl;


    config.getColorExposureConfiguration()->getSaturationValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config.getColorExposureConfiguration()->setSaturationValue(gain);
    std::cout << gain << std::endl;

/*
    gain = gain + 400;
    config.getColorExposureConfiguration()->setWhiteBalanceVValue(gain);
    std::cout << gain << std::endl;

    double rate = 0;
    config.getCameraDeviceConfiguration()->getVideoGammaValue(rate);
    std::cout << "Gamma  "<<rate << std::endl;

    config.getCameraDeviceConfiguration()->getVideoSharpnessValue(rate);
    std::cout << "Sharpness  "<<rate << std::endl;
*/

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

//should either provide image depth to Image2dData or through passing format from
    //enumeration (formats should include this information)

    PixelFormats pf = RGB16;

    while(!quitSignal)
    {
        SDL_Event event;
        Image2dData data(width,height,pf);
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
