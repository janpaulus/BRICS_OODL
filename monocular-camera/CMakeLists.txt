CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(UNICAP_LIB /usr/local/lib)
SET(SOURCES test.cpp MonocularCamera.cpp)



SET(SOURCES 
test.cpp 
MonocularCamera.cpp
${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/MonocularCameraConfiguration.cpp
)

INCLUDE_DIRECTORIES(
/usr/local/include/unicap
${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
)

LINK_LIBRARIES(	
  unicap
  MonocularCameraConfiguration
)

ADD_EXECUTABLE(Test ${SOURCES}
)

INSTALL(TARGETS Test RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
