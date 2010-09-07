
SET( OODL_SickLD_VERSION 0.01 )

#SET( PROJ_SOURCE_DIR ${OODL_SickLD_SOURCE_DIR} )
#SET( PROJ_BINARY_DIR ${OODL_SickLD_BINARY_DIR} )


IF(NOT DEFINED SICK_TOOLBOX_PATH)
  SET( SICK_TOOLBOX_PATH /opt/ros/cturtle/stacks/laser_drivers/sicktoolbox/sicktoolbox CACHE PATH "Sick Toolbox path")
ENDIF(NOT DEFINED SICK_TOOLBOX_PATH)

FIND_PACKAGE( Boost REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}
  ${Boost_INCLUDE_DIR}
  ${SICK_TOOLBOX_PATH}/include
)

link_directories(
  ${Boost_LIBRARY_DIRS}
  ${SICK_TOOLBOX_PATH}/lib
)

link_libraries(	
  libsickld-1.0.so
  pthread
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  boost_log_setup
  boost_log
)

ADD_EXECUTABLE(OODL_SickLD_test
  ${CMAKE_HOME_DIRECTORY}/sick-ld/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-ld/SickLD.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-ld/SickLDConfiguration.cpp
)

INSTALL(TARGETS OODL_SickLD_test RUNTIME DESTINATION bin )
