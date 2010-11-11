
SET( OODL_YOUBOT_VERSION 0.01 )

FIND_PACKAGE( Boost REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}
  ${Boost_INCLUDE_DIR}
  #for soem
 # ${CMAKE_HOME_DIRECTORY}/youbot/src
)

link_directories(
  ${Boost_LIBRARY_DIRS}

)

link_libraries(
  libsoem.a
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  boost_log-mt
#for soem
#pthread
)

SET(OODL_YOUBOT_SRC
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/ExceptionOODL.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Logger.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-joint/JointData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-joint/JointConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBot.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotJoint.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotGripper.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/EthercatMaster.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotJointConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/base-kinematic/FourSwedishWheelOmniBaseKinematic.cpp
)

SET(SOEM_SRC
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatbase.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatcoe.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatconfig.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatfoe.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatsoe.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatmain.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatprint.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/nicdrv.c 
  ${CMAKE_HOME_DIRECTORY}/youbot/src/ethercatdc.c
) 

SET(OODL_YOUBOT_HEADERS

)

#ADD_LIBRARY(OODL_YOUBOT
#  ${OODL_YOUBOT_SRC}
#)
  

ADD_EXECUTABLE(OODL_YOUBOT_test
  ${CMAKE_HOME_DIRECTORY}/youbot/applications/Test.cpp
  ${OODL_YOUBOT_SRC}
# ${SOEM_SRC}
)


MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    INSTALL(FILES ${HEADER} DESTINATION include/${DIR})
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(OODL_SickS300_HEADERS)
INSTALL(TARGETS OODL_YOUBOT_test RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

