
#include "base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp"
namespace brics_oodl {

FourSwedishWheelOmniBaseKinematicConfiguration::FourSwedishWheelOmniBaseKinematicConfiguration() {
  // Bouml preserved body begin 0004C271
  this->RotationRatio = 1;
  this->SlideRatio = 1;
  // Bouml preserved body end 0004C271
}

FourSwedishWheelOmniBaseKinematicConfiguration::~FourSwedishWheelOmniBaseKinematicConfiguration() {
  // Bouml preserved body begin 0004C2F1
  // Bouml preserved body end 0004C2F1
}

FourSwedishWheelOmniBaseKinematicConfiguration::FourSwedishWheelOmniBaseKinematicConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration & source) {
  // Bouml preserved body begin 0004C371
  this->RotationRatio = source.RotationRatio;
  this->SlideRatio = source.SlideRatio;
  this->lengthBetweenFrontAndRearWheels = source.lengthBetweenFrontAndRearWheels;
  this->lengthBetweenFrontWheels = source.lengthBetweenFrontWheels;
  this->wheelRadius = source.wheelRadius;
  // Bouml preserved body end 0004C371
}

FourSwedishWheelOmniBaseKinematicConfiguration & FourSwedishWheelOmniBaseKinematicConfiguration::operator=(const FourSwedishWheelOmniBaseKinematicConfiguration & source) {
  // Bouml preserved body begin 0004C3F1
  this->RotationRatio = source.RotationRatio;
  this->SlideRatio = source.SlideRatio;
  this->lengthBetweenFrontAndRearWheels = source.lengthBetweenFrontAndRearWheels;
  this->lengthBetweenFrontWheels = source.lengthBetweenFrontWheels;
  this->wheelRadius = source.wheelRadius;
  // Bouml preserved body end 0004C3F1
}

void FourSwedishWheelOmniBaseKinematic::cartesianVelocityToWheelVelocities(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity, std::vector<quantity<angular_velocity> >& wheelVelocities) {
  // Bouml preserved body begin 0004C071
    // Requred wheen rotation for X and Y component
    /*
      int YouBotOmniBaseDriver::SetVelocity(float aX_vel, float aY_vel, float aTheta_vel)
  {
      std::cout << "SetVelocity" << std::endl;

      // Requred wheen rotation for X and Y component
      float RadPerSec_FromX = aX_vel / (cWheelDiam / 2);
      float RadPerSec_FromY = aY_vel / (cWheelDiam * cSlideRatio / 2);

      // Calculate Rotation Component
      float Omkreds = sqrt(cWheelDist * cWheelDist + cAxisWidth * cAxisWidth) * cPI;
      float RequestedMovement = Omkreds * (aTheta_vel / (2 * cPI));
      float OneWheelRotation = cRotationRatio * cWheelDiam * cPI;
      float RadPerSec_FromTheta = 2 * cPI * (RequestedMovement / OneWheelRotation);
     *
     * float RadPerSec_FromTheta = 2 * cPI * (Omkreds * (aTheta_vel / (2 * cPI)) / (cRotationRatio * cWheelDiam * cPI));

      // Calcuate required rad/sec for each X/Y component
      float M1 = -RadPerSec_FromX + RadPerSec_FromY + RadPerSec_FromTheta;
      float M2 =  RadPerSec_FromX + RadPerSec_FromY + RadPerSec_FromTheta;
      float M3 = -RadPerSec_FromX - RadPerSec_FromY + RadPerSec_FromTheta;
      float M4 =  RadPerSec_FromX - RadPerSec_FromY + RadPerSec_FromTheta;

      return mMotorDriver.SetSpeed(M1, M2, M3, M4);
     * */
    quantity<angular_velocity> RadPerSec_FromX;
    quantity<angular_velocity> RadPerSec_FromY;
    quantity<angular_velocity> RadPerSec_FromTheta;
    quantity<si::length> Perimeter;
    quantity<si::length> OneWheelRotation;
    wheelVelocities.reserve(4);

    if(config.wheelRadius.value() == 0||config.RotationRatio == 0|| config.SlideRatio == 0){
      throw ExceptionOODL("The wheelRadius, RotationRatio and the SlideRatio are not allowed to be zero");
    }
    

   // RadPerSec_FromX = longitudinalVelocity / config.wheelRadius;
    RadPerSec_FromX = longitudinalVelocity.value() / config.wheelRadius.value() * radian_per_second;
    RadPerSec_FromY = transversalVelocity.value() / (config.wheelRadius.value() * config.SlideRatio) * radian_per_second;

    // Calculate Rotation Component
    Perimeter = (root < 2 > ((config.lengthBetweenFrontAndRearWheels * config.lengthBetweenFrontAndRearWheels) + (config.lengthBetweenFrontWheels * config.lengthBetweenFrontWheels))) * M_PI;
    OneWheelRotation = config.RotationRatio * config.wheelRadius * 2.0 * M_PI;
    RadPerSec_FromTheta = angularVelocity * (Perimeter / OneWheelRotation);


    wheelVelocities[0] = -RadPerSec_FromX + RadPerSec_FromY + RadPerSec_FromTheta;
    wheelVelocities[1] = RadPerSec_FromX + RadPerSec_FromY + RadPerSec_FromTheta;
    wheelVelocities[2] = -RadPerSec_FromX - RadPerSec_FromY + RadPerSec_FromTheta;
    wheelVelocities[3] = RadPerSec_FromX - RadPerSec_FromY + RadPerSec_FromTheta;


    return;

  // Bouml preserved body end 0004C071
}

void FourSwedishWheelOmniBaseKinematic::WheelVelocitiesToCartesianVelocity(const std::vector<quantity<angular_velocity> >& wheelVelocities, quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 0004C0F1
  // Bouml preserved body end 0004C0F1
}

void FourSwedishWheelOmniBaseKinematic::setConfiguration(const FourSwedishWheelOmniBaseKinematicConfiguration& configuration) {
  // Bouml preserved body begin 0004C171
    this->config = configuration;
  // Bouml preserved body end 0004C171
}

FourSwedishWheelOmniBaseKinematicConfiguration FourSwedishWheelOmniBaseKinematic::getConfiguration() const {
  // Bouml preserved body begin 0004C1F1
    return this->config;
  // Bouml preserved body end 0004C1F1
}


} // namespace brics_oodl
