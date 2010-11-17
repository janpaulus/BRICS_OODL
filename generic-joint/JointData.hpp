#ifndef BRICS_OODL_JOINTDATA_H
#define BRICS_OODL_JOINTDATA_H


#include "generic/Units.hpp"

namespace brics_oodl {

class JointData {
};
class JointSensedData : public JointData {
};
class JointSensedAngle : public JointSensedData {
  public:
    quantity<plane_angle> angle;

};
class JointSensedVelocity : public JointSensedData {
  public:
    quantity<si::angular_velocity> angularVelocity;

};
class JointSensedCurrent : public JointSensedData {
  public:
    quantity<si::current> current;

};
class JointSensedTorque : public JointSensedData {
  public:
    quantity<si::torque> torque;

};
class JointSensedTemperature : public JointSensedData {
  public:
    quantity<celsius::temperature> temperature;

};
class JointDataSetpoint : public JointData {
};
class JointAngleSetpoint : public JointDataSetpoint {
  public:
    quantity<plane_angle> angle;

};
class JointVelocitySetpoint : public JointDataSetpoint {
  public:
    quantity<angular_velocity> angularVelocity;

};
class JointCurrentSetpoint : public JointDataSetpoint {
  public:
    quantity<si::current> current;

};
class JointTorqueSetpoint : public JointDataSetpoint {
  public:
    quantity<si::torque> torque;

};
class JointDataRange {
  public:
    JointData jointDataUpper;

    JointData jointDataLower;

};

} // namespace brics_oodl
#endif
