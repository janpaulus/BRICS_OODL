
#include "base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp"
namespace brics_oodl {

FourSwedishWheelOmniBaseKinematic::FourSwedishWheelOmniBaseKinematic() {
  // Bouml preserved body begin 000513F1
    this->lastWheelPositionInitialized = false;
  // Bouml preserved body end 000513F1
}

FourSwedishWheelOmniBaseKinematic::~FourSwedishWheelOmniBaseKinematic() {
  // Bouml preserved body begin 00051471
  // Bouml preserved body end 00051471
}

void FourSwedishWheelOmniBaseKinematic::cartesianVelocityToWheelVelocities(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity, std::vector<quantity<angular_velocity> >& wheelVelocities) {
  // Bouml preserved body begin 0004C071
    quantity<angular_velocity> RadPerSec_FromX;
    quantity<angular_velocity> RadPerSec_FromY;
    quantity<angular_velocity> RadPerSec_FromTheta;
    quantity<si::length> Perimeter;
    quantity<si::length> OneWheelRotation;
    wheelVelocities.assign(4, RadPerSec_FromX);

    if (config.wheelRadius.value() == 0 || config.rotationRatio == 0 || config.slideRatio == 0) {
      throw ExceptionOODL("The wheelRadius, RotationRatio and the SlideRatio are not allowed to be zero");
    }


    // RadPerSec_FromX = longitudinalVelocity / config.wheelRadius;
    RadPerSec_FromX = longitudinalVelocity.value() / config.wheelRadius.value() * radian_per_second;
    RadPerSec_FromY = transversalVelocity.value() / (config.wheelRadius.value() * config.slideRatio) * radian_per_second;

    // Calculate Rotation Component
    Perimeter = (root < 2 > ((config.lengthBetweenFrontAndRearWheels * config.lengthBetweenFrontAndRearWheels) + (config.lengthBetweenFrontWheels * config.lengthBetweenFrontWheels))) * M_PI;
    OneWheelRotation = config.rotationRatio * config.wheelRadius * 2.0 * M_PI;
    RadPerSec_FromTheta = angularVelocity * (Perimeter / OneWheelRotation);


    wheelVelocities[0] = -RadPerSec_FromX + RadPerSec_FromY + RadPerSec_FromTheta;
    wheelVelocities[1] = RadPerSec_FromX + RadPerSec_FromY + RadPerSec_FromTheta;
    wheelVelocities[2] = -RadPerSec_FromX - RadPerSec_FromY + RadPerSec_FromTheta;
    wheelVelocities[3] = RadPerSec_FromX - RadPerSec_FromY + RadPerSec_FromTheta;

    return;

  // Bouml preserved body end 0004C071
}

void FourSwedishWheelOmniBaseKinematic::wheelVelocitiesToCartesianVelocity(const std::vector<quantity<angular_velocity> >& wheelVelocities, quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 0004C0F1


    if (wheelVelocities.size() < 4)
      throw ExceptionOODL("To less wheel velocities");

    if (config.lengthBetweenFrontAndRearWheels.value() == 0 || config.lengthBetweenFrontWheels.value() == 0) {
      throw ExceptionOODL("The lengthBetweenFrontAndRearWheels and the lengthBetweenFrontWheels are not allowed to be zero");
    }

    quantity<si::length> wheel_radius_per4 = config.wheelRadius / 4.0;

    quantity<si::length> geom_factor = (config.lengthBetweenFrontAndRearWheels / 2.0) + (config.lengthBetweenFrontWheels / 2.0);
    //now convert this to a vx,vy,vtheta
    longitudinalVelocity = (-wheelVelocities[0] + wheelVelocities[1] - wheelVelocities[2] + wheelVelocities[3]).value() * wheel_radius_per4.value() * meter_per_second;
    transversalVelocity = (wheelVelocities[0] + wheelVelocities[1] + wheelVelocities[2] + wheelVelocities[3]).value() * wheel_radius_per4.value() * meter_per_second;
    angularVelocity = -(wheelVelocities[0] - wheelVelocities[1] - wheelVelocities[2] + wheelVelocities[3]) * (wheel_radius_per4 / geom_factor).value();


    //		timestamp = mappedHead->timestamp;

  // Bouml preserved body end 0004C0F1
}

void FourSwedishWheelOmniBaseKinematic::wheelPositionsToCartesianPosition(const std::vector<quantity<plane_angle> >& wheelPositions, quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation) {
  // Bouml preserved body begin 00051371

    if (wheelPositions.size() < 4)
      throw ExceptionOODL("To less wheel positions");

    if (this->lastWheelPositionInitialized == false) {
      lastWheelPositions = wheelPositions;
      longitudinalPos = 0 * meter;
      transversalPos = 0 * meter;
      angle = 0 * radian;
      this->lastWheelPositionInitialized = true;
    }

    quantity<plane_angle> deltaPositionW1 = (wheelPositions[0] - lastWheelPositions[0]);
    quantity<plane_angle> deltaPositionW2 = (wheelPositions[1] - lastWheelPositions[1]);
    quantity<plane_angle> deltaPositionW3 = (wheelPositions[2] - lastWheelPositions[2]);
    quantity<plane_angle> deltaPositionW4 = (wheelPositions[3] - lastWheelPositions[3]);

    quantity<si::length> xDelta = config.wheelRadius * (deltaPositionW4 - deltaPositionW3).value();
    quantity<si::length> yDelta = config.wheelRadius * (deltaPositionW4 - deltaPositionW2).value();
    quantity<plane_angle> thetaDelta = (deltaPositionW4 + deltaPositionW1) / 2.0;

    longitudinalPos += xDelta * cos(angle) + yDelta * sin(angle);
    transversalPos += xDelta * -sin(angle) + yDelta * cos(angle);
    angle += thetaDelta;

  //  LOG(trace) <<

    longitudinalPosition = longitudinalPos;
    transversalPosition = transversalPos;
    orientation = angle;
  // Bouml preserved body end 00051371
}

void FourSwedishWheelOmniBaseKinematic::setConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration& configuration) {
  // Bouml preserved body begin 0004C171
    this->config = configuration;
  // Bouml preserved body end 0004C171
}

void FourSwedishWheelOmniBaseKinematic::getConfiguration(FourSwedishWheelOmniBaseKinematicConfiguration& configuration) const {
  // Bouml preserved body begin 0004C1F1
    configuration = this->config;
  // Bouml preserved body end 0004C1F1
}


} // namespace brics_oodl
