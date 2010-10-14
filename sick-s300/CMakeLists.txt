
SET( OODL_SickS300_VERSION 0.01 )

#SET( PROJ_SOURCE_DIR ${OODL_SickS300_SOURCE_DIR} )
#SET( PROJ_BINARY_DIR ${OODL_SickS300_BINARY_DIR} )


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

SET(OODL_SickS300_SRC
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Logger.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/ScannerSickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SerialIO.cpp
)

ADD_LIBRARY(OODL_SickS300
  ${OODL_SickS300_SRC}
)
  

ADD_EXECUTABLE(OODL_SickS300_test
  ${CMAKE_HOME_DIRECTORY}/sick-s300/applications/Test.cpp
  ${OODL_SickS300_SRC}
)

ADD_EXECUTABLE(OODL_SickS300_plot
  ${CMAKE_HOME_DIRECTORY}/sick-s300/applications/plot_laserscanner_values.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/LaserScannerTools.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/gnuplot_i.cpp
  ${OODL_SickS300_SRC}
)

INSTALL(TARGETS OODL_SickS300_plot OODL_SickS300_test OODL_SickS300 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

