#include "Image2dData.hpp"


//buffer size is not only dependent on image resolution but also color depths (bpp)
// so need to think over how this should be done

Image2dData::Image2dData()
{
  buffer = NULL;
  bufferSize = 0;
}


Image2dData::Image2dData(unsigned char *bufferStart = NULL, size_t length = 0)
{
  buffer = bufferStart;
  bufferSize = length;
}

Image2dData::Image2dData(int& width, int& height, PixelFormats& pixelformat)
{
  bufferSize = width * height;
  if(pixelformat == RGB16)
  {
    buffer = new unsigned char[2*bufferSize];
  }
  if(pixelformat == RGB24)
  {
    buffer = new unsigned char[3*bufferSize];
  }
}

Image2dData& Image2dData::operator=(Image2dData& data)
{
  if(&data != this)
  {
    std::cout << "In the assignment operator" << std::endl;
  }
  return *this;
}

unsigned char* Image2dData::getBuffer()
{
  if(buffer != NULL)
  {

    return buffer;
  }
  else
  {
    std::cout << "Failed to allocate buffer" << std::endl;
    return NULL;
  }
}

size_t Image2dData::getBufferSize()
{
  if (buffer != NULL)
  {
    return bufferSize;
  }
  else
  {
    std::cout << "No size available" << std::endl;
    return 0;
  }
}

Image2dData::  ~Image2dData()
{
  delete []buffer;
}
