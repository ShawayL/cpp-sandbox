add_executable(tests tests.cpp)

set_target_properties(tests PROPERTIES FOLDER tests)

target_link_libraries(
  tests
  PRIVATE
    cpp_sandbox::sample_library0
    cpp_sandbox::sample_library1
    cpp_sandbox::string_converter
    Catch2::Catch2WithMain
)

catch_discover_tests(tests)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET tests
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests>
      $<TARGET_FILE_DIR:tests>
    COMMAND_EXPAND_LISTS
  )
endif()
