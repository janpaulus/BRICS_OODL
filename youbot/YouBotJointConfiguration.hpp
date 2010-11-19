#ifndef BRICS_OODL_YOUBOTJOINTCONFIGURATION_H
#define BRICS_OODL_YOUBOTJOINTCONFIGURATION_H


#include <vector>
#include <sstream>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/JointConfiguration.hpp"
#include "youbot/ProtocolDefinitions.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
namespace brics_oodl {

class YouBotJointConfiguration : public JointConfiguration {
friend class YouBotJoint;
  public:
    YouBotJointConfiguration();

    virtual ~YouBotJointConfiguration();

    void setGearRatio(const double ratio);

    double getGearRatio() const;

    unsigned int getEncoderTicksPerRound() const;

    void setEncoderTicksPerRound(const unsigned int ticksPerRound);

    void setMaximumPositioningSpeed(const quantity<angular_velocity>& maximumPositioningSpeed);

    void getMaximumPositioningSpeed(quantity<angular_velocity>& maxPositioningSpeed);

    void getPParameterFirstParametersPositionControl(double& PParameter);


  private:
    double gearRatio;


  public:
    std::vector<JointDataRange> validRanges;

    std::string jointName;

    bool setPositionReferenceToZero;


  private:
    unsigned int encoderTicksPerRound;

    quantity<angular_velocity> maximumPositioningSpeed;

    std::vector<YouBotSlaveMailboxMsg> mailboxMsgVector;

    double PParameterFirstParametersPositionControl;

};

} // namespace brics_oodl
#endif
