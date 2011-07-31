#include "MonocularCamera.hpp"
#include <iostream>

#include <cstdlib>
#include <cstdio>

int main (int argc, char **argv)
{
  using namespace brics_oodl;

    MonocularCameraConfiguration *config ;
    ImageFormat *format;
    MonocularCamera *camera;
    camera = new MonocularCamera(0);
    format = new ImageFormat();
    config = new MonocularCameraConfiguration();



    camera->open(); //always open first
    camera->getConfiguration(*config);

    double gain = 0.5;
    config->getColorExposureConfiguration()->getHueValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config->getColorExposureConfiguration()->setHueValue(gain);
    std::cout << gain << std::endl;

    config->getColorExposureConfiguration()->getGainControlValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config->getColorExposureConfiguration()->setGainControlValue(gain);
    std::cout << gain << std::endl;

    config->getColorExposureConfiguration()->getBrightnessValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config->getColorExposureConfiguration()->setBrightnessValue(gain);
    std::cout << gain << std::endl;


    config->getColorExposureConfiguration()->getSaturationValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config->getColorExposureConfiguration()->setSaturationValue(gain);
    std::cout << gain << std::endl;

    config->getCameraDeviceConfiguration()->getVideoSharpnessValue(gain);
    std::cout << gain << std::endl;

    gain = 0.5;
    config->getCameraDeviceConfiguration()->setVideoSharpnessValue(gain);
    std::cout << gain << std::endl;

    config->getCameraDeviceConfiguration()->getVideoGammaValue(gain);
    std::cout << gain << std::endl;

    gain = 0.2;
    config->getCameraDeviceConfiguration()->setVideoGammaValue(gain);
    std::cout << gain << std::endl;


    // set image format and start capturing
    camera->getImageFormat(*format) ;

    int width = 0;
    int height(0);
    format->getImageFormatResolution(width, height);
    camera->setImageFormat(*format) ;

    camera->capture();

    //should either provide image depth to Image2dData or through passing format from
    //enumeration (formats should include this information)

    PixelFormats pf = RGB16;


    while(true)
    {
      Image2dData data(width,height,pf);
      camera->getImageData(data);
    }

    camera->close();
    delete camera;
    delete format;
    delete config;

    return 0;
}
