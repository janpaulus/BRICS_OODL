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
  bool unifyPropertyNames();

  //counter for the total number of device-lens properties provided by a camera
  //should be equal to array index of listOfProperties, which is currently staticly set
  int deviceConfPropertyCounter;
  //array of properties; will be changed later to dynamic vector type
  unicap_property_t listOfProperties[30];//array of properties; will later be changed to dynamic vector type

  //current/actual property values
  unicap_property_range_t videoFrameRate; 
  unicap_property_range_t videoGammaValue; 
  unicap_property_range_t videoSharpnessValue;
  unicap_property_range_t lensFocus;
  unicap_property_range_t lensZoom; 
  unicap_property_range_t lensIris; 

  unicap_status_t returnStatus;
  unicap_device_t *deviceCameraDevConf;
  unicap_handle_t *handleCameraDevConf;

};

#endif //~_CAMERADEVICECONFIGURATION_
