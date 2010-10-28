#ifndef  _CAMERADEVICECONFIGURATION_
#define _CAMERADEVICECONFIGURATION_


#include <unicap.h>
#include <unicap_status.h>
#include <string>
#include <vector>
#include <iostream>



class CameraDeviceConfiguration
{
public:
    CameraDeviceConfiguration();
    CameraDeviceConfiguration(unicap_device_t *device, unicap_handle_t *handle);
    CameraDeviceConfiguration(CameraDeviceConfiguration& cameradevconf);
    CameraDeviceConfiguration& operator=(CameraDeviceConfiguration& cameradevconf); 


    ~CameraDeviceConfiguration();  
 
    bool getVideoFrameRate(double &rate);
    bool getVideoGammaValue(double &gamma); 
    bool getVideoSharpnessValue(double &sharpness);
    bool getLensFocus(double &focus);
    bool getLensZoom(double &zoom); 
    bool getLensIris(double &iris); 

    bool setVideoFrameRate(double &rate);
    bool setVideoGammaValue(double &gamma); 
    bool setVideoSharpnessValue(double &sharpness);
    bool setLensFocus(double &focus);
    bool setLensZoom(double &zoom); 
    bool setLensIris(double &iris); 

 
private:
    bool getListOfDeviceProperties();
 
    unicap_property_range_t videoFrameRate; 
    unicap_property_range_t videoGammaValue; 
    unicap_property_range_t videoSharpnessValue;
    unicap_property_range_t lensFocus;
    unicap_property_range_t lensZoom; 
    unicap_property_range_t lensIris; 
    unicap_status_t returnStatus;
    unicap_property_t listOfProperties[30];//array of properties
    unicap_device_t *deviceCameraDevConf;
    unicap_handle_t *handleCameraDevConf;
    int deviceConfPropertyCounter;
};

#endif //~_CAMERADEVICECONFIGURATION_
