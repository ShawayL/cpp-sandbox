add_executable(gdal_test main.cpp)

add_executable(cpp_sandbox::gdal_test ALIAS gdal_test)

target_compile_features(gdal_test PRIVATE cxx_std_11)

target_link_libraries(
  gdal_test
  PRIVATE
  cpp_sandbox::gdal_util_library
  GDAL::GDAL
)
