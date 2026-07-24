# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 构建命令

优先使用 `out/build/` 下已有的最新 preset；若无则默认 Linux 用 `ninja-gcc-reldeb`、Windows 用 `vs2026-reldeb`。如果用户未明确指定 preset，AI 应先 `ls out/build/` 查找已有构建目录，取最新的使用。

```bash
# 配置
cmake --preset <preset>

# 构建
cmake --build --preset <preset>

# 测试
ctest --preset <preset>

# 安装
cmake --install out/build/<preset> --config <config>

# 打包
cpack --preset <preset>
```

## CMake 架构

### 分层结构

```
CMakeLists.txt              # 顶层入口：项目声明、选项、依赖、链接标志、安装/CPack
├── CMakePresets.json        # 配置、构建、测试、打包预设
├── CMakeUserPresets.json    # 用户本地预设（不纳入版本控制）
├── ProjectOptions.cmake     # 选项变量，cxx_sandbox_setup_options()
├── Dependencies.cmake       # 依赖查找，cxx_sandbox_setup_dependencies()
├── cmake/                   # CMake 辅助模块
│   ├── CPM.cmake            # CPM 包管理器
│   ├── CppSandboxHelpers.cmake  # 核心公共函数
│   ├── PreventInSourceBuilds.cmake
│   ├── cpp_sandboxConfig.cmake.in
│   └── ...
├── include/                  # 公开头文件
├── external/                # 第三方库（add_subdirectory 模式）
├── src/                     # 源码模块
└── test/                    # 单元测试
```

### CppSandboxHelpers — 核心辅助函数

`cpp_sandbox_setup_sources(<target> [TYPE LIBRARY|EXECUTABLE])` 自动完成：
- `GLOB_RECURSE` + `CONFIGURE_DEPENDS` 收集源文件和内部头文件
- `source_group()` 在 IDE 中按目录树显示文件
- 库：生成导出头 (`generate_export_header`)、注册 FILE_SET headers、启用 `VERIFY_INTERFACE_HEADER_SETS`
- 库：设置 `BUILD_INTERFACE` / `INSTALL_INTERFACE` include 目录
- 可执行文件：设置 PRIVATE include 目录

`cpp_sandbox_install_target(<target>)` 在 `CPP_SANDBOX_INSTALL=ON` 时添加安装规则，所有目标共享 `cpp_sandboxTargets` 导出集。

### 选项变量

| 变量 | 默认 | 说明 |
|---|---|---|
| `CPP_SANDBOX_BUILD_TESTS` | `PROJECT_IS_TOP_LEVEL` | 子项目时自动关闭 |
| `CPP_SANDBOX_INSTALL` | `PROJECT_IS_TOP_LEVEL` | 子项目时自动关闭 |
| `CPP_SANDBOX_INSTALL_DEPS` | `OFF` | 依赖 `CPP_SANDBOX_INSTALL` |
| `CPP_SANDBOX_USE_CPM` | `ON` | 是否用 CPM 管理依赖 |
| ... | — | — |

新增选项统一在 `ProjectOptions.cmake` 的 `cpp_sandbox_setup_options()` 函数中定义。

### 依赖管理

添加第三方库前必须征求用户意见，由用户决定。

- **小型库**（纯头文件、精简支持 CMake 子项目）：放入 `external/`，通过 `add_subdirectory` 引入
- **大型库**：在 `Dependencies.cmake` 中通过 CPM 或 `find_package` 引入

## 添加新模块的规范

所有模块的 CMakeLists.txt 必须**高度统一，精准到行号**。即使 `target_compile_definitions` 无宏定义、`target_link_libraries` 无链接库，这两个语句也必须保留，留空 `PUBLIC` / `PRIVATE` 占位。

### 库模块

每个库模块在 `src/<module_name>/` 和 `include/cpp_sandbox/<module_name>/` 下，CMakeLists.txt 遵循统一模板：

```cmake
# 定义动态库
add_library(<module_name>)
add_library(cpp_sandbox::<module_name> ALIAS <module_name>)

# 设置项目c++标准
target_compile_features(<module_name> PRIVATE cxx_std_11)
target_compile_features(<module_name> INTERFACE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(<module_name> PUBLIC PRIVATE)

# 设置项目属性
set_target_properties(<module_name> PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# 设置vs项目文件夹
set_target_properties(<module_name> PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(<module_name>)

# 链接依赖库
target_link_libraries(<module_name>
  PUBLIC
  PRIVATE
)

cpp_sandbox_install_target(<module_name>)
```

### 可执行文件模块

```cmake
# 定义可执行文件
add_executable(<module_name>)
add_executable(cpp_sandbox::<module_name> ALIAS <module_name>)

# 设置项目c++标准
target_compile_features(<module_name> PRIVATE cxx_std_11)

# 设置项目宏定义
target_compile_definitions(<module_name> PRIVATE)

# 设置项目属性
set_target_properties(<module_name> PROPERTIES
  INSTALL_RPATH "$<$<PLATFORM_ID:Linux>:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}>"
)

# 设置vs项目文件夹
set_target_properties(<module_name> PROPERTIES FOLDER ${PROJECT_NAME})

cpp_sandbox_setup_sources(<module_name>)

# 链接依赖库
target_link_libraries(<module_name>
  PUBLIC
  PRIVATE
)

cpp_sandbox_install_target(<module_name>)
```

新增模块后，在 `src/CMakeLists.txt` 中 `add_subdirectory(<module_name>)` 注册。

### 目录结构约定

```
src/<module_name>/                  # 源文件目录
├── CMakeLists.txt
├── *.cpp                           # 源文件
└── internal/                       # 模块私有头文件（仅本模块可见）
    └── <helper>.hpp

include/cpp_sandbox/<module_name>/  # 公开头文件
├── *.hpp                           # 头文件
└── detail/                         # 内部实现细节（项目内可见，不安装）
    └── <detail_helper>.hpp
```

**三种头文件可见性：**
- `internal/`：PRIVATE include 路径，仅本模块的 .cpp 文件可以包含
- `detail/`：PUBLIC include 路径但不属于 FILE_SET headers（不安装），项目内其他模块可以包含
- 公开头文件：属于 FILE_SET headers，安装后会暴露给下游消费者

### 测试

主要使用 GTest，每个模块在 `test/src/<module_name>/` 下编写单元测试。`test/Catch2/` 仅为 Catch2 的示例用法，不作为主要测试框架。

测试 CMakeLists.txt 模板（以下为必须保留的核心结构，可根据需要附加拷贝 DLL 等逻辑以保证测试能正常运行）：

```cmake
add_executable(test_<module_name> test_<module_name>.cpp)
set_target_properties(test_<module_name> PROPERTIES FOLDER ${PROJECT_NAME}/tests)
target_link_libraries(test_<module_name> PRIVATE cpp_sandbox::<module_name> GTest::gtest_main)
gtest_discover_tests(test_<module_name>)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET test_<module_name>
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test_<module_name>>
      $<TARGET_FILE_DIR:test_<module_name>>
    COMMAND_EXPAND_LISTS
  )
endif()
```

新增测试模块后，在 `test/src/CMakeLists.txt` 中 `add_subdirectory(<module_name>)` 注册。
