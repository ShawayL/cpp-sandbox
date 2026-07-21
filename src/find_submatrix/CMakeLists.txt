# 定义可执行文件
add_executable(find_submatrix)
add_executable(cpp_sandbox::find_submatrix ALIAS find_submatrix)

# 设置项目c++标准
target_compile_features(find_submatrix PRIVATE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(find_submatrix PRIVATE)

# 设置项目属性
set_target_properties(find_submatrix PROPERTIES
  INSTALL_RPATH "$<$<PLATFORM_ID:Linux>:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}>"
)

# 设置vs项目文件夹
set_target_properties(find_submatrix PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(find_submatrix)

# 链接依赖库
target_link_libraries(find_submatrix
  PUBLIC
  PRIVATE
)
