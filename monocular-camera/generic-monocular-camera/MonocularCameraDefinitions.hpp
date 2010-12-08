#ifndef _MONOCULARCAMERADEFINITIONS_
#define _MONOCULARCAMERADEFINITIONS_

#include <vector>
#include <string>


//For the time being we will set image format and camera configuration
//statically and not during runtime. This will limit flexibility and functionality
//of the API because different cameras will definetly have very various set and number
//of properties and formats which should be set dynamically.
//One approach could be to set up a small DB (in text file) where all possible
//camera property names could be entered by a user who would have to use some
//diagnostic program to list all the available camera properties and formats.
//But for this version we stick to enumerations.

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




// TODO (azamat#1#): Add an enumeration for all possible formats and  whenever there is
//a new camera pluged it will check against this enumeration. The number of possible formats (RGB, YUV )
//is limited anyways. So it should not as problematic as in case of camera attributes.

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


const int defaultResolutionWidth = 640;
const int defaultResolutionHeight = 480;
const int defaultColorDepth = 16;
const int defaultByteLength = 8;
#endif //~ _MONOCULARCAMERADEFINITIONS_

