PROJECT(BRICS_OODL)

cmake_minimum_required(VERSION 2.4)

IF(NOT DEFINED SELECTED_DRIVER)
  add_subdirectory(hokuyo-urg)
#  add_subdirectory(sick-lms-2xx)
#  add_subdirectory(sick-ld)
#  add_subdirectory(sick-s300)
ENDIF(NOT DEFINED SELECTED_DRIVER)

IF(DEFINED SELECTED_DRIVER)
  add_subdirectory(${SELECTED_DRIVER})
ENDIF(DEFINED SELECTED_DRIVER)
