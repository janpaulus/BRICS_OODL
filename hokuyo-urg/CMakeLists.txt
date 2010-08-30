
SET( OODL_HokuyoURG_VERSION 0.01 )

#SET( PROJ_SOURCE_DIR ${OODL_HokuyoURG_SOURCE_DIR} )
#SET( PROJ_BINARY_DIR ${OODL_HokuyoURG_BINARY_DIR} )

IF(NOT DEFINED HOKUYO_URG_PATH)
  SET( HOKUYO_URG_PATH ${CMAKE_HOME_DIRECTORY}/../BRICS_Software/ CACHE PATH "Hokuyo URG path")
ENDIF(NOT DEFINED HOKUYO_URG_PATH)

FIND_PACKAGE( Boost REQUIRED )
#FIND_PACKAGE( SDL REQUIRED )
#FIND_PACKAGE( SDL_net REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/
  ${CMAKE_HOME_DIRECTORY}/generic/
  ${Boost_INCLUDE_DIR}
  ${HOKUYO_URG_PATH}/include/urg

)

link_directories(
  ${Boost_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}/lib
  ${HOKUYO_URG_PATH}/lib
)

link_libraries(	
    liburg.a
    liburg_common.a
    liburg_connection.a
    liburg_connection_sdl.a
    liburg_coordinate.a
    liburg_geometry.a
    liburg_monitor.a
    liburg_system.a
 #  libc_urg.a
 #  libc_urg_connection.a
 #  libc_urg_system.a
    SDL
)

ADD_EXECUTABLE(OODL_HokuyoURG_test
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/HokuyoURG.cpp
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/HokuyoURGConfiguration.cpp
)

INSTALL(TARGETS OODL_HokuyoURG_test RUNTIME DESTINATION bin )
