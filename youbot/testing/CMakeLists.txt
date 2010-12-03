
ADD_EXECUTABLE(test_suite
  ${CMAKE_HOME_DIRECTORY}/youbot/testing/TestSuite.cpp
)


target_link_libraries(test_suite OODL_YouBot)

INSTALL(TARGETS test_suite RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

