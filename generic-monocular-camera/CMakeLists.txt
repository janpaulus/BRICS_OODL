CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
SET(SOURCES MonocularCameraConfiguration.cpp)
SET(LIBNAME MonocularCameraConfiguration)



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




