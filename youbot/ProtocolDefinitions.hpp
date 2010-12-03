

/*! \mainpage BRICS OODL youBot API
 *
 * \section intro_sec Introduction
 *
 * The youBot API give you complite joint level access to the youBot joints. Every youBot joint is represented as a brics_oodl::YouBotJoint class in the API.
 * At this stage we make no difference if it is a base joint which powers a wheel or a manipulator joint.
 *
 * By the classes brics_oodl::YouBotBase and brics_oodl::YouBotManipulator it is possible to get access to a brics_oodl::YouBotJoint instance for a particular joint.
 *
 * To set and setpoint or read some sensors form the joints you have to use the brics_oodl::JointData classes.
 * Which could be for instance brics_oodl::JointVelocitySetpoint or brics_oodl::JointSensedCurrent.
 *
 * To configure parameters of a joint you have to use the JointParameter classes.
 * Which could be for instance brics_oodl::MaximumPositioningSpeed.
 *
 *
 * \section install_sec Installation
 * System requirements:
 *  - Linux
 *  - Ethernet adapter
 *  - Root access to the ethernet adapter
 * 
 * These libaries are required by the BRICS OODL youBot API:
 * - Simple Open EtherCAT master http://soem.berlios.de
 * - RudeConfig Open Source C++ Config File Library http://rudeserver.com/config/api.html
 * - C++ logging library being proposed to the Boost library http://sourceforge.net/projects/boost-log
 * - Boost C++ Libraries http://www.boost.org
 *
 * You can fetch, compile and install these libary by hand or you can use robotpkg a software packaging tool to do this automaticly.
 * On this site you can find an instruction how to use robopkg: https://github.com/janpaulus/BRICS_Packages/wiki
 * 
 *
 *
 *
 */


#ifndef PROTOCOLDEFINITIONS_HPP
#define	PROTOCOLDEFINITIONS_HPP


//Opcodes of all TMCL commands that can be used in direct mode
typedef enum TMCLCommandNumber {
  ROR = 1,
  ROL = 2,
  MST = 3,
  MVP = 4,
  SAP = 5,
  GAP = 6,
  STAP = 7,
  RSAP = 8,
  SGP = 9,
  GGP = 10,
  STGP = 11,
  RSGP = 12,
  RFS = 13,
  SIO = 14,
  GIO = 15,
  SCO = 30,
  GCO = 31,
  CCO = 32
} CommandNumber;


//Opcodes of TMCL control functions (to be used to run or abort a TMCL program in the module)
#define TMCL_APPL_STOP 128
#define TMCL_APPL_RUN 129
#define TMCL_APPL_RESET 131

//Options for MVP commandds
#define MVP_ABS 0
#define MVP_REL 1
#define MVP_COORD 2

//Options for RFS command
#define RFS_START 0
#define RFS_STOP 1
#define RFS_STATUS 2

#define TMCL_STATUS_OK 100

//Result codes for GetResult
#define TMCL_RESULT_OK 0
#define TMCL_RESULT_NOT_READY 1
#define TMCL_RESULT_CHECKSUM_ERROR 2

enum YouBotJointControllerMode {
    MOTOR_STOP = 0,
    POSITION_CONTROL = 1,
    VELOCITY_CONTROL = 2,
    NO_MORE_ACTION = 3,
    SET_POSITION_TO_REFERENCE = 4
};

enum TMCLModuleAddress {
    DRIVE = 0,
    GRIPPER = 1
};

enum TMCLGripperValue {
  OPEN_GRIPPER = -10000,//0xFFFFFFFF, //0xFFFF0101
  CLOSE_GRIPPER = 10000,//0x0FFFFFFF, //0x0FFF0000
  STOP_GRIPPER = 0x00000000 //0x0FFF0000
};

enum YouBotErrorFlags {
    OVER_CURRENT = 1,
    UNDER_VOLTAGE = 2,
    OVER_VOLTAGE = 4,
    OVER_TEMPERATURE = 8,
    HALTED = 16,
    HALL_SENSOR = 32,
    ENCODER = 64,
    MOTOR_WINDING = 128,
    CYCLE_TIME_VIOLATION = 256,
    INIT_SIN_COMM = 512
};

#endif	/* PROTOCOLDEFINITIONS_HPP */

