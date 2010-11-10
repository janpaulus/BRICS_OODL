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
