/* 
 * File:   ProtocolDefinitions.hpp
 * Author: jan
 *
 * Created on November 18, 2010, 4:10 PM
 */

/*! \mainpage BRICS OODL youBot API
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
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

