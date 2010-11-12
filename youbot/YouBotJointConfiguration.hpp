#ifndef BRICS_OODL_YOUBOTJOINTCONFIGURATION_H
#define BRICS_OODL_YOUBOTJOINTCONFIGURATION_H


#include <vector>
#include <sstream>
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/ExceptionOODL.hpp"
#include "generic-joint/JointConfiguration.hpp"
namespace brics_oodl {

class YouBotJointConfiguration {
  public:
    YouBotJointConfiguration();

    virtual ~YouBotJointConfiguration();

    YouBotJointConfiguration(const YouBotJointConfiguration & source);

    YouBotJointConfiguration & operator=(const YouBotJointConfiguration & source);

    void setGearRatio(double ratio);

    double getGearRatio() const;

    unsigned int getEncoderTicksPerRound() const;

    void setEncoderTicksPerRound(unsigned int ticksPerRound);


  private:
    double GearRatio;


  public:
    std::vector<JointDataRange> ValidRanges;

    std::string JointName;

    bool SetPositionReferenceToZero;


  private:
    unsigned int EncoderTicksPerRound;

};

} // namespace brics_oodl
#endif
