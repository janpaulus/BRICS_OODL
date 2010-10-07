
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)

#SET(CC gcc)
#SET(CXX g++)

SET(SOURCES test.cpp MonocularCamera.cpp)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
  ../generic-monocular-camera/
)

LINK_LIBRARIES(	
  unicap
  MonocularCameraConfiguration
)

INCLUDE_DIRECTORIES(
/usr/local/include/unicap
../generic-monocular-camera/
)


ADD_EXECUTABLE(Test ${SOURCES}
)




