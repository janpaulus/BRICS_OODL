#include <string>
#include <iostream>
#include <unicap.h>


class ImageFormat
{

public:

     ImageFormat();
     ImageFormat(std::string formatIdentifier);
     ImageFormat(unicap_handle_t *handle);
     ImageFormat(ImageFormat &format);
     ImageFormat& operator=(ImageFormat &format);
     ~ImageFormat();

     bool getImageFormatStringName(std::string &formatName);
     bool getImageFormatFOURCC(unsigned int &fourcc);
     bool getImageFormatResolution(int &width, int &height);
     bool getImageFormatColorModel(std::string &colorModel);
     
     bool setImageFormatColorModel(std::string &colorModel);
 

private:
     bool getListOfFormats();

     //chosen or current device image resolution
     unicap_rect_t *currentResolution;
     //number of possible image resolutions supported by the device;
     // this number and number of elements in listOfResolutions should be equal;
     //currently the latter is set statically and will be changed in the future.
     int numberOfResolutions;
     // array of possible sizes/resolutions supported by a camera; 
     //currently statically defined; will changed to dynamic array later 
     unicap_rect_t listOfResolutions[40];

     int deviceFormatCounter;
     //currently staticly set to 10, should change to dynamic version.
     unicap_format_t listOfDeviceFormats[10];
     unicap_format_t *currentFormat;
     

     //format identifier is string describing color model/codec model, e.g. RGB, YUV, MJPEG etc
     std::string formatIdentifier;
     // fourcc(hex) representation of formatIdentifier
     unsigned int fourcc;    
     int bitsPerPixel;
     //defines what portion of bits is significant in pixel data
     unicap_format_flags_t flags;

     // available/supported buffer types for the given device
     unsigned int bufferTypes; 
  
     // current/chosen memory buffer to which image is read/write
     // there are two types user and system buffers
     unicap_buffer_type_t currentBufferType;
     // amount of memory in bytes required by the chosen resolution and color model
     // widthxheightx(bpp/8.0)
     size_t bufferSize;
     unicap_status_t  returnStatus;
     unicap_handle_t *deviceHandle;

};



/**
 * unicap_rect_t:
 * @x: 
 * @y: 
 * @width: 
 * @height:
 *
 * A struct defining a rectangle

 struct unicap_rect_t
 {
 int x;
 int y;	
 int width;
 int height;
 };

 typedef struct unicap_rect_t unicap_rect_t;

 **
 * unicap_format_flags_t:
 *
 * Flags used in #unicap_format_t.
 *
 * The first five bits are used to specify the number of significant
 * bits in the pixel data. In order to access the number of sigificant
 * bits, do a bitwise AND operation with
 * @UNICAP_FLAGS_SIGNIFICANT_BITS_MASK. If all bits in the data are
 * significant, the special value @UNICAP_FLAGS_SIGNIFICANT_BITS_ALL
 * can be used.
 *
 * @UNICAP_FLAGS_SIGNIFICANT_BITS_ALL:  all bits are significant
 * @UNICAP_FLAGS_SIGNIFICANT_BITS_MASK: mask to access the number of significant bits
 *
 typedef enum
 {
 UNICAP_FLAGS_SIGNIFICANT_BITS_ALL  = 0,
 UNICAP_FLAGS_SIGNIFICANT_BITS_MASK = 0x1F
 } unicap_format_flags_t;

 **
 * unicap_format_t:
 * @identifier: unique textual identifier of this format
 * @size: size of the format
 * @min_size: minimum size
 * @max_size: maximum size
 * @h_stepping: horizontal stepping
 * @v_stepping: vertical stepping
 * @sizes: array of allowed sizes. Might be NULL
 * @size_count: number of element in the sizes array
 * @bpp: bits per pixel
 * @fourcc: FOURCC describing the colour format
 * @flags: 
 * @buffer_types:
 * @system_buffer_count: 
 * @buffer_size: amount of memory required by one data buffer of this
 * format
 * @buffer_type: 
 * 
 *
 struct unicap_format_t
 {
 char identifier[128];
      
 // default
 unicap_rect_t size; ///size/resolution of the chosen/current format
      
 // min and max extends
 unicap_rect_t min_size;
 unicap_rect_t max_size;
      
 // stepping: 
 // 0 if no free scaling available
 int h_stepping;
 int v_stepping;
 // array of possible sizes/resolutions supported by a camera
 unicap_rect_t *sizes;
 int size_count;
      
 int bpp;
 unsigned int fourcc;
 unicap_format_flags_t flags;

 unsigned int buffer_types; // available buffer types
 int system_buffer_count;

 size_t buffer_size;

 unicap_buffer_type_t buffer_type;
 };

 typedef struct unicap_format_t unicap_format_t;
*/
