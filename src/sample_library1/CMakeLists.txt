# 定义动态库
add_library(sample_library1)
add_library(cpp_sandbox::sample_library1 ALIAS sample_library1)

# 设置项目c++标准
target_compile_features(sample_library1 PRIVATE cxx_std_11)
target_compile_features(sample_library1 INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(sample_library1 PUBLIC $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:SAMPLE_LIBRARY1_STATIC_DEFINE> PRIVATE)

# 设置项目属性
set_target_properties(sample_library1 PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(sample_library1 PROPERTIES FOLDER ${PROJECT_NAME})

# 生成定义了导出宏的头文件
include(GenerateExportHeader)
generate_export_header(sample_library1 EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library1/sample_library1_export.hpp)

# 定义公开头文件所在的包含目录
set(sample_library1_HDRS_DIRS
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
)

# 定义公开头文件列表 自动在指定目录下收集头文件 这些头文件在install的时候会被安装到头文件目录
file(GLOB_RECURSE sample_library1_HDRS CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library1/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library1/*.h"
)
file(GLOB_RECURSE sample_library1_HDRS_GENERATE CONFIGURE_DEPENDS
  "${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library1/*.hpp"
  "${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library1/*.h"
)

# 定义内部头文件列表 自动收集位于detail文件夹中的头文件 这些头文件可以被本项目内所有模块使用 但在install的时候不会被安装
file(GLOB_RECURSE sample_library1_HDRS_DETAIL CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library1/detail/*.hpp"
  "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library1/detail/*.h"
)

# 定义内部头文件列表 自动收集位于internal文件夹中的头文件 这些头文件仅在本模块内部使用 在install的时候不会被安装
file(GLOB_RECURSE sample_library1_HDRS_PRIVATE CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h"
)

# 定义源代码列表 自动收集当前目录下的源代码
file(GLOB_RECURSE sample_library1_SRCS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 设置源码文件夹
source_group(TREE ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library1 PREFIX "Header Files/cpp_sandbox/sample_library1" FILES ${sample_library1_HDRS})
source_group(TREE ${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library1 PREFIX "Header Files/cpp_sandbox/sample_library1" FILES ${sample_library1_HDRS_GENERATE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/internal PREFIX "Header Files/internal" FILES ${sample_library1_HDRS_PRIVATE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Source Files" FILES ${sample_library1_SRCS})

# 设置项目源码
target_sources(sample_library1
  PRIVATE
    ${sample_library1_SRCS}
    ${sample_library1_HDRS_PRIVATE}
    ${sample_library1_HDRS}
    ${sample_library1_HDRS_GENERATE}
)

# 设置文件集headers headers自动收集sample_library1_HDRS列表中的头文件
# 在install时会安装此文件集
list(REMOVE_ITEM sample_library1_HDRS ${sample_library1_HDRS_DETAIL})
target_sources(sample_library1
  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
    ${sample_library1_HDRS_DIRS}
    FILES
    ${sample_library1_HDRS}
    ${sample_library1_HDRS_GENERATE}
)

# 启用头文件验证
set_target_properties(sample_library1
  PROPERTIES
    VERIFY_INTERFACE_HEADER_SETS ON
)

# 设置头文件包含目录
target_include_directories(sample_library1
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

# 链接依赖库
target_link_libraries(sample_library1
  PUBLIC
  PRIVATE
    cpp_sandbox::sample_library0
)
