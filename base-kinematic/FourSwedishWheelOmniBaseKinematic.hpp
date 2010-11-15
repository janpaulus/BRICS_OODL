#ifndef BRICS_OODL_FOURSWEDISHWHEELOMNIBASEKINEMATIC_H
#define BRICS_OODL_FOURSWEDISHWHEELOMNIBASEKINEMATIC_H


#include <vector>
#include <string>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "base-kinematic/WheeledBaseKinematic.hpp" 
namespace brics_oodl {

class FourSwedishWheelOmniBaseKinematicConfiguration {
  public:
    FourSwedishWheelOmniBaseKinematicConfiguration();

    ~FourSwedishWheelOmniBaseKinematicConfiguration();

    FourSwedishWheelOmniBaseKinematicConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration & source);

    FourSwedishWheelOmniBaseKinematicConfiguration & operator=(const FourSwedishWheelOmniBaseKinematicConfiguration & source);

    quantity<si::length> wheelRadius;

    quantity<si::length> lengthBetweenFrontWheels;

    quantity<si::length> lengthBetweenFrontAndRearWheels;

    //how far sideways in one wheel rotation compared to forward
    double slideRatio;

    double rotationRatio;

};
class FourSwedishWheelOmniBaseKinematic : public WheeledBaseKinematic {
  public:
    virtual void cartesianVelocityToWheelVelocities(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity, std::vector<quantity<angular_velocity> >& wheelVelocities);

    virtual void wheelVelocitiesToCartesianVelocity(const std::vector<quantity<angular_velocity> >& wheelVelocities, quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<angular_velocity>& angularVelocity);

    void setConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration& configuration);

    void getConfiguration(FourSwedishWheelOmniBaseKinematicConfiguration& configuration) const;


  private:
    FourSwedishWheelOmniBaseKinematicConfiguration config;

};

} // namespace brics_oodl
#endif
