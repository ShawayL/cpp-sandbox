include(GenerateExportHeader)

add_library(sample_library1)

add_library(cpp_sandbox::sample_library1 ALIAS sample_library1)

generate_export_header(sample_library1 EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library1_export.hpp)

target_sources(sample_library1
  PRIVATE
    sample_library1.cpp
)

target_sources(sample_library1
  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
    FILES
      ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library1.hpp
      ${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library1_export.hpp
)

target_include_directories(sample_library1 PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                 $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
                                                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(sample_library1
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} CXX_VISIBILITY_PRESET hidden)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(sample_library1 PUBLIC sample_library1_STATIC_DEFINE)
endif()

target_link_libraries(sample_library1 cpp_sandbox::sample_library0)
                                                                  