#ifndef BRICS_OODL_YOUBOTMANIPULATOR_H
#define BRICS_OODL_YOUBOTMANIPULATOR_H


#include <vector>
#include <sstream>
#include <string>
#include "rude/config.h"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "generic/Exceptions.hpp"
#include "youbot/EthercatMaster.hpp"
#include "youbot/YouBotGripper.hpp"
#include "youbot/YouBotJoint.hpp"
namespace brics_oodl {

class YouBotManipulator {
  public:
    YouBotManipulator(const std::string name, const std::string configFilePath = "../config/");

    virtual ~YouBotManipulator();

    ///return a joint form the arm1
    ///@param armJointNumber 1-5 for the arm1 joints
    YouBotJoint& getArmJoint(const unsigned int armJointNumber);

    YouBotGripper& getArmGripper();


  private:
    void initializeJoints();

    rude::Config configfile;

    std::vector<YouBotJoint> joints;

    std::vector<YouBotGripper> gripperVector;

    std::string configFilePath;

    std::string ethercatConfigFileName;

};

} // namespace brics_oodl
#endif
