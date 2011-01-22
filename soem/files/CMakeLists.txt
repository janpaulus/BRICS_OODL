cmake_minimum_required(VERSION 2.4.6)




#set the default path for built executables to the "bin" directory
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)




ADD_LIBRARY(soem 
  src/ethercatbase.c 
  src/ethercatcoe.c 
  src/ethercatconfig.c 
  src/ethercatfoe.c 
  src/ethercatsoe.c 
  src/ethercatmain.c 
  src/ethercatprint.c 
  src/nicdrv.c 
  src/ethercatdc.c
) 

link_libraries( pthread)

include_directories(
  src
)

SET(SOEM_HEADERS
  src/ethercatbase.h
  src/ethercatcoe.h
  src/ethercatconfig.h
  src/ethercatconfiglist.h
  src/ethercatdc.h
  src/ethercatfoe.h 
  src/ethercatmain.h 
  src/ethercatprint.h 
  src/ethercatsoe.h 
  src/ethercattype.h
  src/nicdrv.h 
) 

MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
    INSTALL(FILES ${HEADER} DESTINATION include/soem/${DIR})
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(SOEM_HEADERS)

INSTALL(TARGETS soem LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

