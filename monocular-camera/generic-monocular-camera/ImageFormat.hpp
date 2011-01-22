#ifndef _IMAGEFORMAT_HPP_
#define _IMAGEFORMAT_HPP_

#include <string>
#include <iostream>
#include <unicap.h>
#include <vector>

//! This class is responsible for setting and getting information for image format.

//! Format contains information on image resolution, color model (RGB, BGR, YUVCr),
//! fourcc id, list of camera supported formats (codecs, e.g. YUV, MJPEG).
class ImageFormat
{

public:
    //! Default constructor
    ImageFormat();
    //! When passed format identifier, it will instantiate an image format
    //! with correct properties obtained from format identifier and bind it to the first
    //! camera identified by OS (dev/video0 or dev/raw13940).
    //! The default image resolution will be set to minimum resoltion supported by the camera
    //! E.g. for format Monochrom, bpp value might be set to 8 bits/px and resoltuion 160x120.
    /*!
     * \param formatID is a string representation of the desired image format. It can be YUV, RGB, YUYV etc
     */
    ImageFormat(std::string &formatID);
    //! Instantiate a format object bound to a camera with the specified handle and set
    //! properties of obtained from the format indentifier
    /*!
     * \param device is a structure which describes a camera (name, path to device node, plugin type etc)
     * \param handle is a handle to the given camera device
     * \param formatIdentifier is a string representation of the desired image format. It can be YUV, RGB, YUYV etc
     */
    ImageFormat(unicap_device_t* device, unicap_handle_t *handle, std::string formatIdentifier);
    //! Copy constructor
    ImageFormat(ImageFormat &format);
    //! Assignment operator
    ImageFormat& operator=(ImageFormat &format);
    //! Class destructor
    ~ImageFormat();
    //! Returns string value for current image format identigier (e.g. JPEG, MJPEG, YUYV )
    /*!
     * \param formatName is a string representation of the desired image format. It can be YUV, RGB, YUYV etc
     */
    bool getImageFormatStringName(std::string &formatName);
    //! Returns FOURCC value for current image format
    /*!
     * \param fourcc is four character code
     */
    bool getImageFormatFOURCC(unsigned int &fourcc);
    //! Returns image resolution for current image format
    /*!
     * \param width is an image width for the current resolution supported by the current format
     * \param height is an image height for the current resolution supported by the current format
     */
    bool getImageFormatResolution(int &width, int &height);
    //! Returns color model used by the format (e.g. MJPEG might be using RGB model)
    bool getImageFormatColorModel(std::string &colorModel);
    //! Returns list of the resolutions supported by the camera
    bool getImageFormatResolutionList();
    //! Returns color model list supported by the camera
    bool getImageFormatColorModelList();
    //! Returns buffer size in bytes for the current format and resolution
    /*!
     * \param size is the amount of memory allocated for the current format and resolution
     */
    bool getImageFormatSize(int &size);
    //! Sets the image resolution
    /*!
     * \param width is a wanted image width for the resolution
     * \param height is a wanted image height for the resolution
     */
    bool setImageFormatResolution(int &width, int &height);

    bool setImageFormatColorModel(std::string &colorModel);

private:
    //!Returns the list of the available formats for the given camera in a vector
    bool getListOfFormats();

    //!chosen or current device image resolution
    unicap_rect_t *currentResolution;

    /*!Number of possible image resolutions supported by the device;
     *this number and number of elements in listOfResolutions should be equal;
     *currently the latter is set statically and will be changed in the future.
     */
    int numberOfResolutions;

    //!Array of possible sizes/resolutions supported by a camera;
    std::vector<unicap_rect_t> listOfResolutions;


    int deviceFormatCounter;
    std::vector<unicap_format_t> listOfDeviceFormats;
    unicap_format_t *currentFormat;


    //!Format identifier is string describing color model/codec model, e.g. RGB, YUV, MJPEG etc
    std::string formatIdentifier;
    //!Fourcc(hex) representation of formatIdentifier
    unsigned int fourcc;
    int bitsPerPixel;
    //!Defines what portion of bits is significant in pixel data
    unicap_format_flags_t flags;

    //!Available/supported buffer types for the given device
    unsigned int bufferTypes;

    //!Current/chosen memory buffer to which image is read/write
    //!There are two types user and system buffers
    unicap_buffer_type_t currentBufferType;
    //!Amount of memory in bytes required by the chosen resolution and color model
    //!widthxheightx(bpp/8.0)
    size_t bufferSize;
    unicap_status_t  returnStatus;
    unicap_handle_t *deviceHandle;
    unicap_device_t *formatDevice;

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

#endif //~ _IMAGEFORMAT_HPP_
