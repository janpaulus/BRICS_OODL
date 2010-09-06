#PROJECT(OODL_SickLMS2xx)

#cmake_minimum_required(VERSION 2.4)

SET( OODL_SickLMS2xx_VERSION 0.01 )

#SET( PROJ_SOURCE_DIR ${OODL_SickLMS2xx_SOURCE_DIR} )
#SET( PROJ_BINARY_DIR ${OODL_SickLMS2xx_BINARY_DIR} )

#SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin CACHE PATH "executable output path" )

IF(NOT DEFINED SICK_TOOLBOX_PATH)
  SET( SICK_TOOLBOX_PATH /opt/ros/cturtle/stacks/laser_drivers/sicktoolbox/sicktoolbox CACHE PATH "Sick Toolbox path")
ENDIF(NOT DEFINED SICK_TOOLBOX_PATH)

FIND_PACKAGE( Boost REQUIRED )
#FIND_PACKAGE( SDL REQUIRED )



include_directories(
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/
${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications
  ${CMAKE_HOME_DIRECTORY}/generic/
  ${Boost_INCLUDE_DIR}
  ${SICK_TOOLBOX_PATH}/include
)

link_directories(
  ${Boost_LIBRARY_DIRS}
  ${SICK_TOOLBOX_PATH}/lib
)

link_libraries(	
  libsicklms-1.0.so
  pthread
boost_thread
boost_date_time
boost_system
boost_filesystem
boost_regex
boost_log_setup
boost_log
)

ADD_LIBRARY(OODL_SickLMS2xx
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xx.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xxConfiguration.cpp
)


ADD_EXECUTABLE(OODL_SickLMS2xx_test
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xx.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xxConfiguration.cpp
)

ADD_EXECUTABLE(OODL_SickLMS2xx_plot
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications/plot_laserscanner_values.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications/gnuplot_i.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xx.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xxConfiguration.cpp
)

INSTALL(TARGETS OODL_SickLMS2xx_test OODL_SickLMS2xx_plot OODL_SickLMS2xx RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

