#include "Image2dData.hpp"



Image2dData::Image2dData():bufferSize(0), buffer(NULL)
{

}

Image2dData::Image2dData(int& width, int& height)
{
  bufferSize = width * height;
  buffer = new unsigned char[bufferSize];

}

unsigned char* Image2dData::getBuffer()
{

  return buffer;
}

long int Image2dData::getBufferSize()
{

  return bufferSize;
}

Image2dData::  ~Image2dData()
{
  delete []buffer;
}
