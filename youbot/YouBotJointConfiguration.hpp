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
    double gearRatio;


  public:
    std::vector<JointDataRange> validRanges;

    std::string jointName;

    bool setPositionReferenceToZero;


  private:
    unsigned int encoderTicksPerRound;

};

} // namespace brics_oodl
#endif
