CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

#SET(UNICAP_LIB /usr/local/lib)
SET(UNICAP_LIB /home/azamat/euprojects/brics/bricsToolchain/workspace/brics/BRICSWP2/BRICS_OODL/monocular-camera/unicap-0.9.5/libunicap/libs)

SET(SDL_LIB /usr/lib)
SET(COMPILE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -g")

INCLUDE_DIRECTORIES(
  /usr/local/include/unicap
#  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
  /usr/include/
  )

LINK_DIRECTORIES(
  ${UNICAP_LIB}
  ${CMAKE_HOME_DIRECTORY}/generic-monocular-camera/
)

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(generic)
ADD_SUBDIRECTORY(application)


