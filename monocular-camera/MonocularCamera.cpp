#include "MonocularCamera.h"



MonocularCamera::MonocularCamera() 
{
    device = new unicap_device_t;
    deviceHandle = new unicap_handle_t;
    cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
}

MonocularCamera::MonocularCamera(MonocularCameraConfiguration &config, ImageFormat &format)
{


}

 
MonocularCamera::~MonocularCamera()
{
  delete device;
  delete deviceHandle;
  delete cameraConfig;
}

//bool MonocularCamera::open (Errors &error)
bool MonocularCamera::open ()
{


}


//bool MonocularCamera ::close (Errors &error)
bool MonocularCamera ::close ()
{


}


//bool MonocularCamera::getConfiguration (MonocularCameraConfiguration &config, Errors &error)
bool MonocularCamera::getConfiguration (MonocularCameraConfiguration *config)
{
  config = cameraConfig;
}


//bool MonocularCamera::setConfiguration (MonocularCameraConfiguration &config, Errors &error)
bool MonocularCamera::setConfiguration (MonocularCameraConfiguration *config)
{


}



//bool MonocularCamera::resetDevice (Errors &error)
bool MonocularCamera::resetDevice ()
{


}
