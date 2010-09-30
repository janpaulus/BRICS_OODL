#ifndef _TOFCAMERACONFIGURATION_H
#define _TOFCAMERACONFIGURATION_H


#include "generic/Logger.h"
#include "generic/Units.h"
/**
 * \brief 
 *
 */
class ToFCameraConfiguration {
  public:
    ToFCameraConfiguration();

    virtual ~ToFCameraConfiguration();

    ToFCameraConfiguration(const ToFCameraConfiguration & source);

    virtual ToFCameraConfiguration & operator=(const ToFCameraConfiguration & source);

    /// Vendor name.
    std::string vendor;

    /// Product name.
    std::string product;

    /// Firmware version.
    std::string firmware;

    std::string protocol;

    std::string serialNumber;

    std::string model;

    std::string devicePath;

    quantity<si::time> integrationTime;

    quantity<si::frequency> modulationFrequency;

    quantity<length> distanceOffset;

};
#endif
