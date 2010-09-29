#ifndef _PMDCAMCUBE_H
#define _PMDCAMCUBE_H


#include "generic/Errors.h"
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-tof-camera/ToFCamera.h"
#include "generic-tof-camera/ToFCameraConfiguration.h"
#include "generic-tof-camera/ToFCameraData.h"
class Errors;
class ToFCameraConfiguration;
class ToFCameraData;

/**
 * \brief 
 *
 */
class PMDCamCube : public ToFCamera {
  public:
    PMDCamCube();

    virtual ~PMDCamCube();


  private:
    bool open(Errors& error);


  public:
    /// @brief Close the connection to the laser scanner.
    virtual bool close(Errors& error);

    /**
     * 
     */
    virtual bool setConfiguration(const ToFCameraConfiguration& configuration, Errors& error);

    virtual bool getConfiguration(ToFCameraConfiguration& configuration, Errors& error) = 0;

    virtual bool getData(ToFCameraData& data, Errors& error);

    virtual bool resetDevice(Errors& error);


  private:
    logger lg;

    bool isConnected;

};
#endif
