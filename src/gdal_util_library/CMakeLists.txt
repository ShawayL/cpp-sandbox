include(GenerateExportHeader)

add_library(gdal_util_library)

add_library(cpp_sandbox::gdal_util_library ALIAS gdal_util_library)

generate_export_header(gdal_util_library EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/cpp_sandbox/gdal_util_library_export.hpp)

target_sources(gdal_util_library
  PRIVATE
    gdal_util_library.cpp
)

target_sources(gdal_util_library
  PUBLIC
    FILE_SET headers
    TYPE HEADERS
    BASE_DIRS
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_BINARY_DIR}/include"
    FILES
      ${PROJECT_SOURCE_DIR}/include/cpp_sandbox/gdal_util_library.hpp
      ${PROJECT_BINARY_DIR}/include/cpp_sandbox/gdal_util_library_export.hpp
)

target_include_directories(gdal_util_library PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                 $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
                                                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(gdal_util_library PUBLIC cxx_std_11)

set_target_properties(gdal_util_library
  PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR} CXX_VISIBILITY_PRESET hidden)

target_link_libraries(gdal_util_library GDAL::GDAL)
                                                                  