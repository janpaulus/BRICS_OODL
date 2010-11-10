#ifndef  _MONOCULARCAMERA_H_
#define  _MONOCULARCAMERA_H_

//#include "../generic/Errors.h"
//#include "../generic/Logger.h"
#include "../generic/Units.h"
#include "../generic-monocular-camera/MonocularCameraConfiguration.hpp"
#include "../generic-monocular-camera/ImageFormat.hpp"
#include "../generic-monocular-camera/Image2dData.hpp"
#include <unicap.h>
#include <iostream>

class Image2dData;
class ImageFormat;

class MonocularCamera 
{
public:
    MonocularCamera(int deviceNumber);
    MonocularCamera(MonocularCameraConfiguration &config, ImageFormat &format);
    MonocularCamera(MonocularCamera &camera);
    MonocularCamera& operator= (const MonocularCamera &camera);
    ~MonocularCamera();

    bool getConfiguration (MonocularCameraConfiguration &config);
    bool setConfiguration (MonocularCameraConfiguration &config);
    bool resetDevice ();
    bool close ();
    bool open ();
    bool capture();
private:
    MonocularCameraConfiguration *cameraConfig;
    ImageFormat *format;
    Image2dData *pixelData;
    unicap_device_t *device;
    unicap_handle_t *deviceHandle;
    unicap_status_t isConnected;
};


#endif //~_MONOCULARCAMERA_H_
