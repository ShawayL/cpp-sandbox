add_executable(sample_executable0 main.cpp)

add_executable(cpp_sandbox::sample_executable0 ALIAS sample_executable0)

target_link_libraries(
  sample_executable0
  PRIVATE cpp_sandbox::sample_library0
          cpp_sandbox::sample_library1)

#include(GNUInstallDirs)
#
#install(TARGETS sample_executable0
#  EXPORT sample_executable0Targets
#  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  FILE_SET headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#
#install(
#  EXPORT sample_executable0Targets
#  NAMESPACE cpp_sandbox::
#  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
#)
