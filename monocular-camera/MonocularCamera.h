#ifndef  _MONOCULARCAMERA_H_
#define  _MONOCULARCAMERA_H_

//#include "../generic/Errors.h"
//#include "../generic/Logger.h"
#include "../generic/Units.h"
#include "../generic-monocular-camera/MonocularCameraConfiguration.h"
#include "../generic-monocular-camera/ImageFormat.h"
#include "../generic-monocular-camera/Image2dData.h"
#include <unicap.h>

class MonocularCameraConfiguration;
class Image2dData;
class ImageFormat;

class MonocularCamera 
{
  public:
    MonocularCamera();
    MonocularCamera(MonocularCameraConfiguration &config, ImageFormat &format);
    ~MonocularCamera();
/*
    bool close (Errors &error);
    bool getConfiguration (MonocularCameraConfiguration &config, Errors &error);
    bool setConfiguration (MonocularCameraConfiguration &config, Errors &error);
    bool resetDevice (Errors &error);
*/
    bool close ();
    bool getConfiguration (MonocularCameraConfiguration &config);
    bool setConfiguration (MonocularCameraConfiguration &config);
    bool resetDevice ();

  private:
    bool isConnected;
    MonocularCameraConfiguration *config;
    ImageFormat *format;
    Image2dData *pixelData;
//    bool open (Errors &error);
    bool open ();
};


#endif //~_MONOCULARCAMERA_H_
