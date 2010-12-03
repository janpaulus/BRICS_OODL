PROJECT(BRICS_OODL)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

SET(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib) #static libraries
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin) #executables
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib) #dynamic libraries (plugins)

INCLUDE_DIRECTORIES(${CMAKE_HOME_DIRECTORY})

# find required and optional dependencies via Find<name>.cmake modules

#SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_ADDITIONAL_VERSIONS "1.39" "1.39.0" "1.40" "1.40.0" "1.41" "1.41.0" "1.42" "1.42.0")
FIND_PACKAGE(Boost REQUIRED COMPONENTS thread date_time filesystem system regex)
IF (Boost_FOUND)
  LINK_LIBRARIES(boost_thread boost_date_time boost_filesystem boost_system boost_regex)
MESSAGE(STATUS "SUCCESSFUL: Boost found")
ELSE (Boost_FOUND)
MESSAGE(STATUS "ERROR: Boost not found")
ENDIF (Boost_FOUND)

FIND_PACKAGE(BoostLog)
IF (BOOSTLOG_FOUND)
  INCLUDE_DIRECTORIES(${BOOSTLOG_INCLUDE_DIR})
  LINK_DIRECTORIES(${BOOSTLOG_LIBRARY_DIR})
  LINK_LIBRARIES(${BOOSTLOGLIB})
  ADD_DEFINITIONS(-DBOOST_LOG_FOUND)
MESSAGE(STATUS "SUCCESSFUL: boost::log found at "${BOOSTLOG_LIBRARY_DIR})
ELSE (BOOSTLOG_FOUND)
MESSAGE(STATUS "ERROR: boost::log not found")
ENDIF (BOOSTLOG_FOUND)


IF(DEFINED UNICAP_PATH)
  link_directories(${UNICAP_PATH}/lib)
  include_directories(${UNICAP_PATH}/include/unicap)
  MESSAGE(STATUS "UNICAP_PATH= ${UNICAP_PATH}")
ENDIF(DEFINED UNICAP_PATH)

IF(NOT DEFINED UNICAP_PATH)
  link_directories(${CMAKE_HOME_DIRECTORY}/../openrobots/lib)
  include_directories(${CMAKE_HOME_DIRECTORY}/../openrobots/include/unicap)
ENDIF(NOT DEFINED UNICAP_PATH)

SET(DOXYFILE_LATEX "NO")
SET(DOXYFILE_OUTPUT_DIR ${CMAKE_HOME_DIRECTORY}/doc)
include(UseDoxygen)


IF(NOT DEFINED SELECTED_DRIVER)
# add_subdirectory(hokuyo-urg)
# add_subdirectory(sick-lms-2xx)
# add_subdirectory(sick-ld)
# add_subdirectory(sick-s300)
   add_subdirectory(youbot)
# add_subdirectory(monocular-camera)
# add_subdirectory(mesa-swissranger)
# add_subdirectory(pmd-camcube)
ENDIF(NOT DEFINED SELECTED_DRIVER)


IF(DEFINED SELECTED_DRIVER)
  add_subdirectory(${SELECTED_DRIVER})
ENDIF(DEFINED SELECTED_DRIVER)