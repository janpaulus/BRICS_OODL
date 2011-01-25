#ifndef BRICS_OODL_WHEELEDBASEKINEMATIC_H
#define BRICS_OODL_WHEELEDBASEKINEMATIC_H


#include <vector>
#include <string>
namespace brics_oodl {

class BaseKinematic {
};
class WheeledBaseKinematic : public BaseKinematic {
  public:
    virtual void cartesianVelocityToWheelVelocities(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<angular_velocity>& angularVelocity, std::vector<quantity<angular_velocity> >& wheelVelocities) = 0;

    virtual void wheelVelocitiesToCartesianVelocity(const std::vector<quantity<angular_velocity> >& wheelVelocities, quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<angular_velocity>& angularVelocity) = 0;

    virtual void wheelPositionsToCartesianPosition(const std::vector<quantity<plane_angle> >& wheelPositions, quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation) = 0;

};

} // namespace brics_oodl
#endif
