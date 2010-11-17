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
	MonocularCamera(MonocularCameraConfiguration &config, std::string &format);
	//!Assignment operator creates an exact copy during an assignment of object instances
	MonocularCamera& operator= (const MonocularCamera &camera);
	~MonocularCamera();

	bool getConfiguration (MonocularCameraConfiguration &config);
	bool setConfiguration ( MonocularCameraConfiguration &config);
	bool getImageFormat(ImageFormat &format);
	bool setImageFormat(ImageFormat &format);

	bool capture(Image2dData &data); // adding frames here could be good, then a user does not have to bother about building capture loops.
	bool open ();
	bool close ();

private:
	MonocularCameraConfiguration *cameraConfig;
	Image2dData *imagedata;
	ImageFormat *format;
	unicap_device_t *device;
	unicap_handle_t *deviceHandle;
	unicap_status_t isConnected;
};


#endif //~_MONOCULARCAMERA_H_
