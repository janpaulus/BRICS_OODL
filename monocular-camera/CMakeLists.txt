CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
SET(SDL_LIB /usr/lib)
SET(COMPILE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -g")
SET(SOURCES 
    ${CMAKE_HOME_DIRECTORY}/monocular-camera/test.cpp 
	${CMAKE_HOME_DIRECTORY}/monocular-camera/MonocularCamera.cpp
	${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/CameraDeviceConfiguration.cpp 
	${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/ColorExposureConfiguration.cpp
	${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/MonocularCameraConfiguration.cpp
	${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/ImageFormat.cpp
	${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/Image2dData.cpp
)


INCLUDE_DIRECTORIES(
  /usr/local/include/unicap
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
  /usr/include/
  )

LINK_DIRECTORIES(
  ${UNICAP_LIB}
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
)

LINK_LIBRARIES(	
  unicap
  SDL
#  MonocularCameraConfiguration
)

ADD_EXECUTABLE(Test ${SOURCES}
)

ADD_SUBDIRECTORY(generic-monocular-camera)

INSTALL(TARGETS Test RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
