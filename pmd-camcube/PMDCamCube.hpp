#ifndef BRICS_OODL_PMDCAMCUBE_H
#define BRICS_OODL_PMDCAMCUBE_H


#include "generic/Errors.hpp"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic-tof-camera/ToFCamera.hpp"
#include "generic-tof-camera/ToFCameraConfiguration.hpp"
#include "generic-tof-camera/ToFCameraData.hpp"
namespace brics_oodl { class Errors; } 
namespace brics_oodl { class ToFCameraConfiguration; } 
namespace brics_oodl { class ToFCameraData; } 

namespace brics_oodl {

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

} // namespace brics_oodl
#endif
