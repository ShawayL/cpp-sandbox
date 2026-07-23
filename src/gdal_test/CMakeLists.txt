# 定义可执行文件
add_executable(gdal_test)
add_executable(cpp_sandbox::gdal_test ALIAS gdal_test)

# 设置项目c++标准
target_compile_features(gdal_test PRIVATE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(gdal_test PRIVATE)

# 设置项目属性
set_target_properties(gdal_test PROPERTIES
  INSTALL_RPATH "$<$<PLATFORM_ID:Linux>:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}>"
)

# 设置vs项目文件夹
set_target_properties(gdal_test PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(gdal_test)

# 链接依赖库
target_link_libraries(gdal_test
  PUBLIC
  PRIVATE
    gdal_util_library
    GDAL::GDAL
)

cpp_sandbox_install_target(gdal_test)
