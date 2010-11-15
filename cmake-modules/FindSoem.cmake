# - Try to find soem
# Once done this will define
#
#  SOEM_FOUND - soem found
#  SOEM_INCLUDE_DIR - the soem include directory
#  SOEM_LIBRARY_DIR - soem lib directory
#

SET(SOEMLIB "libsoem.a")

FIND_PATH(SOEM_INCLUDE_DIR NAMES ethercatmain.h
  PATHS
  ${SOEM_PATH}/include/soem/src
  ${ROBOTPKG_INSTALL_PATH}/include/soem/src
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
  ENV CPATH
  /usr/include/
  /usr/include/soem/src
  /usr/local/include/
  /usr/local/include/soem/src
  /opt/local/include/
  /opt/local/include/soem/src
  NO_DEFAULT_PATH
)

#MARK_AS_ADVANCED("SOEM_INCLUDE_DIR: "${SOEM_INCLUDE_DIR})

FIND_LIBRARY(SOEM_LIBRARY_DIR NAMES ${SOEMLIB} "SoemLibraries"
  PATHS
  ${CMAKE_HOME_DIRECTORY}/../openrobots/lib
  ${SOEM_PATH}/lib
  ${PROJECT_BINARY_DIR}/lib
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/libraries
  ENV LD_LIBRARY_PATH
  ENV LIBRARY_PATH
  /usr/lib
  /usr/local/lib
  /opt/local/lib
  NO_DEFAULT_PATH
)

IF(NOT SOEM_LIBRARIES)
  MESSAGE ("ERROR: Could not find Soem.")
ENDIF(NOT SOEM_LIBRARIES)

IF(SOEM_INCLUDE_DIR AND SOEM_LIBRARY_DIR)
  SET(SOEM_FOUND TRUE)
ENDIF(SOEM_INCLUDE_DIR AND SOEM_LIBRARY_DIR)

# show the SOEM_INCLUDE_DIR and SOEM_LIBRARY_DIR variables only in the advanced view
IF(SOEM_FOUND)
  MARK_AS_ADVANCED(SOEM_INCLUDE_DIR SOEM_LIBRARY_DIR )
ENDIF(SOEM_FOUND)


