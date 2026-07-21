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

# 定义内部头文件列表 自动收集位于internal文件夹中的头文件 这些头文件仅在本模块内部使用 在install的时候不会被安装
file(GLOB_RECURSE gdal_test_HDRS_PRIVATE CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h"
)

# 定义源代码列表 自动收集当前目录下的源代码
file(GLOB_RECURSE gdal_test_SRCS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 设置源码文件夹
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/internal PREFIX "Header Files/internal" FILES ${gdal_test_HDRS_PRIVATE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${gdal_test_SRCS})

# 设置项目源码
target_sources(gdal_test
  PRIVATE
    ${gdal_test_SRCS}
    ${gdal_test_HDRS_PRIVATE}
)

# 设置私有头文件包含目录 这些包含目录仅对于本项目起作用
target_include_directories(gdal_test
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

# 链接依赖库
target_link_libraries(gdal_test
  PUBLIC
  PRIVATE
    gdal_util_library
    GDAL::GDAL
)
