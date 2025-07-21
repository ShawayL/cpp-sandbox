enable_testing()
include(CTest)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)

add_executable(tests tests.cpp)
target_link_libraries(
  tests
  PRIVATE cpp_sandbox::sample_library0
          cpp_sandbox::sample_library1
          Catch2::Catch2WithMain)

catch_discover_tests(tests)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET tests
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
    COMMAND_EXPAND_LISTS)
endif()
