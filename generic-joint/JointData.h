#ifndef _JOINTDATA_H
#define _JOINTDATA_H


#include "generic/Units.h"
class JointData {
};
class JointSensorData : public JointData {
};
class JointSensorAngle : public JointSensorData {
  public:
    quantity<plane_angle> angle;

};
class JointSensorVelocity : public JointSensorData {
  public:
    quantity<angular_velocity> angularVelocity;

};
class JointSensorCurrent : public JointSensorData {
  private:
    quantity<current> current;

};
class JointSensorTorque : public JointSensorData {
  public:
    quantity<torque> torque;

};
class JointSensorTemperature : public JointSensorData {
  public:
    quantity<temperature> temperature;

};
class JointSetpointData : public JointData {
};
class JointSetpointAngle : public JointSetpointData {
  public:
    quantity<plane_angle> angle;

};
class JointSetpointVelocity : public JointSetpointData {
  public:
    quantity<angular_velocity> angularVelocity;

};
class JointSetpointCurrent : public JointSetpointData {
  private:
    quantity<current> current;

};
class JointSetpointTorque : public JointSetpointData {
  public:
    quantity<torque> torque;

};
#endif
