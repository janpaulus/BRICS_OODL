
SET( SickS300_Driver_VERSION 0.01 )


FIND_PACKAGE( Boost REQUIRED )

include_directories(
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/base
  ${Boost_INCLUDE_DIR}
)

link_directories(
  ${Boost_LIBRARY_DIRS}

)

link_libraries(
  boost_thread
  boost_date_time
  boost_system
  boost_filesystem
  boost_regex
  boost_log_setup
  boost_log
)

ADD_LIBRARY(SickS300_driver

  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/SickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/SickS300BufferMonitor.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/SickS300Message.cpp
)

ADD_EXECUTABLE(SickS300_driver_test
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/applications/Test.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/SickS300.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/SickS300BufferMonitor.cpp
  ${CMAKE_HOME_DIRECTORY}/sick-s300-driver/SickS300Message.cpp
)

INSTALL(TARGETS SickS300_driver_test SickS300_driver RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

