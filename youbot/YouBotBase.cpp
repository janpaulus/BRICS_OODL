
#include "youbot/YouBotBase.hpp"
namespace brics_oodl {

YouBotBase::YouBotBase(const std::string name) {
  // Bouml preserved body begin 00067E71

  string configFilename;
  configFilename = "../config/";
  configFilename.append(name);
  configFilename.append(".cfg");

  if(!configfile.load(configFilename.c_str()))
      throw ExceptionOODL(configFilename + " file no found");

  this->initializeJoints();

  this->initializeKinematic();

  // Bouml preserved body end 00067E71
}

YouBotBase::~YouBotBase() {
  // Bouml preserved body begin 00067EF1
  // Bouml preserved body end 00067EF1
}

///return a joint form the base
///@param jointNumber 1-4 for the base joints
YouBotJoint& YouBotBase::getBaseJoint(const unsigned int baseJointNumber) {
  // Bouml preserved body begin 0004F771
    if (baseJointNumber <= 0 || baseJointNumber > 4 ) {
      throw ExceptionOODL("Invalid Joint Number");
    }
    return joints[baseJointNumber - 1];
  // Bouml preserved body end 0004F771
}

///gets the cartesien base position which is calculated from the odometry
///@param longitudinalPosition is the forward or backward position
///@param transversalPosition is the sideway position
///@param orientation is the rotation around the center of the YouBot
void YouBotBase::getBasePosition(quantity<si::length>& longitudinalPosition, quantity<si::length>& transversalPosition, quantity<plane_angle>& orientation) {
  // Bouml preserved body begin 000514F1

    std::vector<quantity<plane_angle> > wheelPositions;
    quantity<plane_angle> dummy;
    JointSensedAngle sensedPos;
    wheelPositions.assign(4, dummy);

    joints[0].getData(sensedPos);
    wheelPositions[0] = sensedPos.angle;
    joints[1].getData(sensedPos);
    wheelPositions[1] = sensedPos.angle;
    joints[2].getData(sensedPos);
    wheelPositions[2] = sensedPos.angle;
    joints[3].getData(sensedPos);
    wheelPositions[3] = sensedPos.angle;

    youBotBaseKinematic.wheelPositionsToCartesianPosition(wheelPositions, longitudinalPosition, transversalPosition, orientation);
  // Bouml preserved body end 000514F1
}

///gets the cartesien base velocity
///@param longitudinalVelocity is the forward or backward velocity
///@param transversalVelocity is the sideway velocity
///@param angularVelocity is the rotational velocity around the center of the YouBot
void YouBotBase::getBaseVelocity(quantity<si::velocity>& longitudinalVelocity, quantity<si::velocity>& transversalVelocity, quantity<si::angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 00051271

    std::vector<quantity<angular_velocity> > wheelVelocities;
    quantity<angular_velocity> dummy;
    JointSensedVelocity sensedVel;
    wheelVelocities.assign(4, dummy);

    joints[0].getData(sensedVel);
    wheelVelocities[0] = sensedVel.angularVelocity;
    joints[1].getData(sensedVel);
    wheelVelocities[1] = sensedVel.angularVelocity;
    joints[2].getData(sensedVel);
    wheelVelocities[2] = sensedVel.angularVelocity;
    joints[3].getData(sensedVel);
    wheelVelocities[3] = sensedVel.angularVelocity;

    youBotBaseKinematic.wheelVelocitiesToCartesianVelocity(wheelVelocities, longitudinalVelocity, transversalVelocity, angularVelocity);

  // Bouml preserved body end 00051271
}

///commands the base in cartesien velocities
///@param longitudinalVelocity is the forward or backward velocity
///@param transversalVelocity is the sideway velocity
///@param angularVelocity is the rotational velocity around the center of the YouBot
void YouBotBase::setBaseVelocity(const quantity<si::velocity>& longitudinalVelocity, const quantity<si::velocity>& transversalVelocity, const quantity<si::angular_velocity>& angularVelocity) {
  // Bouml preserved body begin 0004DD71

    std::vector<quantity<angular_velocity> > wheelVelocities;
    JointVelocitySetpoint setVel;

    youBotBaseKinematic.cartesianVelocityToWheelVelocities(longitudinalVelocity, transversalVelocity, angularVelocity, wheelVelocities);

    if (wheelVelocities.size() < 4)
      throw ExceptionOODL("To less wheel velocities");

    setVel.angularVelocity = wheelVelocities[0];
    joints[0].setData(setVel, NON_BLOCKING);
    setVel.angularVelocity = wheelVelocities[1];
    joints[1].setData(setVel, NON_BLOCKING);
    setVel.angularVelocity = wheelVelocities[2];
    joints[2].setData(setVel, NON_BLOCKING);
    setVel.angularVelocity = wheelVelocities[3];
    joints[3].setData(setVel, NON_BLOCKING);
  // Bouml preserved body end 0004DD71
}

void YouBotBase::initializeJoints() {
  // Bouml preserved body begin 000464F1

    LOG(info) << "Initializing Joints";

    //get number of slaves
    unsigned int noSlaves = EthercatMaster::getInstance().getNumberOfSlaves();

    if(noSlaves < 4){
      throw ExceptionOODL("Not enough ethercat slaves were found to create a YouBotBase!");
    }

    configfile.setSection("JointTopology");

    unsigned int slaveNumber = configfile.getIntValue("BaseLeftFront");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw ExceptionOODL("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("BaseRightFront");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw ExceptionOODL("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("BaseLeftBack");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw ExceptionOODL("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("BaseRightBack");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw ExceptionOODL("The ethercat slave number is not available!");
    }


    //Configure Joint Parameters
    std::string jointName;
    JointName jName;
    GearRatio gearRatio;
    EncoderTicksPerRound ticksPerRound;
    InverseMovementDirection inverseDir;


    for (unsigned int i = 0; i < 4; i++) {
      std::stringstream jointNameStream;
      jointNameStream << "Joint_" << i + 1;
      jointName = jointNameStream.str();
      configfile.setSection(jointName.c_str());

      jName.setParameter(configfile.getStringValue("JointName"));
      double gearRatio_numerator = configfile.getIntValue("GearRatio_numerator");
      double gearRatio_denominator = configfile.getIntValue("GearRatio_denominator");
      gearRatio.setParameter(gearRatio_numerator / gearRatio_denominator);
      ticksPerRound.setParameter(configfile.getIntValue("EncoderTicksPerRound"));
      inverseDir.setParameter(configfile.getBoolValue("InverseMovementDirection"));

      joints[i].setConfigurationParameter(jName);
      joints[i].setConfigurationParameter(gearRatio);
      joints[i].setConfigurationParameter(ticksPerRound);
      joints[i].setConfigurationParameter(inverseDir);

    }

    return;
  // Bouml preserved body end 000464F1
}

void YouBotBase::initializeKinematic() {
  // Bouml preserved body begin 0004DDF1
    FourSwedishWheelOmniBaseKinematicConfiguration kinematicConfig;

    //read the kinematics parameter from a config file
    configfile.setSection("YouBotKinematic");
    kinematicConfig.rotationRatio = configfile.getIntValue("RotationRatio");
    kinematicConfig.slideRatio = configfile.getIntValue("SlideRatio");
    kinematicConfig.lengthBetweenFrontAndRearWheels = configfile.getDoubleValue("LengthBetweenFrontAndRearWheels_[meter]") * meter;
    kinematicConfig.lengthBetweenFrontWheels = configfile.getDoubleValue("LengthBetweenFrontWheels_[meter]") * meter;
    kinematicConfig.wheelRadius = configfile.getDoubleValue("WheelRadius_[meter]") * meter;

    youBotBaseKinematic.setConfiguration(kinematicConfig);
  // Bouml preserved body end 0004DDF1
}


} // namespace brics_oodl
