CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#Build Type
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE on)

SET(COMPILE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -g")

#FIND_PACKAGE(unicap REQUIRED)
#FIND_PACKAGE(zmq REQUIRED)
#FIND_PACKAGE(SDL REQUIRED)

#SET(UNICAP_LIB_DIRS ${unicap_LIBRARY_DIRS})
#SET(ZMQ_LIB_DIRS ${zmq_LIBRARY_DIRS})
#SET(SDL_LIB_DIRS ${SDL_LIBRARY_DIRS})

#SET(SOURCES_1 test/test.cpp)
#SET(SOURCES_2 test/testCameraZMQ.c)

SET(MONOCULARCAMERA_HEADERS
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/MonocularCamera.hpp
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/MonocularCameraConfiguration.hpp
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/ImageFormat.hpp
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/MonocularCameraDefinitions.hpp
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/Image2dData.hpp
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/CameraDeviceConfiguration.hpp
${CMAKE_HOME_DIRECTORY}/monocular-camera/include/ColorExposureConfiguration.hpp
)



INCLUDE_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/include
  $ENV(ROBOTPKG_BASE)/include
  /usr/local/include/unicap
  /usr/include/
  )

LINK_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/lib
  ${UNICAP_LIB}
)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(application)



MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    INSTALL(FILES ${HEADER} DESTINATION include/oodl/monocular-camera/)
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(MONOCULARCAMERA_HEADERS)

#this is for debugging
#SET(UNICAP_LIB_PATH_ALTERNATE_DEBUG /home/azamat/euprojects/brics/bricsToolchain/workspace/brics/BRICSWP2/BRICS_OODL/monocular-camera/unicap-0.9.5/libunicap/libs)
#LINK_DIRECTORIES( ${unicap_LIB_PATH_ALTERNATE_DEBUG} )


#INCLUDE_DIRECTORIES( ${unicap_INCLUDES} ${zmq_INCLUDES} ${SDL_INCLUDES} generic-monocular-camera/)
#LINK_DIRECTORIES( ${SDL_LIB_DIRS} ${ZMQ_LIB_DIRS} generic-monocular-camera/ )

#ADD_EXECUTABLE(testCamera ${SOURCES_1} )
#ADD_EXECUTABLE(testCameraZMQ ${SOURCES_2} )
#TARGET_LINK_LIBRARIES( testCamera ${SDL_LIBRARY} MonocularCameraCommon unicap )
#TARGET_LINK_LIBRARIES( testCameraZMQ ${SDL_LIBRARY} MonocularCameraCommon ${zmq_LIBRARIES})

