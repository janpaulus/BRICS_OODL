#include "MonocularCamera.hpp"



MonocularCamera::MonocularCamera(int deviceNumber): isConnected(STATUS_FAILURE)
{
    std::cout<<"Creating Monocular Camera without arguments"<<std::endl;
    device = new unicap_device_t;
    deviceHandle = new unicap_handle_t;
    cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
}

MonocularCamera::MonocularCamera(MonocularCameraConfiguration &config, ImageFormat &format)
{
    std::cout<<"Creating Monocular Camera with arguments"<<std::endl;
    device = new unicap_device_t;
    deviceHandle = new unicap_handle_t;
    cameraConfig = new MonocularCameraConfiguration(device, deviceHandle);
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
    std::cout<<"In Monocular Camera setConfiguration"<<std::endl;
    *cameraConfig = config;
}



//bool MonocularCamera::resetDevice (Errors &error)
bool MonocularCamera::resetDevice ()
{
// unicap_stop_capture( deviceHandle[0] ); 
    std::cout<<"In Monocular Camera resetDevice"<<std::endl;
}

bool MonocularCamera::capture (Image2D &image)
{
  
    std::cout<<"In Monocular Camera capture"<<std::endl;
}
