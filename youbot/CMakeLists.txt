
SET( OODL_YOUBOT_VERSION 0.01 )

FIND_PACKAGE( Boost REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}
  ${Boost_INCLUDE_DIR}
)

link_directories(
  ${Boost_LIBRARY_DIRS}

)

link_libraries(
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  boost_log-mt
)

SET(OODL_YOUBOT_SRC
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Logger.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-joint/JointData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-joint/JointConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBotJoint.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/YouBot.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/ethercat-master/soem_driver_factory.cpp
  ${CMAKE_HOME_DIRECTORY}/youbot/ethercat-master/soem_master.cpp
)

SET(OODL_YOUBOT_HEADERS

)

ADD_LIBRARY(OODL_YOUBOT
  ${OODL_YOUBOT_SRC}
)
  

#ADD_EXECUTABLE(OODL_YOUBOT_test
#  ${CMAKE_HOME_DIRECTORY}/sick-s300/applications/Test.cpp
#  ${OODL_YOUBOT_SRC}
#)


MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    INSTALL(FILES ${HEADER} DESTINATION include/${DIR})
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(OODL_SickS300_HEADERS)
INSTALL(TARGETS OODL_YOUBOT RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

