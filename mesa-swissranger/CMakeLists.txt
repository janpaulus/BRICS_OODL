
SET( OODL_MESASWISSRANGER_VERSION 0.01 )

#IF(NOT DEFINED MESA_SWISSRANGER_PATH)
#  SET( MESA_SWISSRANGER_PATH /opt/ros/cturtle/stacks/laser_drivers/sicktoolbox/sicktoolbox CACHE PATH "Mesa Swissranger path")
#ENDIF(NOT DEFINED MESA_SWISSRANGER_PATH)

FIND_PACKAGE( Boost REQUIRED )


include_directories(
  ${CMAKE_HOME_DIRECTORY}/
  ${Boost_INCLUDE_DIR}
#  ${SICK_TOOLBOX_PATH}/include
)

link_directories(
  ${Boost_LIBRARY_DIRS}
#  ${SICK_TOOLBOX_PATH}/lib
)

link_libraries(	
  mesasr
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
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCamera.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCameraData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCameraConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/mesa-swissranger/MesaSwissRanger.cpp
#  ${CMAKE_HOME_DIRECTORY}/mesa-swissranger/MesaSwissRangerConfiguration.cpp
)

ADD_LIBRARY(OODL_MesaSwissRanger
  ${MESA_SWISSRANGER_SRC}
)


ADD_EXECUTABLE(OODL_MesaSwissRanger_test
  ${CMAKE_HOME_DIRECTORY}/mesa-swissranger/applications/Test.cpp
  ${MESA_SWISSRANGER_SRC}
)

INSTALL(TARGETS OODL_MesaSwissRanger_test OODL_MesaSwissRanger RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

