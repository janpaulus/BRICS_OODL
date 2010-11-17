#include "MonocularCamera.hpp"



MonocularCamera::MonocularCamera(int deviceNumber): isConnected(STATUS_FAILURE)
{
  std::cout<<"Creating Monocular Camera without arguments"<<std::endl;
  device = new unicap_device_t;
  deviceHandle = new unicap_handle_t;
  cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
  format = new ImageFormat(device, deviceHandle, "RGB");
  imagedata = new Image2dData;
}

MonocularCamera::MonocularCamera(MonocularCameraConfiguration &config, std::string &format): isConnected(STATUS_FAILURE)
{
  std::cout<<"Creating Monocular Camera with arguments"<<std::endl;
  device = new unicap_device_t;
  deviceHandle = new unicap_handle_t;
  cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
  this->format = new ImageFormat(device, deviceHandle, format);
  imagedata = new Image2dData;

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
  //this->close();
  delete device;
  delete deviceHandle;
  delete format;
  delete imagedata;
  //  delete cameraConfig;
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
			  //             int returnValue = getListOfFormats();
                
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


//bool MonocularCamera::setConfiguration (MonocularCameraConfiguration &config, Errors &error)
bool MonocularCamera::setConfiguration ( MonocularCameraConfiguration &config)
{
  std::cout<<"In Monocular Camera setConfiguration"<<std::endl;
  *cameraConfig = config;
  return true;
}


bool MonocularCamera::capture (Image2dData &data)
{
  unicap_data_buffer_t tempBuffer;
  unicap_data_buffer_t *returnedBuffer;

  tempBuffer.data  = data.getBuffer();
  tempBuffer.buffer_size = data.getBufferSize();
  
  std::cout<<"In Monocular Camera capture"<<std::endl;
  unicap_start_capture(*deviceHandle); 
  
  int i = 0;
  while (i<100)
    {
      unicap_queue_buffer(*deviceHandle, &tempBuffer);

      //this waits till buffer is filled with image data and then dequeue it   
      if( !SUCCESS( unicap_wait_buffer( *deviceHandle, &returnedBuffer ) ) )
		{
		  fprintf( stderr, "Failed to wait for buffer!\n" );
		  return false;
		}
      i++;

    }
  return true;
}


bool MonocularCamera::getImageFormat(ImageFormat &format)
{
  std::cout<<"In Monocular Camera getImageFormat"<<std::endl;
  format = *(this->format);
  return true;

}

bool MonocularCamera::setImageFormat(ImageFormat &format)
{

  std::cout<<"In Monocular Camera setImageFormat"<<std::endl;
  return true;
}
