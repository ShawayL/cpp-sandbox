# 定义可执行文件
add_executable(find_submatrix)
add_executable(cpp_sandbox::find_submatrix ALIAS find_submatrix)

# 设置项目c++标准
target_compile_features(find_submatrix PRIVATE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(find_submatrix PRIVATE)

# 设置项目属性
set_target_properties(find_submatrix PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)
set_target_properties(find_submatrix PROPERTIES
  INSTALL_RPATH "$<$<PLATFORM_ID:Linux>:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}>"
)

# 设置vs项目文件夹
set_target_properties(find_submatrix PROPERTIES FOLDER ${PROJECT_NAME})

# 定义内部头文件列表 自动收集位于internal文件夹中的头文件 这些头文件仅在本模块内部使用 在install的时候不会被安装
file(GLOB_RECURSE find_submatrix_HDRS_PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h"
)

# 定义源代码列表 自动收集当前目录下的源代码
file(GLOB_RECURSE find_submatrix_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 设置源码文件夹
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/internal PREFIX "Header Files/internal" FILES ${find_submatrix_HDRS_PRIVATE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${find_submatrix_SRCS})

# 设置项目源码
target_sources(find_submatrix
  PRIVATE
    ${find_submatrix_SRCS}
    ${find_submatrix_HDRS_PRIVATE}
)

# 设置私有头文件包含目录 这些包含目录仅对于本项目起作用
target_include_directories(find_submatrix
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

# 链接依赖库
target_link_libraries(find_submatrix
  PUBLIC
  PRIVATE
)
