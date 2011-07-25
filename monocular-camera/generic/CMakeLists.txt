CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

#SET(UNICAP_LIB /usr/local/lib)
#SET(COMPILE_C_FLAGS_DEBUG "-Wall -g")
#SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

SET(LIBNAME monocular-camera-generic)
SET(SOURCES 
  Image2dData.cpp 
  ImageFormat.cpp 
  CameraDeviceConfiguration.cpp 
  ColorExposureConfiguration.cpp 
  MonocularCameraConfiguration.cpp 
  )

INCLUDE_DIRECTORIES(/usr/local/include/unicap)
LINK_DIRECTORIES(${UNICAP_LIB} )

LINK_LIBRARIES(	unicap )

ADD_LIBRARY(${LIBNAME} SHARED ${SOURCES})




