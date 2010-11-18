#include "Image2dData.hpp"


Image2dData::Image2dData(unsigned char *bufferStart = NULL, size_t length = 0)
{
  buffer = bufferStart;
  bufferSize = length; 
}

Image2dData::Image2dData(int& width, int& height)
{
  bufferSize = width * height;
  buffer = new unsigned char[bufferSize];

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
