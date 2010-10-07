SET(UNICAP_LIB /usr/local/lib)
#SET(CC gcc)
#SET(CXX g++)
SET(SOURCES MonocularCameraConfiguration.cpp)
SET(LIBNAME MonocularCameraConfiguation)

LINK_DIRECTORIES(
  ${UNICAP_LIB}
)

LINK_LIBRARIES(	
  unicap
)

INCLUDE_DIRECTORIES(
/usr/local/include/unicap
)


ADD_LIBRARY(${LIBNAME}
  ${SOURCES}
)


INSTALL()

