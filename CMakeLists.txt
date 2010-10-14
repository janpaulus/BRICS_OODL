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
