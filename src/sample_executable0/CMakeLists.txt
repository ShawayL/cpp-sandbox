add_executable(sample_executable0 main.cpp)

add_executable(cpp_sandbox::sample_executable0 ALIAS sample_executable0)

target_compile_features(sample_executable0 PRIVATE cxx_std_11)

target_link_libraries(
  sample_executable0
  PRIVATE cpp_sandbox::sample_library0
          cpp_sandbox::sample_library1)
