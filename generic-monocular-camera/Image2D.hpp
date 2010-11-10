#include "Image2dData.hpp"
#include "ImageFormat.hpp"

class Image2D
{
public:
  Image2D();
  ~Image2D();
  bool getImageFormat();
  bool getImageData();
  bool setImageFormat();

private:
  Image2dData pixelData;
  ImageFormat format;


};
