PROJECT(OODeviceLayer)

cmake_minimum_required(VERSION 2.4)

SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin CACHE PATH "executable output path" )

SET( SICK_TOOLBOX_PATH /opt/ros/cturtle/stacks/laser_drivers/sicktoolbox/sicktoolbox CACHE PATH "Sick Toolbox path")


FIND_PACKAGE( Boost REQUIRED )
FIND_PACKAGE( SDL REQUIRED )



include_directories(
  ${CMAKE_HOME_DIRECTORY}/src
  ${Boost_INCLUDE_DIR}
  ${SICK_TOOLBOX_PATH}/include
)

link_directories(
  ${Boost_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}/lib
  ${SICK_TOOLBOX_PATH}/lib
)

link_libraries(	
  libsicklms-1.0.so
  pthread
)

ADD_EXECUTABLE(OODeviceLayerDataTypes
  ${CMAKE_HOME_DIRECTORY}/src/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/src/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/src/SickLMS2xxConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/src/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/src/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/src/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/src/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/src/SickLMS2xx.cpp
)


