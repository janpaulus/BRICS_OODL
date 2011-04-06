CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

#Build Type
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE on)

#Library to build
SET(LIBNAME MonocularCameraCommon)

#Compiler flags
SET(COMPILE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

#Paths variables
FIND_PACKAGE(unicap REQUIRED)

SET(UNICAP_LIB ${unicap_LIBRARIES})
SET(UNICAP_INC_PATH ${unicap_INCLUDES})
SET(CMAKE_INCLUDE_CURRENT_DIR ON )

SET(SOURCES
    MonocularCamera.cpp
    Image2dData.cpp
    ImageFormat.cpp
    CameraDeviceConfiguration.cpp
    ColorExposureConfiguration.cpp
    MonocularCameraConfiguration.cpp
    MonocularCameraProperty.cpp
    MonocularCameraPropertyFactory.cpp
   )

INCLUDE_DIRECTORIES( ${UNICAP_INC_PATH} )
LINK_DIRECTORIES( ${unicap_LIBRARY_DIRS} ) #//this is provided by pkgconfig module

ADD_LIBRARY(${LIBNAME} SHARED ${SOURCES} )
TARGET_LINK_LIBRARIES( ${LIBNAME} ${UNICAP_LIB} )



