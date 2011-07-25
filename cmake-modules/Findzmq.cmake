#Searches system for "unicap" installation
# when successfully completed
# <NAME>_FOUND
# <NAME>_INCLUDE_DIRS or <NAME>_INCLUDES
# <NAME>_LIBRARIES or <NAME>_LIBRARIES or <NAME>_LIBS
# <NAME>_DEFINITIONS
# will be set and available for other cmake files


INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(zmq REQUIRED libzmq)

FIND_PATH(zmq_INCLUDE_DIR_NAME zmq.h PATHS $ENV{ROBOTPKG_BASE}/include /usr/local/include/zmq /usr/local/include/ HINTS  ${zmq_INCLUDE_DIRS})
FIND_LIBRARY(zmq_LIB_NAME zmq libzmq PATHS /usr/local/lib/ /usr/lib/ $ENV{ROBOTPKG_BASE}/lib HINTS ${zmq_LIBRARY_DIRS})

IF(zmq_INCLUDE_DIR_NAME AND zmq_LIB_NAME)
    SET(zmq_FOUND TRUE)
    SET(zmq_LIBRARIES ${zmq_LIB_NAME})
    SET(zmq_INCLUDES  ${zmq_INCLUDE_DIR_NAME})
ENDIF(zmq_INCLUDE_DIR_NAME AND zmq_LIB_NAME)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(zmq DEFAULT_MSG zmq_INCLUDE_DIR_NAME zmq_LIB_NAME)

