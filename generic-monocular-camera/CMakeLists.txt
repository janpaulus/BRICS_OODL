CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
SET(SOURCES 
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/CameraDeviceConfiguration.cpp 
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/ColorExposureConfiguration.cpp
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/MonocularCameraConfiguration.cpp 
)

#SET(LIBNAME MonocularCameraConfiguration)
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

#ADD_LIBRARY(${LIBNAME} SHARED
#  ${SOURCES}
#)




