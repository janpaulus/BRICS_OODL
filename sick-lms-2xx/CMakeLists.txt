
SET( OODL_SickLMS2xx_VERSION 0.01 )

IF(NOT DEFINED SICK_TOOLBOX_PATH)
  SET( SICK_TOOLBOX_PATH /opt/ros/cturtle/stacks/laser_drivers/sicktoolbox/sicktoolbox CACHE PATH "Sick Toolbox path")
ENDIF(NOT DEFINED SICK_TOOLBOX_PATH)

FIND_PACKAGE( Boost REQUIRED )


include_directories(
  ${CMAKE_HOME_DIRECTORY}/
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
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xx.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xxConfiguration.cpp
)


ADD_EXECUTABLE(OODL_SickLMS2xx_test
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xx.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xxConfiguration.cpp
)

ADD_EXECUTABLE(OODL_SickLMS2xx_plot
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/applications/plot_laserscanner_values.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/gnuplot_i.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xx.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-lms-2xx/SickLMS2xxConfiguration.cpp
)

INSTALL(TARGETS OODL_SickLMS2xx_test OODL_SickLMS2xx_plot OODL_SickLMS2xx RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

