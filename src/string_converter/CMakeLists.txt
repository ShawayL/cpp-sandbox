include(GenerateExportHeader)

add_library(string_converter)

add_library(cpp_sandbox::string_converter ALIAS string_converter)

generate_export_header(string_converter EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/string_converter_export.hpp)

target_sources(string_converter
  PRIVATE
    StringConverter.cpp
)

target_sources(string_converter
  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
    FILES
      ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/StringConverter.hpp
      ${PROJECT_BINARY_DIR}/include/cpp_sandbox/string_converter_export.hpp
)

target_include_directories(string_converter PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                 $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
                                                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(string_converter PUBLIC cxx_std_11)

set_target_properties(string_converter
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} CXX_VISIBILITY_PRESET hidden)

if(NOT WIN32)
  target_link_libraries(string_converter PRIVATE Iconv::Iconv)
endif()
