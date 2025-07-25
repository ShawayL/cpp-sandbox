cmake_minimum_required(VERSION 3.23)

# 设置项目名称和语言
project(
  cpp_sandbox
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/ShawayL/cpp-sandbox"
  LANGUAGES CXX C)

# 防止源代码目录构建
include(cmake/PreventInSourceBuilds.cmake)

# for CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)
# for configure_package_config_file and write_basic_package_version_file
include(CMakePackageConfigHelpers)

# 作为顶层项目...
if(PROJECT_IS_TOP_LEVEL)
  # 确保使用 -std=c++xx 而非 -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)
  # 顶层项目才启用测试支持
  include(CTest)
endif()

# 设置项目选项
include(ProjectOptions.cmake)
cpp_sandbox_setup_options()

# 设置依赖项
include(Dependencies.cmake)
cpp_sandbox_setup_dependencies()

add_subdirectory(src)

# 添加测试
if(CPP_SANDBOX_BUILD_TESTS AND BUILD_TESTING)
  add_subdirectory(test)
endif()

# 安装目标
if(CPP_SANDBOX_INSTALL)
  install(TARGETS
    sample_library0
    sample_library1
    sample_executable0
    find_submatrix
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

  if(BUILD_SHARED_LIBS)
    set(CPACK_LIB_TYPE "shared")
  else()
    set(CPACK_LIB_TYPE "static")
  endif()

  set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}-${CPACK_LIB_TYPE}"
  )

  include(CPack)
endif()
