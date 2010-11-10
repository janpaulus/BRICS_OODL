#ifndef BRICS_OODL_MESASWISSRANGER_H
#define BRICS_OODL_MESASWISSRANGER_H


#include "generic/Errors.hpp"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic-tof-camera/ToFCamera.hpp"
#include "generic-tof-camera/ToFCameraConfiguration.hpp"
#include "generic-tof-camera/ToFCameraData.hpp"
#include "libMesaSR.h"
#include "definesSR.h"
namespace brics_oodl { class Errors; } 
namespace brics_oodl { class ToFCameraData; } 

namespace brics_oodl {

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

} // namespace brics_oodl
#endif
