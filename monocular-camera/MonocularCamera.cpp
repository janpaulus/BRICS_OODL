#include "MonocularCamera.hpp"


MonocularCamera::MonocularCamera(int deviceNumber): pixels(NULL), isConnected(STATUS_FAILURE)
													
{
  std::cout<<"Creating Monocular Camera without arguments"<<std::endl;
  device = new unicap_device_t;
  deviceHandle = new unicap_handle_t;
  cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
  format = new ImageFormat(device, deviceHandle, "RGB");
}

MonocularCamera::MonocularCamera(MonocularCameraConfiguration &config, std::string &fm):pixels(NULL),isConnected(STATUS_FAILURE)
{
  std::cout<<"Creating Monocular Camera with arguments"<<std::endl;
  device = new unicap_device_t;
  deviceHandle = new unicap_handle_t;
  cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
  format = new ImageFormat(device, deviceHandle, fm);
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
  //Maybe we need to call close on device implicitly without user being aware of it.
  //But then open should also be implicit to make things consistent.

//  delete cameraConfig;
//  delete format;
  delete device;
  delete deviceHandle;
//  delete pixels;

}

//bool MonocularCamera::open (Errors &error)
bool MonocularCamera::open ()
{
  std::cout<<"In Monocular Camera open"<<std::endl;
  if(SUCCESS(isConnected))
  {
    std::cout << "Device is already open" <<std::endl;
    return true;
  }
  else
  {
    isConnected = unicap_enumerate_devices(NULL, device, 0);
    if(SUCCESS(isConnected))
    {
      std::cout << "Openning camera"<<std::endl;
      isConnected = unicap_open(deviceHandle, device);
      if(SUCCESS(isConnected))
      {
	std::cout << "Device is successfully opened" << std::endl;

                
	return true;
      }
      else
      {
	std::cout << "Could not open device" << std::endl;
	return false;
      }
    }
    else
    {
      std::cout << "Could not find devices" << std::endl;
      return false;
    }
  }

}


//bool MonocularCamera ::close (Errors &error)
bool MonocularCamera ::close ()
{
  std::cout<<"In Monocular Camera close"<<std::endl;
  //  unicap_close(deviceHandle[0]);
  return true;
}


//bool MonocularCamera::getConfiguration (MonocularCameraConfiguration &config, Errors &error)
bool MonocularCamera::getConfiguration (MonocularCameraConfiguration &config)
{
  std::cout<<"In Monocular Camera getConfiguration"<<std::endl;

  config = *cameraConfig;
  return true;
}


bool MonocularCamera::setConfiguration ( MonocularCameraConfiguration &config)
{
  std::cout<<"In Monocular Camera setConfiguration"<<std::endl;
  *cameraConfig = config;
  return true;
}


bool MonocularCamera::capture ()
{
  std::cout<<"In Monocular Camera capture"<<std::endl;
  
  if (SUCCESS(unicap_start_capture(*deviceHandle))) 
  {
    return true; 
  }

  else
  { 
    return false;
  }
  
}


Image2dData* MonocularCamera::getImageData()
{
  std::cout << "GetImageData"<< std::endl;

  // this is where pixel data sits
  unicap_data_buffer_t tempBuffer; 
  // this pointer to pixel data buffer, it is needed by wait_buffer. 
  //The data obtained should be accessed through this pointer. Because it does 
  //all the necessary checking for pixel data before returning full/correct data buffer
  unicap_data_buffer_t *returnTempBuffer; 
  
  long int bufferSize = 0 ;
  format->getImageFormatSize(bufferSize);
  tempBuffer.data = new unsigned char[bufferSize];
  tempBuffer.buffer_size = bufferSize;

  //Put the buffer into a queue and wait till it is filled (wait_buffer does this)
  unicap_queue_buffer(*deviceHandle, &tempBuffer);
  //this waits till buffer is ready, it can be then processed through returnedTempBuffer
  if( !SUCCESS( unicap_wait_buffer( *deviceHandle, &returnTempBuffer ) ) )
  {
    std::cout << "Failed to wait for buffer" << std::endl;
    return NULL;
  }
  else
  {
    Image2dData x = Image2dData ((*returnTempBuffer).data,(*returnTempBuffer).buffer_size);
    pixels = &x;
    return pixels;
  }

}

bool MonocularCamera::getImageFormat(ImageFormat &fm)
{
  std::cout<<"In Monocular Camera getImageFormat"<<std::endl;
  fm = *format;
  return true;

}

bool MonocularCamera::setImageFormat(ImageFormat &fm)
{

  std::cout<<"In Monocular Camera setImageFormat"<<std::endl;
  format = &fm;
  return true;
}
