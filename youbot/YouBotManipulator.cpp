
#include "youbot/YouBotManipulator.hpp"
namespace brics_oodl {

YouBotManipulator::YouBotManipulator(const std::string name, const std::string configFilePath) {
  // Bouml preserved body begin 00067F71

  string filename;
  filename = configFilePath;
  filename.append(name);
  filename.append(".cfg");

  this->configFilePath = configFilePath;
  this->ethercatConfigFileName = "youbot-ethercat.cfg";

  if(!configfile.load(filename.c_str()))
      throw FileNotFoundException(filename + " file no found");


  this->initializeJoints();

  // Bouml preserved body end 00067F71
}

YouBotManipulator::~YouBotManipulator() {
  // Bouml preserved body begin 00067FF1
  // Bouml preserved body end 00067FF1
}

///return a joint form the arm1
///@param armJointNumber 1-5 for the arm1 joints
YouBotJoint& YouBotManipulator::getArmJoint(const unsigned int armJointNumber) {
  // Bouml preserved body begin 0004F7F1

    if (armJointNumber <= 0 || armJointNumber > 5) {
      throw std::out_of_range("Invalid Joint Number");
    }
    return joints[armJointNumber - 1];
  // Bouml preserved body end 0004F7F1
}

YouBotGripper& YouBotManipulator::getArmGripper() {
  // Bouml preserved body begin 0005F9F1
    if (this->gripperVector.size() >= 1) {
      return this->gripperVector[0];
    } else {
      throw std::out_of_range("There is no Gripper");
    }
  // Bouml preserved body end 0005F9F1
}

void YouBotManipulator::initializeJoints() {
  // Bouml preserved body begin 00068071

    LOG(info) << "Initializing Joints";


    //get number of slaves
    unsigned int noSlaves = EthercatMaster::getInstance(this->ethercatConfigFileName, this->configFilePath).getNumberOfSlaves();


    if(noSlaves < 5){
      throw ExceptionOODL("Not enough ethercat slaves were found to create a YouBotManipulator!");
    }

    configfile.setSection("JointTopology");

    unsigned int slaveNumber = configfile.getIntValue("ManipulatorJoint1");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw std::out_of_range("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("ManipulatorJoint2");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw std::out_of_range("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("ManipulatorJoint3");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw std::out_of_range("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("ManipulatorJoint4");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw std::out_of_range("The ethercat slave number is not available!");
    }

    slaveNumber = configfile.getIntValue("ManipulatorJoint5");
    if(slaveNumber  <= noSlaves){
      joints.push_back(YouBotJoint(slaveNumber));
    }else{
      throw std::out_of_range("The ethercat slave number is not available!");
    }



    

    //Configure Joint Parameters
    std::string jointName;
    JointName jName;
    GearRatio gearRatio;
    EncoderTicksPerRound ticksPerRound;
    InverseMovementDirection inverseDir;


    for (unsigned int i = 0; i < 5; i++) {
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


    //TODO When to calibrate the manipulator and when it is not necessary
    //Calibrate all manipulator joints
    std::vector<CalibrateJoint> calibrateJointVec;
    quantity<si::current> current;
    JointLimits jLimits;
    bool doCalibration = true;

    for (unsigned int i = 0; i < 5; i++) {

      std::stringstream jointNameStream;
      jointNameStream << "Joint_" << i + 1;
      jointName = jointNameStream.str();
      configfile.setSection(jointName.c_str());

      doCalibration = configfile.getBoolValue("DoCalibration");

      jLimits.setParameter(configfile.getIntValue("LowerLimit_[encoderTicks]"), configfile.getIntValue("UpperLimit_[encoderTicks]"));
      joints[i].setConfigurationParameter(jLimits);

      current = configfile.getDoubleValue("CalibrationMaxCurrent_[ampere]") * ampere;
      std::string direction = configfile.getStringValue("CalibrationDirection");

      calibrateJointVec.push_back(CalibrateJoint());

      if (direction == "POSITIV") {
        calibrateJointVec[i].setParameter(doCalibration, POSITIV, current);
      } else if (direction == "NEGATIV") {
        calibrateJointVec[i].setParameter(doCalibration, NEGATIV, current);
      } else {
        throw ExceptionOODL("Wrong calibration direction for " + jointName);
      }
      joints[i].setConfigurationParameter(calibrateJointVec[i]);
    }



    //Initializing Gripper
    configfile.setSection("JointTopology");
    this->gripperVector.push_back(YouBotGripper(configfile.getIntValue("ManipulatorJoint5")));
    BarSpacingOffset barOffest;
    MaxTravelDistance maxDistance;
    MaxEncoderValue maxEncoder;

    configfile.setSection("Gripper");
    doCalibration = configfile.getBoolValue("DoCalibration");
    barOffest.setParameter(configfile.getDoubleValue("BarSpacingOffset_[meter]") * meter);
    gripperVector[0].setConfigurationParameter(barOffest);
    maxDistance.setParameter(configfile.getDoubleValue("MaxTravelDistance_[meter]") * meter);
    gripperVector[0].setConfigurationParameter(maxDistance);
    maxEncoder.setParameter(configfile.getIntValue("MaxEncoderValue"));
    gripperVector[0].setConfigurationParameter(maxEncoder);

    // Calibrating Gripper
    CalibrateGripper calibrate;
    calibrate.setParameter(doCalibration);
    gripperVector[0].setConfigurationParameter(calibrate);

    return;
  // Bouml preserved body end 00068071
}


} // namespace brics_oodl
