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

    bool getConfiguration (MonocularCameraConfiguration *config);
    bool setConfiguration (MonocularCameraConfiguration *config);
    bool resetDevice ();
    bool close ();

  private:
    MonocularCameraConfiguration *cameraConfig;
    ImageFormat *format;
    Image2dData *pixelData;
    unicap_device_t *device;
    unicap_handle_t *deviceHandle;
    bool open ();
    bool isConnected;
};


#endif //~_MONOCULARCAMERA_H_
