
SET( OODL_HokuyoURG_VERSION 0.01 )


IF(NOT DEFINED HOKUYO_URG_PATH)
  SET( HOKUYO_URG_PATH ${CMAKE_HOME_DIRECTORY}/../openrobots/ CACHE PATH "Hokuyo URG path")
ENDIF(NOT DEFINED HOKUYO_URG_PATH)

FIND_PACKAGE( Boost REQUIRED )
#FIND_PACKAGE( SDL REQUIRED )
#FIND_PACKAGE( SDL_net REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}/
  ${Boost_INCLUDE_DIR}
  ${HOKUYO_URG_PATH}/include/urg

)

link_directories(
  ${Boost_LIBRARY_DIRS}
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
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  boost_log_setup
  boost_log
)

set(MESA_SWISSRANGER_SRC
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Logger.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/HokuyoURG.cpp
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/HokuyoURGConfiguration.cpp
)

ADD_LIBRARY(OODL_HokuyoURG
  ${MESA_SWISSRANGER_SRC}
)



ADD_EXECUTABLE(OODL_HokuyoURG_test
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/applications/Test.cpp
  ${MESA_SWISSRANGER_SRC}
)

ADD_EXECUTABLE(OODL_HokuyoURG_plot

  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/applications/plot_laserscanner_values.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/LaserScannerTools.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/gnuplot_i.cpp
  ${MESA_SWISSRANGER_SRC}
)

INSTALL(TARGETS OODL_HokuyoURG OODL_HokuyoURG_test OODL_HokuyoURG_plot RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
