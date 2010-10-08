#ifndef _MONOCULARCAMERACONFIGURATION_H_
#define _MONOCULARCAMERACONFIGURATION_H_

#define cplusplus

#include <unicap.h>
#include <unicap_status.h>
#include <string>
#include <vector>


class MonocularCameraConfiguration 
{
  public:
    MonocularCameraConfiguration();
    ~MonocularCameraConfiguration();
 
    bool getDeviceName(std::string &deviceId);
    bool getDeviceNodeID(std::string &deviceNodeId);
    bool getDevicePluginType(std::string &pluginName);
    bool getDeviceFullInfoVector();

  private:
    unicap_property_t *deviceConfig;
    unicap_device_t *device;
    int returnStatus;
    std::string deviceID;
    std::string deviceNodeID;
    std::string devicePluginType;
    std::vector<std::string> deviceFullInfo;

};



#endif //~_MONOCULARCAMERACONFIGURATION_H_

/*
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


/* Camera Configuration 


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
