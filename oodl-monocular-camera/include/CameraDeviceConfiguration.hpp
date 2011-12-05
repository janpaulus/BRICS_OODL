#ifndef  _CAMERADEVICECONFIGURATION_HPP_
#define _CAMERADEVICECONFIGURATION_HPP_


#include <unicap.h>
#include <unicap_status.h>
#include <string>
#include <vector>
#include <iostream>

namespace brics_oodl {
//! This class represents a set of camera configuration related to camera lens and iris.
class CameraDeviceConfiguration
{
public:
    //!Default constructor
    CameraDeviceConfiguration();
    //! Constructor instantiates object for the camera device configuration with id `device' and respective `handle'.
    CameraDeviceConfiguration(unicap_device_t *device, unicap_handle_t *handle);
    //!Copy constructor
    CameraDeviceConfiguration(CameraDeviceConfiguration& cameradevconf);
    //!Assignment operator
    CameraDeviceConfiguration& operator=(CameraDeviceConfiguration& cameradevconf);

    //!Destructor
    ~CameraDeviceConfiguration();
    //!Returns frame capture rate for the camera
    bool getVideoFrameRate(double &rate);
    //!Returns gamma correction value for the camera
    bool getVideoGammaValue(double &gamma);
    //!Returns sharpness value for the camera
    bool getVideoSharpnessValue(double &sharpness);
    //!Returns focus distance for the camera lens
    bool getLensFocus(double &focus);
    //!Returns zoom ratio value for the camera
    bool getLensZoom(double &zoom);
    //!Returns iris/adjustable diaphragm diameter value for the camera
    bool getLensIris(double &iris);
    //!Sets frame capture rate to `rate'
    bool setVideoFrameRate(double &rate);
    //!Sets gamma correction value to `gamma'
    bool setVideoGammaValue(double &gamma);
    //!Sets sharpness value for the capture to `sharpness'

    //!This value is dependent on sensor capture resolution and acutance(edge contrast)
    bool setVideoSharpnessValue(double &sharpness);
    //!Sets lens focus distance to `focus'
    bool setLensFocus(double &focus);
    //!Sets lens zoom ratio value to `zoom'
    bool setLensZoom(double &zoom);
    //!Sets iris diameter to `iris'
    bool setLensIris(double &iris);


private:
    bool getListOfDeviceProperties();
    bool unifyPropertyNames();
    bool normalizePropertyValues(double &userValue, unicap_property_t propertyToNormalize);

    //counter for the total number of device-lens properties provided by a camera
    //should be equal to array index of listOfProperties, which is currently staticly set

    unicap_device_t *deviceCameraDevConf;
    unicap_handle_t *handleCameraDevConf;
    unicap_status_t returnStatus;
    int deviceConfPropertyCounter;
    std::vector<unicap_property_t> listOfProperties;

//current/actual property values
    unicap_property_range_t videoFrameRate;
    unicap_property_range_t videoGammaValue;
    unicap_property_range_t videoSharpnessValue;
    unicap_property_range_t lensFocus;
    unicap_property_range_t lensZoom;
    unicap_property_range_t lensIris;
};


}  //~namespace brics_oodl
#endif //~_CAMERADEVICECONFIGURATION_HPP_
