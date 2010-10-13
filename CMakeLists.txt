PROJECT(BRICS_OODL)

cmake_minimum_required(VERSION 2.4)



IF(DEFINED BOOST_LOG_PATH)
  link_directories(${BOOST_LOG_PATH}/lib)
  include_directories(${BOOST_LOG_PATH}/include)
  MESSAGE(STATUS "BOOST_LOG_PATH= ${BOOST_LOG_PATH}")
ENDIF(DEFINED BOOST_LOG_PATH)

IF(NOT DEFINED BOOST_LOG_PATH)
  link_directories(${CMAKE_HOME_DIRECTORY}/../openrobots/lib)
  include_directories(${CMAKE_HOME_DIRECTORY}/../openrobots/include)
ENDIF(NOT DEFINED BOOST_LOG_PATH)



IF(NOT DEFINED SELECTED_DRIVER)
  add_subdirectory(hokuyo-urg)
  add_subdirectory(sick-lms-2xx)
  add_subdirectory(sick-ld)
  add_subdirectory(sick-s300)
#  add_subdirectory(monocular-camera)
  
 # add_subdirectory(mesa-swissranger)
 # add_subdirectory(pmd-camcube)
ENDIF(NOT DEFINED SELECTED_DRIVER)


IF(DEFINED SELECTED_DRIVER)
  add_subdirectory(${SELECTED_DRIVER})
ENDIF(DEFINED SELECTED_DRIVER)



