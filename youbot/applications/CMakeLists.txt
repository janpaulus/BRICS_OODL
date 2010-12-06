
ADD_EXECUTABLE(YouBot_test
  ${CMAKE_HOME_DIRECTORY}/youbot/applications/Test.cpp
)

ADD_EXECUTABLE(YouBot_KeyboardRemoteControl
  ${CMAKE_HOME_DIRECTORY}/youbot/applications/KeyboardRemoteControl.cpp
)

target_link_libraries(YouBot_test OODL_YouBot)
target_link_libraries(YouBot_KeyboardRemoteControl OODL_YouBot ncurses)

INSTALL(TARGETS YouBot_test YouBot_KeyboardRemoteControl RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

