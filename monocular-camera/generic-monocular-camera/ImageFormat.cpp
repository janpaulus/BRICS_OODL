#include "ImageFormat.hpp"


ImageFormat::ImageFormat():returnStatus(STATUS_FAILURE), numberOfResolutions(0),currentResolution(NULL), 
                           currentFormat(NULL), deviceFormatCounter(0), formatIdentifier(""), bitsPerPixel(8), 
                           fourcc(0), bufferSize(0), currentBufferType(UNICAP_BUFFER_TYPE_USER), deviceHandle(NULL)
{

  std::cout  << "Creating ImageFormat without args"<< std::endl;

}


ImageFormat::ImageFormat(std::string &formatID):returnStatus(STATUS_FAILURE), numberOfResolutions(0),currentResolution(NULL), 
                                                      currentFormat(NULL), deviceFormatCounter(0), 
                                                      bitsPerPixel(8), fourcc(0), bufferSize(0), 
                                                      currentBufferType(UNICAP_BUFFER_TYPE_USER),
                                                      deviceHandle(NULL), formatDevice(NULL)
{

  std::cout  << "Creating ImageFormat with formatID string argument"<< std::endl;

}

ImageFormat::ImageFormat(unicap_device_t* device, unicap_handle_t *handle, std::string formatIdentifier = "RGB"): returnStatus(STATUS_FAILURE), 
                                                                                                          numberOfResolutions(0),currentResolution(NULL), 
                                                                                                          currentFormat(NULL), deviceFormatCounter(0), 
                                                                                                          bitsPerPixel(8), fourcc(0), bufferSize(0), 
                                                                                                          currentBufferType(UNICAP_BUFFER_TYPE_USER),
                                                                                                          deviceHandle(handle), formatDevice(device)
{
  
  std::cout  << "Creating ImageFormat with all argument"<< std::endl;

}


ImageFormat::ImageFormat(ImageFormat &format)
{

  std::cout  << "Inside ImageFormat copy constructor"<< std::endl;

}


ImageFormat& ImageFormat::operator=(ImageFormat &format)
{
  std::cout  << "Inside ImageFormat assignment operator"<< std::endl;

  if(this !=&format)
  {
    std::cout << "Inside Format assignment operator" << std::endl;
    this ->currentResolution = format.currentResolution;
    this ->numberOfResolutions = format.numberOfResolutions;
//    this->listOfResolutions[] = format.listOfResolutions;
    this->deviceFormatCounter = format.deviceFormatCounter;
//    this->listOfDeviceFormats = format.listOfDeviceFormats;
    this->currentFormat = format.currentFormat;
    this->formatIdentifier = format.formatIdentifier;
    this->fourcc = format.fourcc;    
    this->bitsPerPixel = format.bitsPerPixel;
    this->flags = format.flags;
    this->bufferTypes = format.bufferTypes; 
    this->currentBufferType = format.currentBufferType;
    this->bufferSize = format.bufferSize;
    this->returnStatus = format.returnStatus;
    this->deviceHandle = format.deviceHandle;
    this->formatDevice = format.formatDevice;
    return *this;
  }

}



ImageFormat:: ~ImageFormat()
{
  std::cout  << "Destroying ImageFormat"<< std::endl;

}



bool ImageFormat::getImageFormatStringName(std::string &formatName)
{
  if(SUCCESS(this->returnStatus)) //if getListOfFormats called don't call   
  {
    formatName = currentFormat->identifier;
    return true;
  }
  else if (getListOfFormats())
  {
    formatName = currentFormat->identifier;
    return true;
  }
  else
  {
    std::cout << "Could not list formats" << std::endl;
    return false;
  }
}


bool ImageFormat::getImageFormatFOURCC(unsigned int &fourcc)
{

  if(SUCCESS(this->returnStatus)) //if getListOfFormats called don't call   
  {
    fourcc = currentFormat->fourcc;
    return true;
  }
  else if (getListOfFormats())
  {
    fourcc = currentFormat->fourcc;
    return true;
  }
  else
  {
    std::cout << "Could not list formats" << std::endl;
    return false;
  }
 
}


bool ImageFormat::getImageFormatResolution(int &width, int &height)
{

 if(SUCCESS(this->returnStatus)) //if getListOfFormats called don't call   
  {
    width = currentResolution->width;
    height = currentResolution->height;
    return true;
  }
  else if (getListOfFormats())
  {
    width = currentResolution->width;
    height = currentResolution->height;
    return true;
  }
  else
  {
    std::cout << "Could not list formats" << std::endl;
    return false;
  }
 
}


bool ImageFormat::getImageFormatColorModel(std::string &colorModel)
{
  if(getImageFormatStringName(colorModel))
    return true;
  else
    return false;
}
     


bool ImageFormat::getImageFormatResolutionList()
{

  return true;
}

bool ImageFormat::getImageFormatColorModelList()
{

  return true;
}

bool ImageFormat::setImageFormatColorModel(std::string &colorModel)
{

  return true;
}


bool ImageFormat::setImageFormatResolution(int &width, int &height)
{

  return true;
}

bool ImageFormat::getImageFormatSize(int &size)
{

  return true;
}

// the problem is that image format is sth device dependent, whether camera sensor supports some format
// but at the same time it is property of an image.
// image is an entity of its own but at the same time it can't exist without a device which generates it.
// Actually, it underlies the focus of this API, that is, it is only to work with cameras and not with standalone pictures.
//  returnStatus = unicap_enumerate_formats(deviceHandle, NULL, listOfDeviceFormats, deviceFormatCounter);
// 
//should create a format object and pass it handle
//also pass it the formats obtained 
bool ImageFormat::getListOfFormats()
{
  std::cout << "Inside Monocular Camera getListOfFormats"<<std::endl;
  if(deviceHandle!=NULL)
  {
    std::cout << "Device is open getting available formats" << std::endl;
    for(int i = 0; i<10; i++)
    {
      this->returnStatus = unicap_enumerate_formats(*deviceHandle, NULL, &listOfDeviceFormats[i], i);
      if(SUCCESS(this->returnStatus))
      {
        deviceFormatCounter++;
        std::cout << listOfDeviceFormats[i].identifier << std::endl; 
    
      }
      else
      {
        break;
     }
    }
  }
  if(listOfDeviceFormats != NULL) //should change all these arrays with vectors
  {
    //set the default format to the first format in the list;
    currentFormat = &listOfDeviceFormats[0];
    currentResolution = &listOfDeviceFormats[0].min_size;
    int returnValue = unicap_set_format(*deviceHandle, currentFormat);
    std::cout << "Setting default format to " << currentFormat->identifier << std::endl;
    std::cout << "Setting default resolution to " << currentResolution->width << "x" <<currentResolution->height<< std::endl;
    if (SUCCESS(returnValue))
    {
      this->returnStatus = STATUS_SUCCESS;
      return true;
    }
  }
  else 
  {
    std::cout << "Could not enumerate formats" << std::endl;
    return false;
  }
}

