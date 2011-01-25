#ifndef BRICS_OODL_FOURSWEDISHWHEELOMNIBASEKINEMATIC_H
#define BRICS_OODL_FOURSWEDISHWHEELOMNIBASEKINEMATIC_H


#include <vector>
#include <string>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Exceptions.hpp"
#include "base-kinematic/WheeledBaseKinematic.hpp" 
#include "base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.hpp"
namespace brics_oodl {

class FourSwedishWheelOmniBaseKinematic : public WheeledBaseKinematic {
  public:
    FourSwedishWheelOmniBaseKinematic();

    virtual ~FourSwedishWheelOmniBaseKinematic();

    virtual void cartesianVelocityToWheelVelocities(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity, std::vector<quantity<angular_velocity> >& wheelVelocities);

    virtual void wheelVelocitiesToCartesianVelocity(const std::vector<quantity<angular_velocity> >& wheelVelocities, quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<angular_velocity>& angularVelocity);

    virtual void wheelPositionsToCartesianPosition(const std::vector<quantity<plane_angle> >& wheelPositions, quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation);

    void setConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration& configuration);

    void getConfiguration(FourSwedishWheelOmniBaseKinematicConfiguration& configuration) const;


  private:
    FourSwedishWheelOmniBaseKinematicConfiguration config;

    std::vector<quantity<plane_angle> > lastWheelPositions;

    bool lastWheelPositionInitialized;

    quantity<si::length> longitudinalPos;

    quantity<si::length> transversalPos;

    quantity<plane_angle> angle;

};

} // namespace brics_oodl
#endif
