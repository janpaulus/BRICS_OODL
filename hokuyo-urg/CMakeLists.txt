
SET( OODL_HokuyoURG_VERSION 0.01 )


IF(NOT DEFINED HOKUYO_URG_PATH)
  SET( HOKUYO_URG_PATH $ENV{ROBOTPKG_BASE}/ CACHE PATH "Hokuyo URG path")
ENDIF(NOT DEFINED HOKUYO_URG_PATH)

FIND_PACKAGE( Boost REQUIRED )
#FIND_PACKAGE( SDL REQUIRED )
#FIND_PACKAGE( SDL_net REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}/
  ${CMAKE_HOME_DIRECTORY}/generic/
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/
  ${Boost_INCLUDE_DIR}
  ${HOKUYO_URG_PATH}/include/urg

)

link_directories(
  ${Boost_LIBRARY_DIRS}
  ${HOKUYO_URG_PATH}/lib
)

#link_libraries(	
 # urg
 # urg_common
 # urg_connection
 # urg_connection_sdl
 # urg_coordinate
#  urg_geometry
#  urg_monitor
#  urg_system
 #  libc_urg.a
 #  libc_urg_connection.a
 #  libc_urg_system.a
#  SDL
#  boost_thread
#  boost_date_time
#  boost_system
#  boost_filesystem
#  boost_regex
  #boost_log_setup
#  boost_log-mt
#)

set(HOKUYO_URG_SRC
  ../generic/Errors.cpp
  ../generic/Logger.cpp
  ../generic-laser-scanner/LaserScanner.cpp
  ../generic-laser-scanner/LaserScannerData.cpp
  ../generic-laser-scanner/LaserScannerConfiguration.cpp
  ../generic-laser-scanner/LaserScannerDataWithIntensities.cpp
  HokuyoURG.cpp
  HokuyoURGConfiguration.cpp
)

SET(HOKUYO_URG_HEADERS
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/HokuyoURG.hpp
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/HokuyoURGConfiguration.hpp

  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScanner.hpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerConfiguration.hpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerData.hpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/LaserScannerDataWithIntensities.hpp

  ${CMAKE_HOME_DIRECTORY}/generic/Errors.hpp
  ${CMAKE_HOME_DIRECTORY}/generic/Exceptions.hpp
  ${CMAKE_HOME_DIRECTORY}/generic/Logger.hpp
  ${CMAKE_HOME_DIRECTORY}/generic/Time.hpp
  ${CMAKE_HOME_DIRECTORY}/generic/Units.hpp
)


ADD_LIBRARY(OODL_HokuyoURG SHARED  ${HOKUYO_URG_SRC}
)

TARGET_LINK_LIBRARIES(OODL_HokuyoURG 
  urg
  urg_common
  urg_connection
  urg_connection_sdl
  urg_coordinate
  urg_geometry
  urg_monitor
  urg_system
 #  libc_urg.a
 #  libc_urg_connection.a
 #  libc_urg_system.a
  SDL
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  #boost_log_setup
  boost_log-mt)

ADD_EXECUTABLE(OODL_HokuyoURG_test
  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/applications/Test.cpp
  ${HOKUYO_URG_SRC}
)


TARGET_LINK_LIBRARIES(OODL_HokuyoURG_test 
  urg
  urg_common
  urg_connection
  urg_connection_sdl
  urg_coordinate
  urg_geometry
  urg_monitor
  urg_system
 #  libc_urg.a
 #  libc_urg_connection.a
 #  libc_urg_system.a
  SDL
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  #boost_log_setup
  boost_log-mt)



ADD_EXECUTABLE(OODL_HokuyoURG_plot

  ${CMAKE_HOME_DIRECTORY}/hokuyo-urg/applications/plot_laserscanner_values.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/LaserScannerTools.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-laser-scanner/applications/gnuplot_i.cpp
  ${HOKUYO_URG_SRC}
)

TARGET_LINK_LIBRARIES(OODL_HokuyoURG_plot 
  urg
  urg_common
  urg_connection
  urg_connection_sdl
  urg_coordinate
  urg_geometry
  urg_monitor
  urg_system
 #  libc_urg.a
 #  libc_urg_connection.a
 #  libc_urg_system.a
  SDL
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  #boost_log_setup
  boost_log-mt)



MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    INSTALL(FILES ${HEADER} DESTINATION include/oodl-hokuyoURG/)
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(HOKUYO_URG_HEADERS)
INSTALL(TARGETS OODL_HokuyoURG OODL_HokuyoURG_test OODL_HokuyoURG_plot RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
