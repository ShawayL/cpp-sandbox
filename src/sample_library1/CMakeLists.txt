# 定义动态库
add_library(sample_library1)
add_library(cpp_sandbox::sample_library1 ALIAS sample_library1)

# 设置项目c++标准
target_compile_features(sample_library1 PRIVATE cxx_std_11)
target_compile_features(sample_library1 INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(sample_library1 PUBLIC $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:SAMPLE_LIBRARY1_STATIC_DEFINE> PRIVATE)

# 设置项目属性
set_target_properties(sample_library1 PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(sample_library1 PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(sample_library1)

# 链接依赖库
target_link_libraries(sample_library1
  PUBLIC
  PRIVATE
    cpp_sandbox::sample_library0
)
