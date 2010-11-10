#include <iostream>

class Image2dData
{
  public:
  Image2dData();
  ~Image2dData();
 
 private:
  char *buffer;

};


/*


/**
 * unicap_data_buffer_t:
 * @format: a #unicap_format_t describing the layout of the data
 * buffer
 * @frame_number:
 * @fill_time: the time when capturing completed on this buffer
 * @duration: frame duration of this buffer ( might not be present on
 * all devices )
 * @capture_start_time: the time when the capturing started on this
 * buffer ( might not be supported on all devices )
 * @data: the image data
 * @buffer_size: size of the memory buffer pointed to by data
 * @type: 
 * 

struct unicap_data_buffer_t
{
      unicap_format_t format;
      
      int frame_number;
      struct timeval fill_time; //
      struct timeval duration;
      struct timeval capture_start_time;// optional, time of first copy action of image data of this frame
      
      unsigned char *data;
      size_t buffer_size;	

      unicap_buffer_type_t type; // system pointers or user pointers

      unicap_buffer_flags_t flags;
      unsigned int reserved[7];		
};

typedef struct unicap_data_buffer_t unicap_data_buffer_t;



*/
