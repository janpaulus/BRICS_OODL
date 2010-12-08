#include "ImageFormat.hpp"
#include "MonocularCameraDefinitions.hpp"


ImageFormat::ImageFormat(): deviceHandle(NULL),
    currentResolution(NULL),
    currentFormat(NULL),
    formatDevice(NULL),
    returnStatus(STATUS_FAILURE),
    numberOfResolutions(0),
    deviceFormatCounter(0),
    formatIdentifier(""),
    bitsPerPixel(8),
    fourcc(0), bufferSize(0),
    currentBufferType(UNICAP_BUFFER_TYPE_USER)

{

    std::cout  << "Creating ImageFormat without args"<< std::endl;

}


ImageFormat::ImageFormat(std::string &formatID):currentResolution(NULL),
    currentFormat(NULL),
    deviceHandle(NULL),
    formatDevice(NULL),
    returnStatus(STATUS_FAILURE),
    numberOfResolutions(0),
    deviceFormatCounter(0),
    bitsPerPixel(8),
    fourcc(0),
    bufferSize(0),
    currentBufferType(UNICAP_BUFFER_TYPE_USER)

{

    std::cout  << "Creating ImageFormat with formatID string argument"<< std::endl;

}


ImageFormat::ImageFormat(unicap_device_t* device, unicap_handle_t *handle, std::string formatIdentifier = "RGB"): currentResolution(NULL),
    currentFormat(NULL),
    returnStatus(STATUS_FAILURE),
    numberOfResolutions(0), deviceFormatCounter(0),
    bitsPerPixel(8), fourcc(0), bufferSize(0),
    currentBufferType(UNICAP_BUFFER_TYPE_USER),
    deviceHandle(handle), formatDevice(device)
{

    std::cout  << "Creating ImageFormat with all argument"<< std::endl;

}


ImageFormat::ImageFormat(ImageFormat &format)
{

    std::cout  << "Inside ImageFormat copy constructor"<< std::endl;

}


ImageFormat& ImageFormat::operator=(ImageFormat &format)
{
    std::cout  << "Inside ImageFormat assignment operator"<< std::endl;

    if(this !=&format)
    {
        std::cout << "Inside Format assignment operator" << std::endl;
        currentResolution = format.currentResolution;
        numberOfResolutions = format.numberOfResolutions;
        deviceFormatCounter = format.deviceFormatCounter;
        currentFormat = format.currentFormat;
        formatIdentifier = format.formatIdentifier;
        fourcc = format.fourcc;
        bitsPerPixel = format.bitsPerPixel;
        flags = format.flags;
        bufferTypes = format.bufferTypes;
        currentBufferType = format.currentBufferType;
        bufferSize = format.bufferSize;
        returnStatus = format.returnStatus;
        deviceHandle = format.deviceHandle;
        formatDevice = format.formatDevice;
        //copy vector contents later
    }
    return *this;
}



ImageFormat:: ~ImageFormat()
{
    std::cout  << "Destroying ImageFormat"<< std::endl;

}



bool ImageFormat::getImageFormatStringName(std::string &formatName)
{
    if(SUCCESS(this->returnStatus)) //if getListOfFormats called don't call
    {
        formatName = currentFormat->identifier;
        return true;
    }
    else if (getListOfFormats())
    {
        formatName = currentFormat->identifier;
        return true;
    }
    else
    {
        std::cout << "Could not list formats" << std::endl;
        return false;
    }
}


bool ImageFormat::getImageFormatFOURCC(unsigned int &fourcc)
{

    if(SUCCESS(this->returnStatus)) //if getListOfFormats called don't call
    {
        fourcc = currentFormat->fourcc;
        return true;
    }
    else if (getListOfFormats())
    {
        fourcc = currentFormat->fourcc;
        return true;
    }
    else
    {
        std::cout << "Could not list formats" << std::endl;
        return false;
    }

}


bool ImageFormat::getImageFormatResolution(int &width, int &height)
{
    //if getListOfFormats called don't call
    if(SUCCESS(this->returnStatus))
    {
        width = currentResolution->width;
        height = currentResolution->height;
        return true;
    }
    else if (getListOfFormats())
    {
        width = currentResolution->width;
        height = currentResolution->height;
        return true;
    }
    else
    {
        std::cout << "Could not list formats" << std::endl;
        return false;
    }

}


