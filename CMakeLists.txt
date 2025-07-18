cmake_minimum_required(VERSION 3.21)

# 设置项目名称和语言
project(
  cpp_sandbox
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/ShawayL/cpp-sandbox"
  LANGUAGES CXX C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# 防止源代码目录构建
include(cmake/PreventInSourceBuilds.cmake)

# 仅当 CMAKE_CXX_STANDARD 未由其他人设置时才设置
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

# 设置项目选项
include(ProjectOptions.cmake)
cpp_sandbox_setup_options()

# 设置依赖项
include(Dependencies.cmake)
cpp_sandbox_setup_dependencies()

add_subdirectory(src)

# 添加测试
if(CPP_SANDBOX_BUILD_TESTS)
  add_subdirectory(test)
endif()

# 安装目标
if(CPP_SANDBOX_INSTALL)
  install(TARGETS
    sample_library0
    sample_library1
    sample_executable0
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

  configure_package_config_file("cmake/${PROJECT_NAME}Config.cmake.in"
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

  set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
  )

  include(CPack)
endif()
