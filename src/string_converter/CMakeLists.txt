# 定义动态库
add_library(string_converter)
add_library(cpp_sandbox::string_converter ALIAS string_converter)

# 设置项目c++标准
target_compile_features(string_converter PRIVATE cxx_std_17)
target_compile_features(string_converter INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(string_converter PUBLIC PRIVATE)

# 设置项目属性
set_target_properties(string_converter PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(string_converter PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(string_converter)

# 链接依赖库
target_link_libraries(string_converter
  PUBLIC
  PRIVATE
    $<$<NOT:$<PLATFORM_ID:Windows>>:Iconv::Iconv>
)
