# ==============================================================================
# CppSandboxHelpers — 公共 CMake 辅助函数
# ==============================================================================

# 为目标收集源文件和头文件，封装 GLOB_RECURSE、source_group、FILE_SET、
# target_include_directories 等样板代码。
#
# 用法:
#   cpp_sandbox_setup_sources(<target>)
#   cpp_sandbox_setup_sources(<target> TYPE LIBRARY|EXECUTABLE)
#
# 若不传 TYPE，则通过 get_target_property(TYPE) 自动判断。
function(cpp_sandbox_setup_sources TARGET)
  cmake_parse_arguments(ARG "" "TYPE" "" ${ARGN})

  # --- 自动判断目标类型 ---
  if(NOT ARG_TYPE)
    get_target_property(_target_type ${TARGET} TYPE)
    if(_target_type STREQUAL "EXECUTABLE")
      set(ARG_TYPE "EXECUTABLE")
    else()
      set(ARG_TYPE "LIBRARY")
    endif()
  endif()

  # ==========================================================================
  # 源文件 & 内部头文件（所有 target 共用）
  # ==========================================================================
  file(GLOB_RECURSE ${TARGET}_SRCS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
  )
  file(GLOB_RECURSE ${TARGET}_HDRS_PRIVATE CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/*.h"
  )

  # 设置源码文件夹
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/internal
    PREFIX "Header Files/internal" FILES ${${TARGET}_HDRS_PRIVATE})
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    PREFIX "Source Files" FILES ${${TARGET}_SRCS})

  target_sources(${TARGET}
    PRIVATE
      ${${TARGET}_SRCS}
      ${${TARGET}_HDRS_PRIVATE}
  )

  # ==========================================================================
  # 库专属：公开头文件 + 导出头 + FILE_SET + 头文件验证 + include 目录
  # ==========================================================================
  if(ARG_TYPE STREQUAL "LIBRARY")
    # 生成导出头
    include(GenerateExportHeader)
    generate_export_header(${TARGET}
      EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/${TARGET}/${TARGET}_export.hpp)

    # 公开头文件
    file(GLOB_RECURSE ${TARGET}_HDRS CONFIGURE_DEPENDS
      "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/${TARGET}/*.hpp"
      "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/${TARGET}/*.h"
    )
    # 生成的头文件
    file(GLOB_RECURSE ${TARGET}_HDRS_GENERATE CONFIGURE_DEPENDS
      "${PROJECT_BINARY_DIR}/include/cpp_sandbox/${TARGET}/*.hpp"
      "${PROJECT_BINARY_DIR}/include/cpp_sandbox/${TARGET}/*.h"
    )
    # 内部 detail 头文件（不安装）
    file(GLOB_RECURSE ${TARGET}_HDRS_DETAIL CONFIGURE_DEPENDS
      "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/${TARGET}/detail/*.hpp"
      "${PROJECT_SOURCE_DIR}/include/cpp_sandbox/${TARGET}/detail/*.h"
    )

    # 设置源码文件夹
    source_group(TREE ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/${TARGET}
      PREFIX "Header Files/cpp_sandbox/${TARGET}" FILES ${${TARGET}_HDRS})
    source_group(TREE ${PROJECT_BINARY_DIR}/include/cpp_sandbox/${TARGET}
      PREFIX "Header Files/cpp_sandbox/${TARGET}" FILES ${${TARGET}_HDRS_GENERATE})

    # 将公开头文件注册为 target 私有源码（使其在 IDE 中可见）
    target_sources(${TARGET}
      PRIVATE
        ${${TARGET}_HDRS}
        ${${TARGET}_HDRS_GENERATE}
    )

    # FILE_SET — 安装时自动安装，配合头文件验证
    list(REMOVE_ITEM ${TARGET}_HDRS ${${TARGET}_HDRS_DETAIL})
    target_sources(${TARGET}
      PUBLIC
        FILE_SET headers
        TYPE HEADERS
        BASE_DIRS
        ${PROJECT_BINARY_DIR}/include
        ${PROJECT_SOURCE_DIR}/include
        FILES
        ${${TARGET}_HDRS}
        ${${TARGET}_HDRS_GENERATE}
    )

    # 启用头文件自包含验证
    set_target_properties(${TARGET}
      PROPERTIES
        VERIFY_INTERFACE_HEADER_SETS ON
    )

    # 头文件包含目录：PUBLIC（对外暴露）+ PRIVATE（内部）
    target_include_directories(${TARGET}
      PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
      PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/internal
    )
  endif()

  # ==========================================================================
  # 可执行文件：仅 PRIVATE 包含目录
  # ==========================================================================
  if(ARG_TYPE STREQUAL "EXECUTABLE")
    target_include_directories(${TARGET}
      PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/internal
    )
  endif()
endfunction()
