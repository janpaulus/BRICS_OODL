CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
#SET(CC gcc)
#SET(CXX g++)

SET(SOURCES MonocularCameraConfiguration.cpp)
SET(LIBNAME MonocularCameraConfiguration)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
)

LINK_LIBRARIES(	
  unicap
)

INCLUDE_DIRECTORIES(
/usr/local/include/unicap
)


ADD_LIBRARY(${LIBNAME} SHARED
  ${SOURCES}
)




