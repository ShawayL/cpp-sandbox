include(CMakeDependentOption)

macro(cpp_sandbox_setup_options)
  # 当作为子项目引入时，默认关闭测试和安装，避免影响父项目配置。
  if(NOT PROJECT_IS_TOP_LEVEL)
    option(CPP_SANDBOX_BUILD_TESTS "Build unit tests" OFF)
    option(CPP_SANDBOX_INSTALL "Enable install targets" OFF)
  else()
    option(CPP_SANDBOX_BUILD_TESTS "Build unit tests" ON)
    option(CPP_SANDBOX_INSTALL "Enable install targets" ON)
  endif()

  # CPP_SANDBOX_INSTALL_DEPS: 是否安装依赖库
  # 仅在 CPP_SANDBOX_INSTALL 为 ON 时可启用，否则强制 OFF
  cmake_dependent_option(
    CPP_SANDBOX_INSTALL_DEPS
    "Enable install dependencies"
    OFF
    "CPP_SANDBOX_INSTALL"
    OFF
  )

  # CPP_SANDBOX_USE_CPM: 是否使用 CPM.cmake 来管理依赖
  option(CPP_SANDBOX_USE_CPM "Use CPM to setup dependencies" ON)

  # CPP_SANDBOX_BUILD_WITH_GDAL: 是否启用 GDAL 支持
  option(CPP_SANDBOX_BUILD_WITH_GDAL "Build with gdal" OFF)

  # 当作为子项目引入时，隐藏这些选项以避免干扰父项目配置
  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      CPP_SANDBOX_BUILD_TESTS
      CPP_SANDBOX_INSTALL
      CPP_SANDBOX_INSTALL_DEPS
      CPP_SANDBOX_USE_CPM
      CPP_SANDBOX_BUILD_WITH_GDAL
    )
  endif()
endmacro()
