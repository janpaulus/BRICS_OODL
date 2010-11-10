#ifndef _TOFCAMERA_H
#define _TOFCAMERA_H


#include "generic/Errors.hpp"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic-tof-camera/ToFCamera.hpp"
#include "generic-tof-camera/ToFCameraConfiguration.hpp"
#include "generic-tof-camera/ToFCameraData.hpp"
class Errors;
class ToFCameraConfiguration;
class ToFCameraData;

/**
 * \brief 
 *
 */
class ToFCamera {
  public:
    ToFCamera();

    virtual ~ToFCamera();

    /// @brief Close the connection to the laser scanner.
    virtual bool close(Errors& error) = 0;

    /**
     * 
     */
    virtual bool setConfiguration(const ToFCameraConfiguration& configuration, Errors& error) = 0;

    virtual bool getConfiguration(ToFCameraConfiguration& configuration, Errors& error) = 0;

    virtual bool getData(ToFCameraData& data, Errors& error) = 0;

    virtual bool resetDevice(Errors& error) = 0;

};
#endif
