CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
SET(SOURCES test.cpp MonocularCamera.cpp)


INCLUDE_DIRECTORIES(
/usr/local/include/unicap
../generic-monocular-camera/
)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
  ../generic-monocular-camera/
)

LINK_LIBRARIES(	
  unicap
  MonocularCameraConfiguration
)

ADD_EXECUTABLE(Test ${SOURCES}
)




