PROJECT(BRICS_OODL)


CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS_DEBUG "-Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")


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

 # add_subdirectory(hokuyo-urg)
 # add_subdirectory(sick-lms-2xx)
 # add_subdirectory(sick-ld)
#  add_subdirectory(sick-s300)
 ADD_SUBDIRECTORY(monocular-camera)
 ADD_SUBDIRECTORY(generic-monocular-camera)
#add_subdirectory(sick-s300-test)

 # add_subdirectory(hokuyourg)
 # add_subdirectory(sicklms2xx)
 # add_subdirectory(sickld)
  add_subdirectory(sicks300)
#  add_subdirectory(monocularcamera)
#add_subdirectory(sicks300test)

  
 # add_subdirectory(mesaswissranger)
 # add_subdirectory(pmdcamcube)
ENDIF(NOT DEFINED SELECTED_DRIVER)


IF(DEFINED SELECTED_DRIVER)
  add_subdirectory(${SELECTED_DRIVER})
ENDIF(DEFINED SELECTED_DRIVER)
