macro(cpp_sandbox_setup_options)
  if(NOT PROJECT_IS_TOP_LEVEL)
    option(CPP_SANDBOX_BUILD_TESTS "Build unit tests" OFF)
    option(CPP_SANDBOX_INSTALL "Enable install targets" OFF)
  else()
    option(CPP_SANDBOX_BUILD_TESTS "Build unit tests" ON)
    option(CPP_SANDBOX_INSTALL "Enable install targets" ON)
  endif()

  option(CPP_SANDBOX_USE_CPM "Use CPM to setup dependencies" ON)

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(CPP_SANDBOX_BUILD_TESTS
      CPP_SANDBOX_INSTALL
      CPP_SANDBOX_USE_CPM
    )
  endif()
endmacro()
