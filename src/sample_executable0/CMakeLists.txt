# 定义可执行文件
add_executable(sample_executable0)
add_executable(cpp_sandbox::sample_executable0 ALIAS sample_executable0)

# 设置项目c++标准
target_compile_features(sample_executable0 PRIVATE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(sample_executable0 PRIVATE)

# 设置项目属性
set_target_properties(sample_executable0 PROPERTIES
  INSTALL_RPATH "$<$<PLATFORM_ID:Linux>:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}>"
)

# 设置vs项目文件夹
set_target_properties(sample_executable0 PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(sample_executable0)

# 链接依赖库
target_link_libraries(sample_executable0
  PUBLIC
  PRIVATE
    cpp_sandbox::sample_library0
    cpp_sandbox::sample_library1
)

cpp_sandbox_install_target(sample_executable0)
