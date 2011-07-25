CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(LIBNAME monocular-camera-core)
SET(SOURCES MonocularCamera.cpp)


INCLUDE_DIRECTORIES(
  /usr/local/include/unicap
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic/
)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic/
)

LINK_LIBRARIES(	
  unicap
  monocular-camera-generic
)

ADD_LIBRARY(${LIBNAME} SHARED
  ${SOURCES}
)




