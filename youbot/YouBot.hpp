#ifndef BRICS_OODL_YOUBOT_H
#define BRICS_OODL_YOUBOT_H


#include <vector>
#include <sstream>
#include <string>
#include <boost/thread.hpp>
#include "rude/config.h"
#include "generic/Logger.hpp"
#include "generic/Units.hpp"
#include "generic/Time.hpp"
#include "generic/ExceptionOODL.hpp"
#include "youbot/YouBotSlaveMsg.hpp"
#include "youbot/EthercatMaster.hpp"
#include "youbot/YouBotJoint.hpp"
#include "youbot/YouBotSlaveMailboxMsg.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp"
#include "base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.hpp"

extern "C"{
#include <ethercattype.h>
#include <ethercatmain.h>
}

namespace brics_oodl {

//have to be a singleton in the system
class YouBot {
friend class YouBotJoint;
  private:
    static YouBot* instance;

    YouBot();

    YouBot(const YouBot& ) {};

    ~YouBot();


  public:
    static YouBot& getInstance();

    static void destroy();

    ///return the quantity of joints
    unsigned int getNumberOfJoints() const;

    ///return a joint form the base, arm1 or arm2
    ///@param jointNumber 1-4 are the base joints, 5-9 are the arm1 joints, 9-14 are the arm2 joints
    YouBotJoint& getJoint(const unsigned int jointNumber);

    ///return a joint form the base, arm1 or arm2
    ///@param jointName e.g. BaseLeftFront
    YouBotJoint& getJointByName(const std::string jointName);

    ///return a joint form the base
    ///@param jointNumber 1-4 for the base joints
    YouBotJoint& getBaseJoint(const unsigned int baseJointNumber);

    ///return a joint form the arm1
    ///@param jointNumber 1-5 for the arm1 joints
    YouBotJoint& getArm1Joint(const unsigned int arm1JointNumber);

    ///return a joint form the arm2
    ///@param jointNumber 1-5 for the arm2 joints
    YouBotJoint& getArm2Joint(const unsigned int arm2JointNumber);

    ///commands the base in cartesien velocities
    ///@param longitudinalVelocity is the forward or backward velocity
    ///@param transversalVelocity is the sideway velocity
    ///@param angularVelocity is the rotational velocity around the center of the YouBot
    void setBaseVelocity(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity);

    ///gets the cartesien base velocity
    ///@param longitudinalVelocity is the forward or backward velocity
    ///@param transversalVelocity is the sideway velocity
    ///@param angularVelocity is the rotational velocity around the center of the YouBot
    void getBaseVelocity(quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<si::angular_velocity>& angularVelocity);

    ///gets the cartesien base position which is calculated from the odometry
    ///@param longitudinalPosition is the forward or backward position
    ///@param transversalPosition is the sideway position
    ///@param orientation is the rotation around the center of the YouBot
    void getBasePosition(quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation);

    ///This class represents the kinematic of the YouBot 
    FourSwedishWheelOmniBaseKinematic youBotBaseKinematic;


  private:
    void initializeEthercat();

    void initializeJoints();

    void initializeKinematic();

    bool closeEthercat();

    void setMsgBuffer(const YouBotSlaveMsg& msgBuffer, const unsigned int jointNumber);

    YouBotSlaveMsg getMsgBuffer(const unsigned int jointNumber);

    void setMailboxMsgBuffer(const YouBotSlaveMailboxMsg& msgBuffer, const unsigned int jointNumber);

    void getMailboxMsgBuffer(YouBotSlaveMailboxMsg& mailboxMsg, const unsigned int jointNumber);

    bool sendMailboxMessage(const YouBotSlaveMailboxMsg& mailboxMsg);

    bool receiveMailboxMessage(YouBotSlaveMailboxMsg& mailboxMsg);

    void updateSensorActorValues();

    std::vector<YouBotJoint> joints;

    EthercatMaster* ethercatMaster;

    std::string ethernetDevice;

    ec_mbxbuft mailboxBuffer;

    //in milliseconds
    unsigned int timeTillNextEthercatUpdate;

    boost::mutex mutexDataOne;

    boost::mutex mutexDataTwo;

    boost::thread_group threads;

    volatile bool stopThread;

    boost::mutex mutexEthercatMaster;

    std::vector<YouBotSlaveMsg> firstBufferVector;

    std::vector<YouBotSlaveMsg> secondBufferVector;

    unsigned int nrOfSlaves;

    volatile bool newDataFlagOne;

    volatile bool newDataFlagTwo;

    std::vector<bool> newOutputDataFlagOne;

    std::vector<bool> newOutputDataFlagTwo;

    std::vector<OutputBuffer*> ethercatOutputBufferVector;

    std::vector<InputBuffer*> ethercatInputBufferVector;

    std::vector<YouBotSlaveMailboxMsg> firstMailboxBufferVector;

    std::vector<YouBotSlaveMailboxMsg> secondMailboxBufferVector;

    std::vector<bool> newMailboxDataFlagOne;

    std::vector<bool> newMailboxDataFlagTwo;

    ec_mbxbuft mailboxBufferSend;

    unsigned int mailboxTimeout;

    ec_mbxbuft mailboxBufferReceive;

    std::vector<bool> newMailboxInputDataFlagOne;

    std::vector<bool> newMailboxInputDataFlagTwo;

    rude::Config configfile;

};

} // namespace brics_oodl
#endif
