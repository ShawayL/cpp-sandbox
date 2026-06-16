add_executable(test_sample_library0 test_sample_library0.cpp)

set_target_properties(test_sample_library0 PROPERTIES FOLDER ${PROJECT_NAME}/tests)

target_link_libraries(test_sample_library0
  PRIVATE
    cpp_sandbox::sample_library0
    GTest::gtest_main
)

gtest_discover_tests(test_sample_library0)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET test_sample_library0
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test_sample_library0>
      $<TARGET_FILE_DIR:test_sample_library0>
    COMMAND_EXPAND_LISTS
  )
endif()
