#ifndef  _MONOCULARCAMERA_H_
#define  _MONOCULARCAMERA_H_

//#include "../generic/Errors.hpp"
//#include "../generic/Logger.hpp"
#include "../generic/Units.hpp"
#include "../generic-monocular-camera/MonocularCameraConfiguration.hpp"
#include "../generic-monocular-camera/Image2D.hpp"
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
    bool capture(Image2D &image);
private:
    MonocularCameraConfiguration *cameraConfig;
    Image2D *image;
    unicap_device_t *device;
    unicap_handle_t *deviceHandle;
    unicap_status_t isConnected;
};


#endif //~_MONOCULARCAMERA_H_
