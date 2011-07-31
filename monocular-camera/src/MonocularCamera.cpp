#include "MonocularCamera.hpp"

//Maybe again similar to properties and formats we can receive a list of devices and save them in the vector
// then according to provided ID chose the approapriate one
// Or create a device manager class which observers what devices are there connected to the system


MonocularCamera::MonocularCamera(int deviceNumber = 0): pixels(NULL),
    isConnected(STATUS_FAILURE),
    cameraDeviceCounter(0)
{
    if (getListOfCameras())
    {
        std::cout<<"Creating Monocular Camera"<< deviceNumber <<std::endl;
        currentDevice = &listOfCameraDevices[deviceNumber];
        deviceHandle = new unicap_handle_t;
        cameraConfig = new MonocularCameraConfiguration(currentDevice, deviceHandle);
        format = new ImageFormat(currentDevice, deviceHandle, "RGB");
    }
    else
    {
        std::cout << "Make sure that there is a camera connected" << std::cout;
    }

}

MonocularCamera::MonocularCamera(int deviceNumber, MonocularCameraConfiguration &config, std::string &fm):pixels(NULL),
    isConnected(STATUS_FAILURE),
    cameraDeviceCounter(0)
{
    if(getListOfCameras())
    {
        std::cout<<"Creating Monocular Camera"<< deviceNumber <<" with arguments config and format"<<std::endl;
        currentDevice = &listOfCameraDevices[deviceNumber];
        deviceHandle = new unicap_handle_t;
        cameraConfig = new MonocularCameraConfiguration(currentDevice, deviceHandle);
        format = new ImageFormat(currentDevice, deviceHandle, fm);
    }
    else
    {
        std::cout << "Make sure that there is a camera connected" << std::cout;
    }
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

  delete cameraConfig;
  delete format;
//    delete currentDevice;
    delete deviceHandle;
 // delete pixels;

}

//bool MonocularCamera::open (Errors &error)
bool MonocularCamera::open ()
{
    std::cout<<"In Monocular Camera open"<<std::endl;
    if(SUCCESS(isConnected))
    {
        std::cout << "Device is connected" <<std::endl;
        std::cout << "Opening device"<< currentDevice->identifier <<std::endl;
        isOpened = unicap_open(deviceHandle, currentDevice);
        if(SUCCESS(isOpened))
        {
            std::cout << "Device is successfully opened" << std::endl;
            return true;
        }
    }
    else
    {
        std::cout << "Could not find devices" << std::endl;
        return false;

    }

}


//bool MonocularCamera ::close (Errors &error)
bool MonocularCamera ::close ()
{
    std::cout<<"In Monocular Camera close"<<std::endl;
    int returnValue = unicap_stop_capture(*deviceHandle);
    if (SUCCESS(returnValue))
    {
        std::cout << "Stopped capture process, closing device" << std::endl;
        returnValue = unicap_close(*deviceHandle);
        if(SUCCESS(returnValue))
        {
            std::cout << "Device closed successfully" << std::endl;
            return true;
        }
    }
    else
        return false;
}


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
    if (SUCCESS(unicap_start_capture(*deviceHandle)))
    {
        std::cout<<"Device is ready for capture"<<std::endl;
        return true;
    }
    else
    {
        std::cout<<"Can not open device for capture"<<std::endl;
        return false;
    }

}

// TODO (azamat#2#): This capture method is blocking and sometimes it seems not
//to work with some cameras (in Alexeys case). Another approach is to use callbacks,
//which allows non-blocking capture mode. The method signature chould be changed
//with parameter type. Need to check unicap_callback

void MonocularCamera::getImageData(Image2dData& data)
{
    std::cout << "GetImageData"<< std::endl;

    // this is where pixel data sits
    unicap_data_buffer_t tempBuffer;

    // this is a pointer to pixel data buffer, it is needed by wait_buffer.
    //The data obtained should be accessed through this pointer. Because it does
    //all the necessary checking for pixel data before returning full/correct data buffer
    unicap_data_buffer_t *returnTempBuffer;

    int bufferSize = 0;
    format->getImageFormatSize(bufferSize);
    tempBuffer.data = new unsigned char[bufferSize];
    tempBuffer.buffer_size = bufferSize;


    //Put the buffer into a queue and wait till it is filled (wait_buffer does this)
    unicap_queue_buffer(*deviceHandle, &tempBuffer);
    //this waits till buffer is ready, it can be then processed through returnedTempBuffer
    if(SUCCESS( unicap_wait_buffer( *deviceHandle, &returnTempBuffer ) ) )
    {
        data.bufferSize = returnTempBuffer->buffer_size;
        memcpy(data.buffer, returnTempBuffer->data, returnTempBuffer->buffer_size);
        delete []tempBuffer.data;
    }
    else
    {
        std::cout << "Failed to wait for buffer" << std::endl;
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


//checks for the available cameras on the system
//and packs general info(device name, node file path etc)
//on them into a vector for future use
bool MonocularCamera::getListOfCameras()
{
    unicap_device_t tempDevice = {0};

    while(SUCCESS(unicap_enumerate_devices(NULL, &tempDevice, cameraDeviceCounter)))
    {
        listOfCameraDevices.push_back(tempDevice);
        cameraDeviceCounter++;

    }
    if(listOfCameraDevices.size() != 0)
    {
        isConnected = STATUS_SUCCESS;
        return true;
    }
    else
    {
        std::cout << "Could not find any cameras, make sure OS recognizes you camera!" << std::endl;
        return false;
    }

}
