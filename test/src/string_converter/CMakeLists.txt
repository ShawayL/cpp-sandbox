add_executable(test_StringConverter test_StringConverter.cpp)

set_target_properties(test_StringConverter PROPERTIES FOLDER ${PROJECT_NAME}/tests)

target_link_libraries(test_StringConverter
  PRIVATE
    cpp_sandbox::string_converter
    GTest::gtest_main
)

gtest_discover_tests(test_StringConverter)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET test_StringConverter
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test_StringConverter>
      $<TARGET_FILE_DIR:test_StringConverter>
    COMMAND_EXPAND_LISTS
  )
endif()
