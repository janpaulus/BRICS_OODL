#ifndef  _COLOREXPOSURECONFIGURATION_
#define  _COLOREXPOSURECONFIGURATION_

#include <unicap.h>
#include <unicap_status.h>
#include <string>
#include <vector>
#include <iostream>


//! This class represents a set of camera properties related to color and exposure
class ColorExposureConfiguration
{
public:
  ColorExposureConfiguration();
  ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle);
  ColorExposureConfiguration( ColorExposureConfiguration &colorconfig);
  ColorExposureConfiguration& operator=( ColorExposureConfiguration &colorconfig);
  ~ColorExposureConfiguration();
  
  bool getHueValue(double &hue); 
  bool getContrastValue(double &conrast);
  bool getSaturationValue(double &saturation);
  bool getWhiteBalanceUValue(double &uValue);
  bool getWhiteBalanceVValue(double &vValue);
  bool getBrightnessValue(double &brightness);
  bool getGainControlValue(double &gain);
  bool getShutterTime(double &sTime);
  bool getExposureTime(double &eTime);
  bool getColorTemperatureValue(double &temp);

  bool setHueValue(double &hue); 
  bool setChromaValue(double &chroma);
  bool setSaturationValue(double &saturation);
  bool setWhiteBalanceUValue(double &uValue);
  bool setWhiteBalanceVValue(double &vValue);
  bool setBrightnessValue(double &brightness);
  bool setGainControlValue(double &gain);
  bool setShutterTime(double &sTime);
  bool setExposureTime(double &eTime);
  bool setColorTemperatureValue(double &temp);

private:
  bool getListOfColorProperties();
  bool unifyPropertyNames();

  //counter for the total number of color-exposure properties provided by a camera
  //should be equal to array index of listOfProperties, which is currently staticly set
  int colorConfPropertyCounter;
  //array of properties; will be changed later to dynamic vector type
  unicap_property_t listOfProperties[30];
     
  //current/actual property values
  unicap_property_range_t hueValue; 
  unicap_property_range_t chromaValue;
  unicap_property_range_t saturationValue;
  unicap_property_range_t colorTemperatureValue;
  unicap_property_range_t whiteBalanceUValue;
  unicap_property_range_t whiteBalanceVValue;
  unicap_property_range_t brightnessValue;
  unicap_property_range_t gainControlValue;
  unicap_property_range_t shutterTime;
  unicap_property_range_t exposureTime;
  unicap_status_t returnStatus;
  unicap_device_t *deviceColorExposureDev;
  unicap_handle_t *handleColorExposureDev;
};

#endif// ~ _COLOREXPOSURECONFIGURATION_
