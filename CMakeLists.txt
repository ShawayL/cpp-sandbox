cmake_minimum_required(VERSION 3.21)

# 设置项目名称和语言
project(
  cpp_sandbox
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/ShawayL/cpp-sandbox"
  LANGUAGES CXX C)

# 防止源代码目录构建
include(cmake/PreventInSourceBuilds.cmake)

# 仅当 CMAKE_CXX_STANDARD 未由其他人设置时才设置
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

include(ProjectOptions.cmake)
cpp_sandbox_setup_options()

include(Dependencies.cmake)
cpp_sandbox_setup_dependencies()

add_subdirectory(src)

include(GNUInstallDirs)

install(TARGETS sample_library0
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
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
