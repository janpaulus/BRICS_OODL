#include "ImageFormat.hpp"


ImageFormat::ImageFormat()
{

}


ImageFormat::ImageFormat(ImageFormat &format)
{


}


ImageFormat& ImageFormat::operator=(ImageFormat &format)
{


}



ImageFormat:: ~ImageFormat()
{


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


bool ImageFormat::getListOfSupportedFormats()
{
// the problem is that image format is sth device dependent, whether camera sensor supports some format
// but at the same time it is property of an image.
// image is an entity of its own but at the same time it can't exist without a device which generates it.
// Actually, it underlies the focus of this API, that is, it is only to work with cameras and not with standalone pictures.
//  returnStatus = unicap_enumerate_formats(deviceHandle, NULL, listOfDeviceFormats, deviceFormatCounter);

}
