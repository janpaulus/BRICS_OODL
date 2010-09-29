#ifndef _MESASWISSRANGER_H
#define _MESASWISSRANGER_H


#include "generic/Errors.h"
#include "generic/Logger.h"
#include "generic/Units.h"
#include "generic-tof-camera/ToFCamera.h"
#include "generic-tof-camera/ToFCameraConfiguration.h"
#include "generic-tof-camera/ToFCameraData.h"
#include "libMesaSR.h"
#include "definesSR.h"
class Errors;
class ToFCameraData;

/**
 * \brief 
 *
 */
class MesaSwissRanger : public ToFCamera {
  public:
    MesaSwissRanger();

    virtual ~MesaSwissRanger();


  private:
    bool open(Errors& error);


  public:
    /// @brief Close the connection to the laser scanner.
    virtual bool close(Errors& error);

    /**
     * 
     */
    virtual bool setConfiguration(const ToFCameraConfiguration& configuration, Errors& error);

    virtual bool getConfiguration(ToFCameraConfiguration& configuration, Errors& error);

    virtual bool getData(ToFCameraData& data, Errors& error);

    virtual bool resetDevice(Errors& error);


  private:
    bool reserveMemory();

    bool freeMemory();

    SRCAM srCam;

    logger lg;

    AcquireMode acquireMode;

    ToFCameraConfiguration config;

    bool isConnected;

};
#endif
