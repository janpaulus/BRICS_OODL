
SET(EXECUTABLE1 test-monocamera-viewer)
SET(EXECUTABLE2 test-monocamera-console)

INCLUDE_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/include
)

LINK_DIRECTORIES(
  ${SDL_LIB}
  ${CMAKE_HOME_DIRECTORY}/lib
)

ADD_EXECUTABLE(${EXECUTABLE1} test-viewer.cpp)
TARGET_LINK_LIBRARIES(${EXECUTABLE1}	
  monocular-camera-generic
  monocular-camera-core
  SDL
)

ADD_EXECUTABLE(${EXECUTABLE2} test-console.cpp)
TARGET_LINK_LIBRARIES(${EXECUTABLE2}	
  monocular-camera-generic
  monocular-camera-core
)


INSTALL(TARGETS ${EXECUTABLE1}  ${EXECUTABLE2} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)



