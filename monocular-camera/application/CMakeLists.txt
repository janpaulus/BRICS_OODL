
SET(EXECUTABLE1 test-monocamera-viewer)
SET(EXECUTABLE2 test-monocamera-console)

INCLUDE_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic/
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/core/
)

LINK_DIRECTORIES(
  ${SDL_LIB}
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/generic/
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/core/
)

LINK_LIBRARIES(	
  monocular-camera-generic
  monocular-camera-core
  SDL
)

ADD_EXECUTABLE(${EXECUTABLE1} test-viewer.cpp)
ADD_EXECUTABLE(${EXECUTABLE2} test-console.cpp)




