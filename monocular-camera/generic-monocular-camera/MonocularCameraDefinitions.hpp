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
struct CAMERACOLORPROPERTYNAMES
{

  std::vector<std::string> hue; //= {"hue", "Hue"};
/*
  std::vector<std::string> chroma = {"chroma", "Chroma"};
  std::vector<std::string> contrast = {"contrast", "Constrast"};
  std::vector<std::string> saturation = {"Saturation", "saturation"};
  std::vector<std::string> whitebalance = {"White Balance", "white balance", "whitebalance", "white_balance", "White_Balance", "WhiteBalance"};
*/
};


struct CAMERALENSPROPERTYNAMES
{



};

// TODO (azamat#1#): Add an enumeration for all possible formats and  whenever there is
//a new camera pluged it will check against this enumeration. The number of possible formats (RGB, YUV )
//is limited anyways. So it should not as problematic as in case of camera attributes.
enum IMAGEPIXELFORMATS
{
    RGB16 = 0,
    RGB24,
    RGB32,
    YUV16,
    YUV24,
    YUV32,
    Mono,
    GRGB
};


typedef IMAGEPIXELFORMATS PixelFormats;

#endif //~#define _MONOCULARCAMERADEFINITIONS_

