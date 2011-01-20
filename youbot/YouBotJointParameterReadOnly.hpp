#ifndef BRICS_OODL_YOUBOTJOINTPARAMETERREADONLY_H
#define BRICS_OODL_YOUBOTJOINTPARAMETERREADONLY_H


#include <vector>
#include <sstream>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/JointParameter.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
#include "youbot/YouBotJointStorage.hpp"
namespace brics_oodl {

enum ParameterType {
  MOTOR_CONTOLLER_PARAMETER,
  API_PARAMETER

};
class YouBotJointParameterReadOnly : public JointParameter {
friend class YouBotJoint;
  protected:
    YouBotJointParameterReadOnly();


  public:
    virtual ~YouBotJointParameterReadOnly();


  protected:
    virtual void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const = 0;

    virtual void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage) = 0;

    virtual std::string getName() const = 0;

    virtual ParameterType getType() const = 0;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class ArePIDcontrollersActive : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    ArePIDcontrollersActive();

    virtual ~ArePIDcontrollersActive();

    void getParameter(bool& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
class CommutationMode : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    CommutationMode();

    virtual ~CommutationMode();

    void getParameter(int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class PWMSchemeBlockCommutation : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    PWMSchemeBlockCommutation();

    virtual ~PWMSchemeBlockCommutation();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class MotorContollerGearRatio : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    MotorContollerGearRatio();

    virtual ~MotorContollerGearRatio();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class MotorCoilResistance : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    MotorCoilResistance();

    virtual ~MotorCoilResistance();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class InitializationMode : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    InitializationMode();

    virtual ~InitializationMode();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class EncoderResolution : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    EncoderResolution();

    virtual ~EncoderResolution();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class ReversingEncoderDirection : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    ReversingEncoderDirection();

    virtual ~ReversingEncoderDirection();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class MotorPoles : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    MotorPoles();

    virtual ~MotorPoles();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
//Switches the ramp generator for speed and position control on and off
class HallSensorPolarityReversal : public YouBotJointParameterReadOnly {
friend class YouBotJoint;
  public:
    HallSensorPolarityReversal();

    virtual ~HallSensorPolarityReversal();

    void getParameter(unsigned int& parameter) const;


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, TMCLCommandNumber msgType, const YouBotJointStorage& storage) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message, const YouBotJointStorage& storage);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};

} // namespace brics_oodl
#endif
