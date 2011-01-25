#ifndef BRICS_OODL_YOUBOTGRIPPERPARAMETER_H
#define BRICS_OODL_YOUBOTGRIPPERPARAMETER_H


#include <vector>
#include <sstream>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "rude/config.h"
#include "generic/Exceptions.hpp"
#include "generic-joint/JointParameter.hpp"
#include "generic-gripper/GripperParameter.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
namespace brics_oodl {

class YouBotGripperParameter : public GripperParameter {
friend class YouBotGripper;
  protected:
    YouBotGripperParameter();


  public:
    virtual ~YouBotGripperParameter();


  protected:
    virtual std::string getName() const = 0;

    std::string name;

};
class CalibrateGripper : public YouBotGripperParameter {
friend class YouBotGripper;
  public:
    CalibrateGripper();

    virtual ~CalibrateGripper();

    void getParameter(bool& parameter) const;

    void setParameter(const bool parameter);


  private:
    std::string getName() const {return this->name;};

    bool value;

    std::string name;

};
class BarSpacingOffset : public YouBotGripperParameter {
friend class YouBotGripper;
  public:
    BarSpacingOffset();

    virtual ~BarSpacingOffset();

    void getParameter(quantity<si::length>& parameter) const;

    void setParameter(const quantity<si::length>& parameter);


  private:
    std::string getName() const {return this->name;};

    quantity<si::length> value;

    std::string name;

};
class MaxEncoderValue : public YouBotGripperParameter {
friend class YouBotGripper;
  public:
    MaxEncoderValue();

    virtual ~MaxEncoderValue();

    void getParameter(unsigned int& parameter) const;

    void setParameter(const unsigned int parameter);


  private:
    std::string getName() const {return this->name;};

    unsigned int value;

    std::string name;

};
class MaxTravelDistance : public YouBotGripperParameter {
friend class YouBotGripper;
  public:
    MaxTravelDistance();

    virtual ~MaxTravelDistance();

    void getParameter(quantity<si::length>& parameter) const;

    void setParameter(const quantity<si::length>& parameter);


  private:
    std::string getName() const {return this->name;};

    quantity<si::length> value;

    std::string name;

};

} // namespace brics_oodl
#endif
