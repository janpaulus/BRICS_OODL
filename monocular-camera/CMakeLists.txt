CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

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


INCLUDE_DIRECTORIES(
  /usr/local/include/unicap
#  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
  /usr/include/
  )

LINK_DIRECTORIES(
  ${UNICAP_LIB}
#  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
)

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(generic)
ADD_SUBDIRECTORY(application)


#this is for debugging
#SET(UNICAP_LIB_PATH_ALTERNATE_DEBUG /home/azamat/euprojects/brics/bricsToolchain/workspace/brics/BRICSWP2/BRICS_OODL/monocular-camera/unicap-0.9.5/libunicap/libs)
#LINK_DIRECTORIES( ${unicap_LIB_PATH_ALTERNATE_DEBUG} )


#INCLUDE_DIRECTORIES( ${unicap_INCLUDES} ${zmq_INCLUDES} ${SDL_INCLUDES} generic-monocular-camera/)
#LINK_DIRECTORIES( ${SDL_LIB_DIRS} ${ZMQ_LIB_DIRS} generic-monocular-camera/ )

#ADD_EXECUTABLE(testCamera ${SOURCES_1} )
#ADD_EXECUTABLE(testCameraZMQ ${SOURCES_2} )
#TARGET_LINK_LIBRARIES( testCamera ${SDL_LIBRARY} MonocularCameraCommon unicap )
#TARGET_LINK_LIBRARIES( testCameraZMQ ${SDL_LIBRARY} MonocularCameraCommon ${zmq_LIBRARIES})

