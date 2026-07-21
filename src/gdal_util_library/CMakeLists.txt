# 定义动态库
add_library(gdal_util_library)
add_library(cpp_sandbox::gdal_util_library ALIAS gdal_util_library)

# 设置项目c++标准
target_compile_features(gdal_util_library PRIVATE cxx_std_11)
target_compile_features(gdal_util_library INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(gdal_util_library PUBLIC PRIVATE)

# 设置项目属性
set_target_properties(gdal_util_library PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(gdal_util_library PROPERTIES FOLDER ${PROJECT_NAME})

# 生成定义了导出宏的头文件
include(GenerateExportHeader)
generate_export_header(gdal_util_library EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/gdal_util_library/gdal_util_library_export.hpp)

# 定义公开头文件所在的包含目录
set(gdal_util_library_HDRS_DIRS
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
)

# 定义公开头文件列表 自动在指定目录下收集头文件 这些头文件在install的时候会被安装到头文件目录
file(GLOB_RECURSE gdal_util_library_HDRS
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/gdal_util_library/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/gdal_util_library/*.h"
)
file(GLOB_RECURSE gdal_util_library_HDRS_GENERATE
  "${PROJECT_BINARY_DIR}/include/cpp_sandbox/gdal_util_library/*.hpp"
  "${PROJECT_BINARY_DIR}/include/cpp_sandbox/gdal_util_library/*.h"
)

# 定义内部头文件列表 自动收集位于detail文件夹中的头文件 这些头文件可以被本项目内所有模块使用 但在install的时候不会被安装
file(GLOB_RECURSE gdal_util_library_HDRS_DETAIL
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/gdal_util_library/detail/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/gdal_util_library/detail/*.h"
)

# 定义内部头文件列表 自动收集位于internal文件夹中的头文件 这些头文件仅在本模块内部使用 在install的时候不会被安装
file(GLOB_RECURSE gdal_util_library_HDRS_PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h"
)

# 定义源代码列表 自动收集当前目录下的源代码
file(GLOB_RECURSE gdal_util_library_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 设置源码文件夹 方便在vs中查看
if(WIN32 AND MSVC)
  source_group(TREE ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/gdal_util_library PREFIX "Header Files/cpp_sandbox/gdal_util_library" FILES ${gdal_util_library_HDRS})
  source_group(TREE ${PROJECT_BINARY_DIR}/include/cpp_sandbox/gdal_util_library PREFIX "Header Files/cpp_sandbox/gdal_util_library" FILES ${gdal_util_library_HDRS_GENERATE})
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/internal PREFIX "Header Files/internal" FILES ${gdal_util_library_HDRS_PRIVATE})
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${gdal_util_library_SRCS})
endif()

# 设置项目源码
target_sources(gdal_util_library
  PRIVATE
    ${gdal_util_library_SRCS}
    ${gdal_util_library_HDRS_PRIVATE}
    ${gdal_util_library_HDRS}
    ${gdal_util_library_HDRS_GENERATE}
)

# 设置文件集headers headers自动收集gdal_util_library_HDRS列表中的头文件
# 在install时会安装此文件集
list(REMOVE_ITEM gdal_util_library_HDRS ${gdal_util_library_HDRS_DETAIL})
target_sources(gdal_util_library
  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
    ${gdal_util_library_HDRS_DIRS}
    FILES
    ${gdal_util_library_HDRS}
    ${gdal_util_library_HDRS_GENERATE}
)

# 启用头文件验证
set_target_properties(gdal_util_library
  PROPERTIES
    VERIFY_INTERFACE_HEADER_SETS ON
)

# 设置公开头文件包含目录 这些包含目录不仅对本项目起作用 对于使用本项目的其他项目也起作用
target_include_directories(gdal_util_library
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# 设置私有头文件包含目录 这些包含目录仅对于本项目起作用
target_include_directories(gdal_util_library
  PUBLIC
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

# 链接依赖库
target_link_libraries(gdal_util_library
  PUBLIC
  PRIVATE
    GDAL::GDAL
)
