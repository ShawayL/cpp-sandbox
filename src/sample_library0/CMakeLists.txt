include(GenerateExportHeader)

add_library(sample_library0)

add_library(cpp_sandbox::sample_library0 ALIAS sample_library0)

generate_export_header(sample_library0 EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library0_export.hpp)

target_sources(sample_library0
  PRIVATE
    sample_library0.cpp
)

target_sources(sample_library0
  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
    FILES
      ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/sample_library0.hpp
      ${PROJECT_BINARY_DIR}/include/cpp_sandbox/sample_library0_export.hpp
)

target_include_directories(sample_library0 PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                 $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
                                                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(sample_library0 PUBLIC cxx_std_11)

set_target_properties(sample_library0
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} CXX_VISIBILITY_PRESET hidden)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(sample_library0 PUBLIC SAMPLE_LIBRARY0_STATIC_DEFINE)
endif()
