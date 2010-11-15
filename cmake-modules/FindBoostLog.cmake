# - Try to find boost::log
# Once done this will define
#
#  BOOSTLOG_FOUND - boost::log found
#  BOOSTLOG_INCLUDE_DIR - the boost::log include directory
#  BOOSTLOG_LIBRARY_DIR - boost::log lib directory
#

#STRING(COMPARE EQUAL ${CMAKE_BUILD_TYPE} "debug" ISDEBUGENABLED)

SET(BOOSTLOGLIB "libboost_log-mt.a")

FIND_PATH(BOOSTLOG_INCLUDE_DIR NAMES boost/log/core.hpp
  PATHS
  ${BOOST_LOG_PATH}/include/
  ${CMAKE_HOME_DIRECTORY}/../openrobots/include/
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
  ENV CPATH
  /usr/include/
  /usr/local/include/
  /opt/local/include/
  NO_DEFAULT_PATH
)

MARK_AS_ADVANCED("BOOSTLOG_INCLUDE_DIR: "${BOOSTLOG_INCLUDE_DIR})

FIND_LIBRARY(BOOSTLOG_LIBRARY_DIR NAMES ${BOOSTLOGLIB} "boostlogLibraries"
  PATHS
  ${CMAKE_HOME_DIRECTORY}/../openrobots/lib
  ${BOOST_LOG_PATH}/lib
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

#IF(NOT BOOSTLOG_LIBRARIES)
#  MESSAGE ("ERROR: Could not find boost::log library.")
#ENDIF(NOT BOOSTLOG_LIBRARIES)

IF(BOOSTLOG_INCLUDE_DIR AND BOOSTLOG_LIBRARY_DIR)
  SET(BOOSTLOG_FOUND TRUE)
ENDIF(BOOSTLOG_INCLUDE_DIR AND BOOSTLOG_LIBRARY_DIR)

# show the BOOSTLOG_INCLUDE_DIR and BOOSTLOG_LIBRARY_DIR variables only in the advanced view
IF(BOOSTLOG_FOUND)
  MARK_AS_ADVANCED(BOOSTLOG_INCLUDE_DIR BOOSTLOG_LIBRARY_DIR )
ENDIF(BOOSTLOG_FOUND)


