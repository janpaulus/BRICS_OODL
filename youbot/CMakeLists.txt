
SET( OODL_YOUBOT_VERSION 0.01 )



FIND_PACKAGE(Soem REQUIRED)
IF (SOEM_FOUND)
  INCLUDE_DIRECTORIES(${SOEM_INCLUDE_DIR})
  LINK_DIRECTORIES(${SOEM_LIBRARY_DIR})
  LINK_LIBRARIES(${SOEMLIB})
	MESSAGE(STATUS "SUCCESSFUL: Soem found at "${SOEM_LIBRARY_DIR})
ELSE (SOEM_FOUND)
	MESSAGE(STATUS "ERROR: Soem not found")
ENDIF (SOEM_FOUND)


FIND_PACKAGE(Rudeconfig REQUIRED)
IF (RUDECONFIG_FOUND)
  INCLUDE_DIRECTORIES(${RUDECONFIG_INCLUDE_DIR})
  LINK_DIRECTORIES(${RUDECONFIG_LIBRARY_DIR})
  LINK_LIBRARIES(${RUDECONFIGLIB})
	MESSAGE(STATUS "SUCCESSFUL: rudeconfig found at "${RUDECONFIG_LIBRARY_DIR})
ELSE (RUDECONFIG_FOUND)
	MESSAGE(STATUS "ERROR: rudeconfig not found")
ENDIF (RUDECONFIG_FOUND)



SET(OODL_YOUBOT_SRC
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/ExceptionOODL.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Logger.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/EthercatMaster.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotJoint.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotBase.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotManipulator.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotGripper.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotGripperParameter.cpp
  
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotJointParameter.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotJointParameterReadOnly.cpp
  ${CMAKE_HOME_DIRECTORY}/base-kinematic/FourSwedishWheelOmniBaseKinematic.cpp
  ${CMAKE_HOME_DIRECTORY}/base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.cpp
)

SET(OODL_YOUBOT_HEADERS
  EthercatMaster.hpp
  YouBotGripper.hpp
  YouBotGripperParameter.hpp
  YouBotBase.hpp
  YouBotManipulator.hpp
  YouBotJoint.hpp
  YouBotJointParameterReadOnly.hpp
  YouBotJointParameter.hpp
  YouBotSlaveMailboxMsg.hpp
  YouBotSlaveMsg.hpp
  ProtocolDefinitions.hpp
../base-kinematic/FourSwedishWheelOmniBaseKinematic.hpp
../base-kinematic/FourSwedishWheelOmniBaseKinematicConfiguration.hpp
../base-kinematic/WheeledBaseKinematic.hpp

../generic/Errors.hpp
../generic/ExceptionOODL.hpp
../generic/Logger.hpp
../generic/Time.hpp
../generic/Units.hpp

../generic-gripper/Gripper.hpp
../generic-gripper/GripperData.hpp
../generic-gripper/GripperParameter.hpp

../generic-joint/Joint.hpp
../generic-joint/JointData.hpp
../generic-joint/JointParameter.hpp

../one-dof-gripper/OneDOFGripper.hpp
../one-dof-gripper/OneDOFGripperData.hpp

)


SET(OODL_YOUBOT_CONFIG
  ${CMAKE_HOME_DIRECTORY}/config/youbot-ethercat.cfg
  ${CMAKE_HOME_DIRECTORY}/config/youbot-base.cfg
  ${CMAKE_HOME_DIRECTORY}/config/youbot-manipulator.cfg
  ${CMAKE_HOME_DIRECTORY}/config/applications.cfg
)

ADD_LIBRARY(OODL_YouBot
  ${OODL_YOUBOT_SRC}
)

add_subdirectory(applications)
add_subdirectory(testing)

MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    INSTALL(FILES ${HEADER} DESTINATION include/oodl/youbot/${DIR})
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

MACRO(INSTALL_CONFIG_WITH_DIRECTORY CONFIG_LIST)
  FOREACH(CONFIG ${${CONFIG_LIST}})
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${CONFIG})
    INSTALL(FILES ${CONFIG} DESTINATION config)
  ENDFOREACH(CONFIG)
ENDMACRO(INSTALL_CONFIG_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(OODL_YOUBOT_HEADERS)
INSTALL_CONFIG_WITH_DIRECTORY(OODL_YOUBOT_CONFIG)
INSTALL(TARGETS OODL_YouBot RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

