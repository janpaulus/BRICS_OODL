
SET( OODL_SickS300_VERSION 0.01 )

#SET( PROJ_SOURCE_DIR ${OODL_SickS300_SOURCE_DIR} )
#SET( PROJ_BINARY_DIR ${OODL_SickS300_BINARY_DIR} )


FIND_PACKAGE( Boost REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}/sick-s300/
  ${CMAKE_HOME_DIRECTORY}/generic/
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
boost_log_setup
boost_log
)

ADD_LIBRARY(OODL_SickS300
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SickS300Configuration.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/ScannerSickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SerialIO.cpp
)

ADD_EXECUTABLE(OODL_SickS300_test
  ${CMAKE_HOME_DIRECTORY}/sick-s300/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SickS300Configuration.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/ScannerSickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300/SerialIO.cpp
)

INSTALL(TARGETS OODL_SickS300_test OODL_SickS300 RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

