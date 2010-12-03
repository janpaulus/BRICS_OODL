#ifndef  _MONOCULARCAMERA_H_
#define  _MONOCULARCAMERA_H_

//#include "../generic/Errors.hpp"
//#include "../generic/Logger.hpp"
//#include "../generic/Units.hpp"
#include "./generic-monocular-camera/MonocularCameraConfiguration.hpp"
#include "./generic-monocular-camera/Image2dData.hpp"
#include "./generic-monocular-camera/ImageFormat.hpp"
#include <unicap.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

//! This class represents a physical camera attached.
//! It can be instantiated to create camera objects.
class MonocularCamera
{
public:

    //!Class constructor takes device ID as a parameter and instantiates a camera
    MonocularCamera(int deviceNumber);
    //!Class copy constructor
    MonocularCamera(MonocularCamera &camera);
    //!Class constructor takes camera configuration and image format and instantiates a camera
    MonocularCamera(int deviceNumber, MonocularCameraConfiguration &config, std::string &fm);
    //!Assignment operator creates an exact copy during an assignment of object instances
    MonocularCamera& operator= (const MonocularCamera &camera);
    ~MonocularCamera();
    //!Returns camera configuration object which allows access to camera lens and color configurations
    bool getConfiguration (MonocularCameraConfiguration &config);
    //!Sets camera configuration to `config'
    bool setConfiguration (MonocularCameraConfiguration &config);
    //!Returns current image capture format
    bool getImageFormat(ImageFormat &fm);
    //!Set image capture format to particular `format' value
    bool setImageFormat(ImageFormat &fm);
    //!Prepares camera for a capture process
    bool capture();
    //!Opens camera device and prepares for format and properties to be configured
    bool open ();
    //!Stops capture process and closes the device
    bool close ();
    //!Returns captured image in Image2dData data structure
    /*!
     * \param data contains captured image
     * \sa Image2dData()
     */
    void getImageData(Image2dData& data);

private:
//!Checks system for the connected cameras and packs them into a vector
    bool getListOfCameras();
    MonocularCameraConfiguration *cameraConfig;
    ImageFormat *format;
    Image2dData *pixels;
    unicap_device_t *currentDevice;
    unicap_handle_t *deviceHandle;
    unicap_status_t isConnected;
    unicap_status_t isOpened;
    int cameraDeviceCounter;
    std::vector<unicap_device_t> listOfCameraDevices;
};


#endif //~_MONOCULARCAMERA_H_
