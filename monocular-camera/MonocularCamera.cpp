#include "MonocularCamera.h"



MonocularCamera::MonocularCamera() 
{
  std::cout<<"Creating Monocular Camera without arguments"<<std::endl;
 
  device = new unicap_device_t;
  deviceHandle = new unicap_handle_t;
  cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
}

MonocularCamera::MonocularCamera(MonocularCameraConfiguration &config, ImageFormat &format)
{
  std::cout<<"Creating Monocular Camera with arguments"<<std::endl;

}


MonocularCamera::MonocularCamera(MonocularCamera &camera)
{
  std::cout<<"Creating Copy of Monocular Camera"<<std::endl;

}

MonocularCamera& MonocularCamera::operator= (const MonocularCamera &camera)
{
  if(&camera != this)
  {
    std::cout<<"Assigning MonocularCamera"<<std::endl;
  }

  return *this;
}

MonocularCamera::~MonocularCamera()
{
  std::cout<<"Destroying Monocular Camera"<<std::endl;

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
bool MonocularCamera::getConfiguration (MonocularCameraConfiguration &config)
{
  std::cout<<"In Monocular Camera getConfiguration"<<std::endl;

  config = *cameraConfig;
}


//bool MonocularCamera::setConfiguration (MonocularCameraConfiguration &config, Errors &error)
bool MonocularCamera::setConfiguration (MonocularCameraConfiguration &config)
{


}



//bool MonocularCamera::resetDevice (Errors &error)
bool MonocularCamera::resetDevice ()
{


}
