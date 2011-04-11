#Searches system for "unicap" installation
# when successfully completed
# <NAME>_FOUND
# <NAME>_INCLUDE_DIRS or <NAME>_INCLUDES
# <NAME>_LIBRARIES or <NAME>_LIBRARIES or <NAME>_LIBS
# <NAME>_DEFINITIONS
# will be set and available for other cmake files


INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(unicap REQUIRED libunicap)

FIND_PATH(unicap_INCLUDE_DIR_NAME unicap.h PATHS $ENV{ROBOTPKG_BASE}/include /usr/local/include/unicap /usr/include/unicap HINTS  ${unicap_INCLUDE_DIRS})
FIND_LIBRARY(unicap_LIB_NAME unicap libunicap PATHS /usr/local/lib/libunicap /usr/lib/unicap $ENV{ROBOTPKG_BASE}/lib HINTS ${unicap_LIBRARY_DIRS})

IF(unicap_INCLUDE_DIR_NAME AND unicap_LIB_NAME)
    SET(unicap_FOUND TRUE)
    SET(unicap_LIBRARIES ${unicap_LIB_NAME})
    SET(unicap_INCLUDES  ${unicap_INCLUDE_DIR_NAME})
ENDIF(unicap_INCLUDE_DIR_NAME AND unicap_LIB_NAME)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(unicap DEFAULT_MSG unicap_INCLUDE_DIR_NAME unicap_LIB_NAME)
