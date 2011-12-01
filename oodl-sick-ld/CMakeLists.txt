
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
rosbuild_init()
# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)



#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

SET(CMAKE_MODULE_PATH "${CMAKE_HOME_DIRECTORY}/../cmake-modules")

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

FIND_PACKAGE( Boost REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}
  ${CMAKE_HOME_DIRECTORY}/../
  ${CMAKE_HOME_DIRECTORY}/../generic
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
)

set(SickLD_SRC
  ${CMAKE_HOME_DIRECTORY}/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/../generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/../generic/Logger.cpp
  ${CMAKE_HOME_DIRECTORY}/../generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/../generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/../generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/../generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/SickLD.cpp
  ${CMAKE_HOME_DIRECTORY}/SickLDConfiguration.cpp
)

ADD_LIBRARY(OODL_SickLD
  ${SickLD_SRC}
)

ADD_EXECUTABLE(OODL_SickLD_test
  ${SickLD_SRC}
)

