cmake_minimum_required(VERSION 3.26)

# 设置项目名称和语言
project(
  cpp_sandbox
  VERSION 0.0.1
  DESCRIPTION
    "A personal C++ sandbox for daily practice, experiments, and implementing ideas"
  HOMEPAGE_URL "https://github.com/ShawayL/cpp-sandbox"
  LANGUAGES CXX C
)

# cmake模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 防止源代码目录构建
include(PreventInSourceBuilds)

# 提供 CMAKE_INSTALL_BINDIR、CMAKE_INSTALL_LIBDIR、CMAKE_INSTALL_INCLUDEDIR 等变量
include(GNUInstallDirs)
# 提供生成版本文件的功能
include(CMakePackageConfigHelpers)

# 作为顶层项目...
if(PROJECT_IS_TOP_LEVEL)
  # 确保使用 -std=c++xx 而非 -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)
  # 顶层项目才启用测试支持
  include(CTest)
  # 启用项目文件夹
  if(WIN32 AND MSVC)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  endif()
endif()

# 设置项目选项
include(ProjectOptions.cmake)
cpp_sandbox_setup_options()

# 设置依赖项
include(Dependencies.cmake)
cpp_sandbox_setup_dependencies()

# 添加external目录
add_subdirectory(external)

# 关闭替代标记
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-operator-names")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-operator-names")
endif(CMAKE_COMPILER_IS_GNUCXX)

# 设置链接标志
include(CheckLinkerFlag)
check_linker_flag(CXX "-Wl,--disable-new-dtags" LINKER_SUPPORTS_DISABLE_NEWTAGS)
if(LINKER_SUPPORTS_DISABLE_NEWTAGS)
  message(STATUS "Linker supports --disable-new-dtags")
  add_link_options(-Wl,--disable-new-dtags)
endif()
check_linker_flag(CXX "-Wl,--exclude-libs,ALL" LINKER_SUPPORTS_EXCLUDE_LIBS)
if(LINKER_SUPPORTS_EXCLUDE_LIBS)
  message(STATUS "Linker supports --exclude-libs,ALL")
  add_link_options(-Wl,--exclude-libs,ALL)
endif()

# 添加源码目录
add_subdirectory(src)

# 添加测试
if(CPP_SANDBOX_BUILD_TESTS AND BUILD_TESTING)
  add_subdirectory(test)
  # 设置vs默认启动项目
  if(WIN32 AND MSVC)
    set_property(
      DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      PROPERTY VS_STARTUP_PROJECT tests
    )
  endif()
endif()

#linux下定义获取目标文件函数
if(LINUX)
  function(get_all_library_of_target TARGET OUT_VAR)
    if(NOT TARGET ${TARGET})
      message(WARNING "Target ${TARGET} does not exist.")
      set(${OUT_VAR} "" PARENT_SCOPE)
      return()
    endif()
    get_target_property(LIB_PATH ${TARGET} IMPORTED_LOCATION)
    if(NOT LIB_PATH)
      set(LIB_PATH $<TARGET_FILE:${TARGET}>)
    endif()
    if(NOT LIB_PATH)
      message(
        WARNING
        "Target ${TARGET} does not have a library file associated."
      )
      set(${OUT_VAR} "" PARENT_SCOPE)
      return()
    endif()
    get_filename_component(LIB_DIR "${LIB_PATH}" DIRECTORY)
    get_filename_component(LIB_NAME "${LIB_PATH}" NAME)
    string(REGEX REPLACE "\\.so.*$" "" LIB_PREFIX "${LIB_NAME}")
    file(GLOB ALL_LIBS "${LIB_DIR}/${LIB_PREFIX}*.so*")
    list(SORT ALL_LIBS)
    set(${OUT_VAR} ${ALL_LIBS} PARENT_SCOPE)
  endfunction()
endif()

#定义安装空目录的宏
macro(install_empty_directory dirname root)
  file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${dirname}")
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${dirname} DESTINATION ${root})
endmacro()

# 安装目标
if(CPP_SANDBOX_INSTALL)
  set(cpp_sandbox_install_targets
    sample_library0
    sample_library1
    string_converter
    sample_executable0
    find_submatrix
  )
  if(CPP_SANDBOX_BUILD_WITH_GDAL)
    list(APPEND cpp_sandbox_install_targets gdal_util_library)
  endif()

  install(
    TARGETS
      ${cpp_sandbox_install_targets}
    EXPORT cpp_sandboxTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILE_SET headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(
    EXPORT cpp_sandboxTargets
    NAMESPACE cpp_sandbox::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  )

  configure_package_config_file(
    "cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  )

  write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
  )

  install(
    FILES
      "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
      "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  )

  if(BUILD_SHARED_LIBS)
    set(CPACK_LIB_TYPE "shared")
  else()
    set(CPACK_LIB_TYPE "static")
  endif()

  set(
    CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${CPACK_LIB_TYPE}"
  )

  include(CPack)
endif()
