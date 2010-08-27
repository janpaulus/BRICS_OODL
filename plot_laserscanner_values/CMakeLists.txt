#PROJECT(OODL_SickLMS2xx)

#cmake_minimum_required(VERSION 2.4)

SET( OODL_plot_laserscanner_values_VERSION 0.01 )

#SET( PROJ_SOURCE_DIR ${OODL_SickLMS2xx_SOURCE_DIR} )
#SET( PROJ_BINARY_DIR ${OODL_SickLMS2xx_BINARY_DIR} )

#SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin CACHE PATH "executable output path" )


FIND_PACKAGE( Boost REQUIRED )


include_directories(
  ${CMAKE_HOME_DIRECTORY}/generic/
  ${Boost_INCLUDE_DIR}
  ${CMAKE_HOME_DIRECTORY}/sick-s300/

)

link_directories(
  ${Boost_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}/lib
  ${CMAKE_HOME_DIRECTORY}/sick-s300/

)

link_libraries(	
  OODL_SickS300.a
)

ADD_EXECUTABLE(plot_laserscanner_values
main.cpp
gnuplot_i.cpp

)

INSTALL(TARGETS plot_laserscanner_values RUNTIME DESTINATION bin )
