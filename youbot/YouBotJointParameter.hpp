#ifndef BRICS_OODL_YOUBOTJOINTPARAMETER_H
#define BRICS_OODL_YOUBOTJOINTPARAMETER_H


#include <vector>
#include <sstream>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "rude/config.h"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/JointParameter.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
namespace brics_oodl {

enum CalibrationDirection {
  POSITIV,
  NEGATIV

};
enum ParameterType {
  MOTOR_CONTOLLER_PARAMETER,
  API_PARAMETER

};
class YouBotJointParameter : public JointParameter {
friend class YouBotJoint;
  protected:
    YouBotJointParameter();


  public:
    virtual ~YouBotJointParameter();


  protected:
    virtual void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const = 0;

    virtual void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) = 0;

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
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {};

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
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {};

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
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {};

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
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

};
class MaximumPositioningSpeed : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    MaximumPositioningSpeed();

    virtual ~MaximumPositioningSpeed();

    void getParameter(quantity<angular_velocity>& parameter) const;

    void setParameter(const quantity<angular_velocity>& parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message);

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

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const;

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message);

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    unsigned int upperLimit;

    unsigned int lowerLimit;

    unsigned int value;

    std::string name;

    ParameterType parameterType;

};
class CalibrateJoint : public YouBotJointParameter {
friend class YouBotJoint;
  public:
    CalibrateJoint();

    virtual ~CalibrateJoint();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);

    void setCalibrationDirection(CalibrationDirection direction);

    void setMaxCurrent(const quantity<si::current>& current);


  private:
    void getYouBotMailboxMsg(YouBotSlaveMailboxMsg& message, MailboxMsgType msgType) const {};

    void setYouBotMailboxMsg(const YouBotSlaveMailboxMsg& message) {};

    std::string getName() const {return this->name;};

    ParameterType getType() const {return this->parameterType;};

    bool value;

    std::string name;

    ParameterType parameterType;

    CalibrationDirection calibrationDirection;

    quantity<si::current> maxCurrent;

};

} // namespace brics_oodl
#endif
