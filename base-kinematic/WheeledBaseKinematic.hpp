#ifndef BRICS_OODL_WHEELEDBASEKINEMATIC_H
#define BRICS_OODL_WHEELEDBASEKINEMATIC_H


#include <vector>
#include <string>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
namespace brics_oodl {

class BaseKinematic {
};
class WheeledBaseKinematic : public BaseKinematic {
  public:
    virtual void cartesianVelocityToWheelVelocities(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<angular_velocity>& angularVelocity, std::vector<quantity<angular_velocity> >& wheelVelocities) = 0;

    virtual void WheelVelocitiesToCartesianVelocity(const std::vector<quantity<angular_velocity> >& wheelVelocities, quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<angular_velocity>& angularVelocity) = 0;

};

} // namespace brics_oodl
#endif
