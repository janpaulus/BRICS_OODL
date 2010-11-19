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

    void setPositionReferenceToZero(const bool yesOrNo);

    void setJointName(const std::string jointName);

    void getJointName(std::string& jointName);


  private:
    bool findMailboxMsg(const uint8& commandNumber, const uint8& moduleAddress, const uint8& typeNumber, unsigned int& vectorIndex);

    double gearRatio;

    bool gearRatioBeenSet;

    std::vector<JointDataRange> validRanges;

    std::string jointName;

    bool jointNameBeenSet;

    bool PositionReferenceToZero;

    bool PositionReferenceToZeroBeenSet;

    unsigned int encoderTicksPerRound;

    bool encoderTicksPerRoundBeenSet;

    quantity<angular_velocity> maximumPositioningSpeed;

    double PParameterFirstParametersPositionControl;

    std::vector<YouBotSlaveMailboxMsg> mailboxMsgVector;

};

} // namespace brics_oodl
#endif
