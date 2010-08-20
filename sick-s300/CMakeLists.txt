
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
  ${Boost_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}/lib
)

link_libraries(	

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

INSTALL(TARGETS OODL_SickS300_test RUNTIME DESTINATION bin )
