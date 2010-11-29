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
  //!Default constructor
  ColorExposureConfiguration();
  //! Constructor instantiates color exposure configuration object for the camera with id `device' and respective `handle'.
  ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle);
  //!Copy constructor
  ColorExposureConfiguration( ColorExposureConfiguration &colorconfig);
  //!Assignment operator
  ColorExposureConfiguration& operator=( ColorExposureConfiguration &colorconfig);
  //! Class destructor
  ~ColorExposureConfiguration();
  //! Returns hue value setting for the capture
  bool getHueValue(double &hue);
  //! Returns constrast value setting for the capture
  bool getContrastValue(double &conrast);
  //! Returns saturation value setting for the capture
  bool getSaturationValue(double &saturation);
  //! Returns white balance U value setting for the capture
  bool getWhiteBalanceUValue(double &uValue);
  //! Returns white balance V value setting for the capture
  bool getWhiteBalanceVValue(double &vValue);
  //! Returns brightness value setting for the capture
  bool getBrightnessValue(double &brightness);
  //! Returns gain control value (signal amplification value) setting for the capture
  bool getGainControlValue(double &gain);
  //! Returns shutter time value setting for the camera
  bool getShutterTime(double &sTime);
  //! Returns exposure time value setting for the camera
  bool getExposureTime(double &eTime);
  //! Returns color temperature value setting for the camera
  bool getColorTemperatureValue(double &temp);
  //!Sets hue value for the capture
  bool setHueValue(double &hue); 
  //!Sets chroma value for the capture
  bool setChromaValue(double &chroma);
  //!Sets saturation value for the capture
  bool setSaturationValue(double &saturation);
  //!Sets whitebalance U value for the capture
  bool setWhiteBalanceUValue(double &uValue);
  //!Sets whitebalance V value for the capture
  bool setWhiteBalanceVValue(double &vValue);
  //!Sets brightness value for the capture
  bool setBrightnessValue(double &brightness);
  //!Sets gain value for the capture
  bool setGainControlValue(double &gain);
  //!Sets shutter time
  bool setShutterTime(double &sTime);
  //!Sets exposure time
  bool setExposureTime(double &eTime);
  //!Sets color temperature value for the capture
  bool setColorTemperatureValue(double &temp);

private:
  //!Returns list of color and exposure related properties of the sensor

  //! This method is used internally to store all the properties in one call
  //! to the camera, rather then invoking it for each property, which would be expensive.
  bool getListOfColorProperties();
  bool unifyPropertyNames();

  unicap_device_t *deviceColorExposureDev;
  unicap_handle_t *handleColorExposureDev;
  unicap_status_t returnStatus;

  //counter for the total number of color-exposure properties provided by a camera
  //should be equal to vector index of listOfProperties
  int colorConfPropertyCounter;
  std::vector<unicap_property_t> listOfProperties;     

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

};

#endif// ~ _COLOREXPOSURECONFIGURATION_
