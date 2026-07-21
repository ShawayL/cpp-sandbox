# 定义动态库
add_library(sample_library0)
add_library(cpp_sandbox::sample_library0 ALIAS sample_library0)

# 设置项目c++标准
target_compile_features(sample_library0 PRIVATE cxx_std_11)
target_compile_features(sample_library0 INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(sample_library0 PUBLIC $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:SAMPLE_LIBRARY0_STATIC_DEFINE> PRIVATE)

# 设置项目属性
set_target_properties(sample_library0 PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(sample_library0 PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(sample_library0)

# 链接依赖库
target_link_libraries(sample_library0
  PUBLIC
  PRIVATE
)
