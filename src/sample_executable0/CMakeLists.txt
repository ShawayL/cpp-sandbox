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

# 定义内部头文件列表 自动收集位于internal文件夹中的头文件 这些头文件仅在本模块内部使用 在install的时候不会被安装
file(GLOB_RECURSE sample_executable0_HDRS_PRIVATE CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h"
)

# 定义源代码列表 自动收集当前目录下的源代码
file(GLOB_RECURSE sample_executable0_SRCS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 设置源码文件夹
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/internal PREFIX "Header Files/internal" FILES ${sample_executable0_HDRS_PRIVATE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${sample_executable0_SRCS})

# 设置项目源码
target_sources(sample_executable0
  PRIVATE
    ${sample_executable0_SRCS}
    ${sample_executable0_HDRS_PRIVATE}
)

# 设置私有头文件包含目录 这些包含目录仅对于本项目起作用
target_include_directories(sample_executable0
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

# 链接依赖库
target_link_libraries(sample_executable0
  PUBLIC
  PRIVATE
    cpp_sandbox::sample_library0
    cpp_sandbox::sample_library1
)
