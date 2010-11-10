#include <string>
#include <iostream>
#include <unicap.h>


class ImageFormat
{
 public:
  ImageFormat();
  ~ImageFormat();
 private:
  std::string formatIdentifier;
  unicap_rect_t currentResolution;
  

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
