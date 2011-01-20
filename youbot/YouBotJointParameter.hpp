#ifndef BRICS_OODL_YOUBOTJOINTPARAMETER_H
#define BRICS_OODL_YOUBOTJOINTPARAMETER_H


#include <vector>
#include <sstream>
#include <boost/limits.hpp>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "rude/config.h"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/JointParameter.hpp"
#include "youbot/YouBotJointParameterReadOnly.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
#include "youbot/YouBotJointStorage.hpp"
namespace brics_oodl {

enum CalibrationDirection {
  POSITIV,
  NEGATIV

};
class YouBotJointParameter : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  protected:
    YouBotJointParameter();


  public:
    virtual ~YouBotJointParameter();


  protected:
    virtual void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const = 0;

    virtual void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) = 0;

    virtual std::string getName() const = 0;

    virtual ParameterType getType() const = 0;

    std::string name;

    ParameterType parameterType;

};
class JointName : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    JointName();

    virtual ~JointName();

    void getParameter(std::string& parameter) const;

    void setParameter(const std::string parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    std::string value;

    std::string name;

    ParameterType parameterType;

};
class GearRatio : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    GearRatio();

    virtual ~GearRatio();

    void getParameter(double& parameter) const;

    void setParameter(const double parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    double value;

    std::string name;

    ParameterType parameterType;

};
class EncoderTicksPerRound : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    EncoderTicksPerRound();

    virtual ~EncoderTicksPerRound();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class InverseMovementDirection : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    InverseMovementDirection();

    virtual ~InverseMovementDirection();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
class CalibrateJoint : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    CalibrateJoint();

    virtual ~CalibrateJoint();

    void getParameter(bool& doCalibration, CalibrationDirection& calibrationDirection, quantity<si::current>& maxCurrent) const;

    void setParameter(const bool doCalibration, CalibrationDirection calibrationDirection, const quantity<si::current>& maxCurrent);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool doCalibration;

    std::string name;

    ParameterType parameterType;

    CalibrationDirection calibrationDirection;

    quantity<si::current> maxCurrent;

};
class JointLimits : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    JointLimits();

    virtual ~JointLimits();

    void getParameter(int& lowerLimit, int& upperLimit) const;

    void setParameter(const int lowerLimit, const int upperLimit);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int lowerLimit;

    int upperLimit;

    std::string name;

    ParameterType parameterType;

};
class StopJoint : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    StopJoint();

    virtual ~StopJoint();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
class NoMoreAction : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    NoMoreAction();

    virtual ~NoMoreAction();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
//The maximum velocity used for move to position command when executing a ramp to a position. In sensorless commutation mode the velocity threshold for hallFXTM.

class MaximumPositioningVelocity : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    MaximumPositioningVelocity();

    virtual ~MaximumPositioningVelocity();

    void getParameter(quantity<angular_velocity>& parameter) const;

    void setParameter(const quantity<angular_velocity>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<angular_velocity> upperLimit;

    quantity<angular_velocity> lowerLimit;

    quantity<angular_velocity> value;

    std::string name;

    ParameterType parameterType;

};
//Set PWM limit (0%... 100%).

class PWMLimit : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PWMLimit();

    virtual ~PWMLimit();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switching threshold for speed control between the first and second set of parameters
class MaximumMotorCurrent : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    MaximumMotorCurrent();

    virtual ~MaximumMotorCurrent();

    void getParameter(quantity<current>& parameter) const;

    void setParameter(const quantity<current>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<current> upperLimit;

    quantity<current> lowerLimit;

    quantity<current> value;

    std::string name;

    ParameterType parameterType;

};
//Maximum velocity at which end position can be set. Prevents issuing of end position when the target is passed at high velocity

class MaximumVelocityToSetPosition : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    MaximumVelocityToSetPosition();

    virtual ~MaximumVelocityToSetPosition();

    void getParameter(quantity<angular_velocity>& parameter) const;

    void setParameter(const quantity<angular_velocity>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<angular_velocity> upperLimit;

    quantity<angular_velocity> lowerLimit;

    quantity<angular_velocity> value;

    std::string name;

    ParameterType parameterType;

};
//Adjusts the limit to switch between first velocity PID parameter set and second velocity PID parameter set.

class SpeedControlSwitchingThreshold : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    SpeedControlSwitchingThreshold();

    virtual ~SpeedControlSwitchingThreshold();

    void getParameter(quantity<angular_velocity>& parameter) const;

    void setParameter(const quantity<angular_velocity>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<angular_velocity> upperLimit;

    quantity<angular_velocity> lowerLimit;

    quantity<angular_velocity> value;

    std::string name;

    ParameterType parameterType;

};
class ClearTargetDistance : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    ClearTargetDistance();

    virtual ~ClearTargetDistance();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
class PositionTargetReachedDistance : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PositionTargetReachedDistance();

    virtual ~PositionTargetReachedDistance();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
//Switching threshold for speed control between the first and second set of parameters
class MotorAcceleration : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    MotorAcceleration();

    virtual ~MotorAcceleration();

    void getParameter(quantity<angular_acceleration>& parameter) const;

    void setParameter(const quantity<angular_acceleration>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<angular_acceleration> upperLimit;

    quantity<angular_acceleration> lowerLimit;

    quantity<angular_acceleration> value;

    std::string name;

    ParameterType parameterType;

};
//Switching threshold for position control between the first and second set of parameters
class PositionControlSwitchingThreshold : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PositionControlSwitchingThreshold();

    virtual ~PositionControlSwitchingThreshold();

    void getParameter(quantity<angular_velocity>& parameter) const;

    void setParameter(const quantity<angular_velocity>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<angular_velocity> upperLimit;

    quantity<angular_velocity> lowerLimit;

    quantity<angular_velocity> value;

    std::string name;

    ParameterType parameterType;

};
class PParameterFirstParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PParameterFirstParametersPositionControl();

    virtual ~PParameterFirstParametersPositionControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
class IParameterFirstParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IParameterFirstParametersPositionControl();

    virtual ~IParameterFirstParametersPositionControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
class DParameterFirstParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    DParameterFirstParametersPositionControl();

    virtual ~DParameterFirstParametersPositionControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
//PID calculation delay: Set operational frequency PID

class PIDControlTime : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PIDControlTime();

    virtual ~PIDControlTime();

    void getParameter(quantity<si::time>& parameter) const;

    void setParameter(const quantity<si::time>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<si::time> upperLimit;

    quantity<si::time> lowerLimit;

    quantity<si::time> value;

    std::string name;

    ParameterType parameterType;

};
//PID calculation delay: Set operational frequency PID

class CurrentControlLoopDelay : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    CurrentControlLoopDelay();

    virtual ~CurrentControlLoopDelay();

    void getParameter(quantity<si::time>& parameter) const;

    void setParameter(const quantity<si::time>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<si::time> upperLimit;

    quantity<si::time> lowerLimit;

    quantity<si::time> value;

    std::string name;

    ParameterType parameterType;

};
//Adjust in standstill to lowest possible value at which the motor keeps its position. A too high value causes overshooting at positioning mode. (first position parameter set)

class IClippingParameterFirstParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IClippingParameterFirstParametersPositionControl();

    virtual ~IClippingParameterFirstParametersPositionControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
//Compensates dead time of PWM and motor friction.

class PWMHysteresis : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PWMHysteresis();

    virtual ~PWMHysteresis();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
//Compensates dead time of PWM and motor friction.

class ClearISumIfPWMReachesMaximum : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    ClearISumIfPWMReachesMaximum();

    virtual ~ClearISumIfPWMReachesMaximum();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
//Compensates dead time of PWM and motor friction.

class ClearISumIfOvershootsTarget : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    ClearISumIfOvershootsTarget();

    virtual ~ClearISumIfOvershootsTarget();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
class PParameterFirstParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PParameterFirstParametersSpeedControl();

    virtual ~PParameterFirstParametersSpeedControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
class IParameterFirstParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IParameterFirstParametersSpeedControl();

    virtual ~IParameterFirstParametersSpeedControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
class DParameterFirstParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    DParameterFirstParametersSpeedControl();

    virtual ~DParameterFirstParametersSpeedControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
class IClippingParameterFirstParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IClippingParameterFirstParametersSpeedControl();

    virtual ~IClippingParameterFirstParametersSpeedControl();

    void getParameter(int& parameter) const;

    void setParameter(const int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int upperLimit;

    int lowerLimit;

    int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class ActivateRampGeneratorSpeedAndPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    ActivateRampGeneratorSpeedAndPositionControl();

    virtual ~ActivateRampGeneratorSpeedAndPositionControl();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
//Enabled the re-initialization of the sinusoidal commutation
class ReinitializationSinusoidalCommutation : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    ReinitializationSinusoidalCommutation();

    virtual ~ReinitializationSinusoidalCommutation();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
class PParameterSecondParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PParameterSecondParametersPositionControl();

    virtual ~PParameterSecondParametersPositionControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class IParameterSecondParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IParameterSecondParametersPositionControl();

    virtual ~IParameterSecondParametersPositionControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class DParameterSecondParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    DParameterSecondParametersPositionControl();

    virtual ~DParameterSecondParametersPositionControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class IClippingParameterSecondParametersPositionControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IClippingParameterSecondParametersPositionControl();

    virtual ~IClippingParameterSecondParametersPositionControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class PParameterSecondParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    PParameterSecondParametersSpeedControl();

    virtual ~PParameterSecondParametersSpeedControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class IParameterSecondParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IParameterSecondParametersSpeedControl();

    virtual ~IParameterSecondParametersSpeedControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class DParameterSecondParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    DParameterSecondParametersSpeedControl();

    virtual ~DParameterSecondParametersSpeedControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class IClippingParameterSecondParametersSpeedControl : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    IClippingParameterSecondParametersSpeedControl();

    virtual ~IClippingParameterSecondParametersSpeedControl();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Maximum speed for initialisation in block commutation
class BlockCommutationMaximumSpeed : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    BlockCommutationMaximumSpeed();

    virtual ~BlockCommutationMaximumSpeed();

    void getParameter(quantity<angular_velocity>& parameter) const;

    void setParameter(const quantity<angular_velocity>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    quantity<angular_velocity> upperLimit;

    quantity<angular_velocity> lowerLimit;

    quantity<angular_velocity> value;

    std::string name;

    ParameterType parameterType;

};
//Commutation (CW) to compensate for the Hall sensor deviations. The aim is that the motor rotates in either direction with equal speed.
class CommutationCompensationClockwise : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    CommutationCompensationClockwise();

    virtual ~CommutationCompensationClockwise();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Commutation (CCW) to compensate for the Hall sensor deviations. The aim is that the motor rotates in either direction with equal speed.
class CommutationCompensationCounterClockwise : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    CommutationCompensationCounterClockwise();

    virtual ~CommutationCompensationCounterClockwise();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};

} // namespace brics_oodl
#endif
