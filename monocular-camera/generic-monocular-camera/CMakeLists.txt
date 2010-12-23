CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
SET(LIBNAME MonocularCameraConfiguration)
SET(SOURCES 
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/Image2dData.cpp 
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/ImageFormat.cpp 
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/CameraDeviceConfiguration.cpp 
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/ColorExposureConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/MonocularCameraConfiguration.cpp 
#${CMAKE_HOME_DIRECTORY}/monocular-camera/generic-monocular-camera/MonocularCameraDefinitions.cpp 
)



SET(COMPILE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")



INCLUDE_DIRECTORIES(
/usr/local/include/unicap
)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
)

LINK_LIBRARIES(	
  unicap
)

ADD_LIBRARY(${LIBNAME} SHARED
  ${SOURCES}
)




