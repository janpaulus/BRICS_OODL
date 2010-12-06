
#ifndef _MONOCULARCAMERADEFINITIONS_
#define _MONOCULARCAMERADEFINITIONS_

#include <vector>
#include <string>

typedef enum IMAGEPIXELFORMATS
{

  RGB8 = 0,
  RGB16,
  RGB24,
  RGB32,
  YUV422_16,
  YUV422_24,
  YUV400_8,
  YUV400_16,
  YUV444_32,

} PixelFormats;



typedef enum COLOREXPOSUREPROPERTYDESCRIPTORS
{
    Hue = 0,
    Chroma,
    Saturation,
    Brightness,
    Contrast,
    Gain,
    Exposure

} ColorPropertyDesc;


typedef enum LENSPROPERTYDESCRIPTORS
{
    FrameRate = 0,
    Focus,
    Sharpness,
    Zoom,
    Iris

} LensPropDesc;

#endif //~ _MONOCULARCAMERADEFINITIONS_
