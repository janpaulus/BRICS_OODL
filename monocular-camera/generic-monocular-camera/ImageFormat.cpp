#include "ImageFormat.hpp"


ImageFormat::ImageFormat():returnStatus(STATUS_FAILURE), 
			   numberOfResolutions(0),
			   currentResolution(NULL), 
                           currentFormat(NULL), 
			   deviceFormatCounter(0), 
			   formatIdentifier(""), 
			   bitsPerPixel(8), 
                           fourcc(0), bufferSize(0), 
			   currentBufferType(UNICAP_BUFFER_TYPE_USER), 
			   deviceHandle(NULL)
{

  std::cout  << "Creating ImageFormat without args"<< std::endl;

}


ImageFormat::ImageFormat(std::string &formatID):returnStatus(STATUS_FAILURE), 
						numberOfResolutions(0),
						currentResolution(NULL), 
						currentFormat(NULL), 
						deviceFormatCounter(0), 
						bitsPerPixel(8), 
						fourcc(0), 
						bufferSize(0), 
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
    currentResolution = format.currentResolution;
    numberOfResolutions = format.numberOfResolutions;
    deviceFormatCounter = format.deviceFormatCounter;
    currentFormat = format.currentFormat;
    formatIdentifier = format.formatIdentifier;
    fourcc = format.fourcc;    
    bitsPerPixel = format.bitsPerPixel;
    flags = format.flags;
    bufferTypes = format.bufferTypes; 
    currentBufferType = format.currentBufferType;
    bufferSize = format.bufferSize;
    returnStatus = format.returnStatus;
    deviceHandle = format.deviceHandle;
    formatDevice = format.formatDevice;
    //copy vector contents later
  }
  return *this;
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
    for(int i=0; i<currentFormat->size_count; i++)
    {
        std::cout << currentFormat->sizes[i].width<< "x" << currentFormat->sizes[i].height <<std::endl;
    }
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

bool ImageFormat::getImageFormatSize(long int &size)
{

  bufferSize = (currentResolution->width)*(currentResolution->height);
  size = bufferSize;
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
  unicap_format_t tempFormat = {0};
  if(deviceHandle!=NULL)
  {
    std::cout << "Device is open getting available formats" << std::endl;
    while(SUCCESS(unicap_enumerate_formats(*deviceHandle, NULL, &tempFormat, deviceFormatCounter)))
    {

        listOfDeviceFormats.push_back(tempFormat);
        std::cout << listOfDeviceFormats[deviceFormatCounter].identifier << std::endl;
        std::cout << listOfDeviceFormats[deviceFormatCounter].size_count << std::endl;
        std::cout << listOfDeviceFormats.size() << std::endl;
        deviceFormatCounter++;
      
    }
  }
  if(listOfDeviceFormats.size() != 0) //should change all these arrays with vectors
  {
    //set the default format to the first format in the list;
    currentFormat = &listOfDeviceFormats[0];
    currentResolution = &listOfDeviceFormats[0].size;
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

