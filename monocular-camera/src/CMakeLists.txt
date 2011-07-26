

SET(CORELIBNAME monocular-camera-core)
SET(GENERICLIBNAME  monocular-camera-generic)
SET(CORESOURCES MonocularCamera.cpp)
SET(GENERICSOURCES   
  Image2dData.cpp 
  ImageFormat.cpp 
  CameraDeviceConfiguration.cpp 
  ColorExposureConfiguration.cpp 
  MonocularCameraConfiguration.cpp 
  )


INCLUDE_DIRECTORIES(
  ${CMAKE_HOME_DIRECTORY}/monocular-camera/include
  $ENV(ROBOTPKG_BASE)/include
  /usr/local/include/unicap
  /usr/include/
  )

LINK_DIRECTORIES(
  $ENV(ROBOTPKG_BASE)/lib
  ${UNICAP_LIB}
)


ADD_LIBRARY(${CORELIBNAME} SHARED
  ${CORESOURCES}
)

ADD_LIBRARY(${GENERICLIBNAME} SHARED
  ${GENERICSOURCES}
)


TARGET_LINK_LIBRARIES(	
  ${GENERICLIBNAME}
  unicap
)

TARGET_LINK_LIBRARIES(	
  ${CORELIBNAME}
  ${GENERICLIBNAME}
)


INSTALL(TARGETS ${CORELIBNAME} ${GENERICLIBNAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)