bool ImageFormat::getImageFormatColorModel(std::string &colorModel)
{
    if(getImageFormatStringName(colorModel))
        return true;
    else
        return false;
}



bool ImageFormat::getImageFormatResolutionList()
{
    for(int i=0; i<currentFormat->size_count; i++)
    {
        std::cout << currentFormat->sizes[i].width<< "x" << currentFormat->sizes[i].height <<std::endl;
    }
    return true;
}

bool ImageFormat::getImageFormatColorModelList()
{

    return true;
}


bool ImageFormat::getImageFormatSize(int &size)
{
    if (currentFormat != NULL)
    {
        size = currentFormat->buffer_size;
        return true;
    }
    else
    {
        std::cout << "Size is not available, please check whether format set properly"<< std::endl;
        return false;
    }
}

//should this be a color model or space. Basically here we want to set whether the capture
//should use rgb, yuv, mono... thus setting a color depth and other relevant information
bool ImageFormat::setImageFormatColorModel(std::string &colorModel)
{

    return true;
}


bool ImageFormat::setImageFormatResolution(int &width, int &height)
{

    return true;
}

// the problem is that image format is sth device dependent, whether camera sensor supports some format
// but at the same time it is property of an image.
// image is an entity of its own but at the same time it can't exist without a device which generates it.
// Actually, it underlies the focus of this API, that is, it is only to work with cameras and not with standalone pictures.


//should create a format object and pass it handle
//also pass it the formats obtained
bool ImageFormat::getListOfFormats()
{
    std::cout << "Inside Monocular Camera getListOfFormats"<<std::endl;
    unicap_format_t tempFormat = {0};
    if(deviceHandle != NULL)
    {
        std::cout << "Device is open getting available formats" << std::endl;
        while(SUCCESS(unicap_enumerate_formats(*deviceHandle, NULL, &tempFormat, deviceFormatCounter)))
        {

            listOfDeviceFormats.push_back(tempFormat);
            std::cout << listOfDeviceFormats[deviceFormatCounter].identifier << std::endl;
            std::cout << "Number of supported resolutions by the format"<<listOfDeviceFormats[deviceFormatCounter].size_count << std::endl;
            deviceFormatCounter++;

        }
    }
    // if there are formats available set 1st in the list as default
    if(listOfDeviceFormats.size() != 0)
    {
        //set the default format to the first format in the list;
        //unicap does not set all the values (resolutions, buffersize etc) even if the format is set
        //so this needs to be done manually, at least for the buffersize, or else segfaults will happen
        currentFormat = &listOfDeviceFormats[0];
        //set default resolution to default resolution supported by the chosen format
        //some older cameras do not have default size or it is 0
        if (((listOfDeviceFormats[0].size).width != 0) || ((listOfDeviceFormats[0].size).height != 0))
        {
            currentResolution = &listOfDeviceFormats[0].size;
        }
        else
        {
            currentResolution->width = defaultResolutionWidth; // set default width
            currentResolution->height = defaultResolutionHeight; // set default height
        }

        if (currentFormat->bpp != 0 )
        {
            //calculate buffer size for the given format
            currentFormat->buffer_size = (currentResolution->width*currentResolution->height)*(currentFormat->bpp)/defaultByteLength;
        }
        else
        {
            currentFormat->bpp = defaultColorDepth; //set color depth to 16
            currentFormat->buffer_size = (currentResolution->width*currentResolution->height)*(currentFormat->bpp)/defaultByteLength;
        }

        // set buffertype (can be system or user level memory buffer), at construction time it is set to user level
        currentFormat->buffer_type = this->currentBufferType;

        int returnValue = unicap_set_format(*deviceHandle, currentFormat);
        std::cout << "Setting default format to " << currentFormat->identifier << std::endl;
        std::cout << "Setting default resolution to " << currentResolution->width << "x" <<currentResolution->height<< std::endl;
        std::cout << "Setting default color depth " << currentFormat->bpp << std::endl;
        if (SUCCESS(returnValue))
        {
            this->returnStatus = STATUS_SUCCESS;
            std::cout << "Format successfullye set" << std::endl;
            return true;
        }
    }
    else
    {
        std::cout << "Could not enumerate formats" << std::endl;
        std::cout << "Format set failed" << std::endl;
        return false;
    }
}

