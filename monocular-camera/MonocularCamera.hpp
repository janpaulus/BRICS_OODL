#ifndef  _MONOCULARCAMERA_H_
#define  _MONOCULARCAMERA_H_

//#include "../generic/Errors.hpp"
//#include "../generic/Logger.hpp"
#include "../generic/Units.hpp"
#include "../generic-monocular-camera/MonocularCameraConfiguration.hpp"
#include "../generic-monocular-camera/Image2dData.hpp"
#include "../generic-monocular-camera/ImageFormat.hpp"
#include <unicap.h>
#include <iostream>


class MonocularCamera 
{
public:
     MonocularCamera(int deviceNumber);
     MonocularCamera(MonocularCamera &camera);
     MonocularCamera(MonocularCameraConfiguration &config, ImageFormat &format);
     MonocularCamera& operator= (const MonocularCamera &camera);
     ~MonocularCamera();

     bool getConfiguration (MonocularCameraConfiguration &config);
     bool setConfiguration (MonocularCameraConfiguration &config);
     bool getImageFormat(ImageFormat &format);
     bool setImageFormat(ImageFormat &format);

     bool capture(/*int frames*/); // adding frames here could be good, then a user does not have to bother about building capture loops.
     bool open ();
     bool close ();

private:
     MonocularCameraConfiguration *cameraConfig;
     Image2dData *imagedata;
     ImageFormat *format;
     unicap_device_t *device;
     unicap_handle_t *deviceHandle;
     unicap_status_t isConnected;
};


#endif //~_MONOCULARCAMERA_H_
