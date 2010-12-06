#ifndef _MONOCULARCAMERACONFIGURATION_H_
#define _MONOCULARCAMERACONFIGURATION_H_



#include "ColorExposureConfiguration.hpp"
#include "CameraDeviceConfiguration.hpp"



class MonocularCameraConfiguration
{
public:
    MonocularCameraConfiguration();
    MonocularCameraConfiguration(unicap_device_t *device, unicap_handle_t *handle);
    MonocularCameraConfiguration( MonocularCameraConfiguration &cameraConfig);
    MonocularCameraConfiguration& operator= ( MonocularCameraConfiguration &cameraConfig);
    ~MonocularCameraConfiguration();

    bool getDeviceName(std::string &deviceId);
    bool getDeviceNodeID(std::string &deviceNodeId);
    bool getDevicePluginType(std::string &pluginName);
    bool setCameraDeviceConfiguration(CameraDeviceConfiguration &cameradevconf);
    bool setColorExposureConfiguration(ColorExposureConfiguration &colorexpconf);
    CameraDeviceConfiguration* getCameraDeviceConfiguration();
    ColorExposureConfiguration* getColorExposureConfiguration();


private:
    unicap_property_t *propertyConfig;
    unicap_device_t *deviceConfig;
    unicap_handle_t *handleConfig;
    unicap_status_t returnStatus;

    std::string deviceID;
    std::string deviceNodeID;
    std::string devicePluginType;
    ColorExposureConfiguration *colExpConfiguration;
    CameraDeviceConfiguration *devConfiguration;
};




#endif //~_MONOCULARCAMERACONFIGURATION_H_


/*

  There are several categories for camera configuration.

  CAT1: Device general info which includes all the information accessible through
  unicap_device_t. Listed below. These configuration info can not be changes and provided by the manufacturer.

  **
  * unicap_device_t:
  * @identifier: unique textual if of a device
  * @model_name: model name of the device
  * @vendor_name: name of the device vendor
  * @model_id: unique model id, ie. serial number
  * @vendor_id: ID of the vendor like USB Vendor ID for example
  * @cpi_layer: name of the plugin used to communicate with the device
  * @device: name of the device file, if any
  * @flags:


  CAT2:  configuration related to device physical properties, such as of lens and video.
  these are

  DeviceConfiguration
  {
  VideoConfiguration
  {
  framerate - range
  gamma value - range
  sharpness - range
  }

  LensConfiguration
  {
  focus - range
  zoom - range
  iris - range
  }

  }

  CAT3: configuration related to how sensor perceives light

  ColorExposureConfiguration
  {
  ColorConfiguration
  {
  hue -range
  chroma - range
  saturation - range
  color temperature - range
  white balance - value list/flag
  {
  u - range
  v - range
  }
  }

  ExposureConfiguration
  {
  brightness - range
  gainControl - range
  shutterTime - range
  exposureTime - range
  }

  }


  * Camera Configuration  in unicap


  * identifier:   unique textual identifier of this properties
  * category:     a category for this property, for example: 'Lens Control' for zoom and focus properties
  * unit:         optional unit, for example: 's' for Exposure
  * denoting the Exposure time in seconds
  * relations:    properties that might their state or value when
  * changing this property
  * relations_count: size of the relations array
  * value:           for UNICAP_PROPERTY_TYPE_RANGE and
  * UNICAP_PROPERTY_TYPE_VALUE_LIST properties: current value
  * menu_item:       for UNICAP_PROPERTY_TYPE_MENU properties: selected menu entry
  * range:           for UNICAP_PROPERTY_TYPE_RANGE properties: valid range for value
  * value_list:      for UNICAP_PROPERTY_TYPE_VALUE_LIST properties: list
  * of valid values
  * menu:            for UNICAP_PROPERTY_TYPE_MENU properties: menu
  * stepping:        for UNICAP_PROPERTY_TYPE_RANGE properties: stepping
  * type:
  * flags: when enumerated, this field contains the
  * flags_mask:
  * property_data:
  * property_data_size:
  *  </programlisting>
  * </informalexample>
  *
  *
  struct unicap_property_t
  {
  char identifier[128]; //mandatory
  char category[128];
  char unit[128]; //

// list of properties identifier which value / behaviour may change if this property changes
char **relations;
int relations_count;

union
{
double value; // default if enumerated
char menu_item[128];
};


union{
unicap_property_range_t range; // if UNICAP_USE_RANGE is asserted
unicap_property_value_list_t value_list; // if UNICAP_USE_VALUE_LIST is asserted
unicap_property_menu_t menu;
};


double stepping;

unicap_property_type_enum_t type;
unicap_property_flags_t flags;        // defaults if enumerated
unicap_property_flags_t flags_mask;	// defines capabilities if enumerated

// optional data
void *property_data;
size_t property_data_size;
};


*/
