#include "ImageFormat.hpp"


ImageFormat::ImageFormat():returnStatus(STATUS_FAILURE), numberOfResolutions(0),currentResolution(NULL), 
                           currentFormat(NULL), deviceFormatCounter(0), formatIdentifier(""), bitsPerPixel(8), 
                           fourcc(0), bufferSize(0), currentBufferType(0)
{
  std::cout  << "Creating ImageFormat without args"<< std::endl;
}

ImageFormat::ImageFormat(std::string formatIdentifier)
{
  this->formatIdentifier = formatIdentifier;
  std::cout  << "Creating ImageFormat without formatIdentifier"<< std::endl;

}

ImageFormat::ImageFormat(unicap_handle_t *handle)
{

  deviceHandle = handle;

}


ImageFormat::ImageFormat(ImageFormat &format)
{
  std::cout  << "Inside ImageFormat copy constructor"<< std::endl;

}


ImageFormat& ImageFormat::operator=(ImageFormat &format)
{


}



ImageFormat:: ~ImageFormat()
{
  std::cout  << "Destroying ImageFormat"<< std::endl;

}



bool ImageFormat::getImageFormatStringName(std::string &formatName)
{

  return true;
}


bool ImageFormat::getImageFormatFOURCC(unsigned int &fourcc)
{

  return true;
}


bool ImageFormat::getImageFormatResolution(int &width, int &height)
{

  return true;
}


bool ImageFormat::getImageFormatColorModel(std::string &colorModel)
{

  return true;
}
     


bool ImageFormat::setImageFormatColorModel(std::string &colorModel)
{

  return true;
}



// the problem is that image format is sth device dependent, whether camera sensor supports some format
// but at the same time it is property of an image.
// image is an entity of its own but at the same time it can't exist without a device which generates it.
// Actually, it underlies the focus of this API, that is, it is only to work with cameras and not with standalone pictures.
//  returnStatus = unicap_enumerate_formats(deviceHandle, NULL, listOfDeviceFormats, deviceFormatCounter);

//should create a format object and pass it handle
//also pass it the formats obtained 
bool ImageFormat::getListOfFormats()
{
  std::cout << "Inside Monocular Camera getListOfFormats"<<std::endl;
  if(SUCCESS(returnStatus))
  {
    std::cout << "Device is open getting available formats" << std::endl;
    for(int i = 0; i<10; i++)
    {
      int returnStatus = unicap_enumerate_formats(*deviceHandle, NULL, &listOfDeviceFormats[i], i);
      if(SUCCESS(returnStatus))
      {
        deviceFormatCounter++;
        std::cout << listOfDeviceFormats[i].identifier<< std::endl; 
      }
      else
      {
        break;
      }
    }
  }
  if(listOfDeviceFormats != NULL)
  {
    //set the default format to the first format in the list;
 
    return true;
  }
  else 
  {
    std::cout << "Could not enumerate formats" << std::endl;
    return false;
  }
}

