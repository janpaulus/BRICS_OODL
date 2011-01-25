#ifndef BRICS_OODL_YOUBOTBASE_H
#define BRICS_OODL_YOUBOTBASE_H


#include <vector>
#include <sstream>
#include <string>
#include "rude/config.h"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "generic/Exceptions.hpp"
#include "youbot/YouBotJoint.hpp"
#include "youbot/EthercatMaster.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.hpp"
namespace brics_oodl {

class YouBotBase {
  public:
    YouBotBase(const std::string name, const std::string configFilePath = "../config/");

    virtual ~YouBotBase();

    ///return a joint form the base
    ///@param baseJointNumber 1-4 for the base joints
    YouBotJoint& getBaseJoint(const unsigned int baseJointNumber);

    ///gets the cartesien base position which is calculated from the odometry
    ///@param longitudinalPosition is the forward or backward position
    ///@param transversalPosition is the sideway position
    ///@param orientation is the rotation around the center of the YouBot
    void getBasePosition(quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation);

    ///gets the cartesien base velocity
    ///@param longitudinalVelocity is the forward or backward velocity
    ///@param transversalVelocity is the sideway velocity
    ///@param angularVelocity is the rotational velocity around the center of the YouBot
    void getBaseVelocity(quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<si::angular_velocity>& angularVelocity);

    ///commands the base in cartesien velocities
    ///@param longitudinalVelocity is the forward or backward velocity
    ///@param transversalVelocity is the sideway velocity
    ///@param angularVelocity is the rotational velocity around the center of the YouBot
    void setBaseVelocity(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity);

    ///This class represents the kinematic of the YouBot 
    FourSwedishWheelOmniBaseKinematic youBotBaseKinematic;


  private:
    void initializeJoints();

    void initializeKinematic();

    rude::Config configfile;

    std::vector<YouBotJoint> joints;

    std::string configFilePath;

    std::string ethercatConfigFileName;

};

} // namespace brics_oodl
#endif
