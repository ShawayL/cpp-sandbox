# 定义动态库
add_library(gdal_util_library)
add_library(cpp_sandbox::gdal_util_library ALIAS gdal_util_library)

# 设置项目c++标准
target_compile_features(gdal_util_library PRIVATE cxx_std_11)
target_compile_features(gdal_util_library INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(gdal_util_library PUBLIC PRIVATE)

# 设置项目属性
set_target_properties(gdal_util_library PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(gdal_util_library PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(gdal_util_library)

# 链接依赖库
target_link_libraries(gdal_util_library
  PUBLIC
  PRIVATE
    GDAL::GDAL
)
