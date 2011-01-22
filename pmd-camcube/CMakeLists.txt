
SET( OODL_PMDCAMCUBE_VERSION 0.01 )

#IF(NOT DEFINED SICK_TOOLBOX_PATH)
#  SET( SICK_TOOLBOX_PATH /opt/ros/cturtle/stacks/laser_drivers/sicktoolbox/sicktoolbox CACHE PATH "Sick Toolbox path")
#ENDIF(NOT DEFINED SICK_TOOLBOX_PATH)

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

	boost_thread
	boost_date_time
	boost_system
	boost_filesystem
	boost_regex
	boost_log_setup
	boost_log
)

ADD_LIBRARY(OODL_PMDCamCube
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCamera.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCameraData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCameraConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/pmd-camcube/PMDCamCube.cpp
#  ${CMAKE_HOME_DIRECTORY}/pmd-camcube/PMDCamCubeConfiguration.cpp
)


ADD_EXECUTABLE(OODL_PMDCamCube_test
  ${CMAKE_HOME_DIRECTORY}/pmd-camcube/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/generic/Errors.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCamera.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCameraData.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-tof-camera/ToFCameraConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/pmd-camcube/PMDCamCube.cpp
#  ${CMAKE_HOME_DIRECTORY}/pmd-camcube/PMDCamCubeConfiguration.cpp
)



INSTALL(TARGETS OODL_PMDCamCube_test OODL_PMDCamCube RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

