macro(cpp_sandbox_setup_options)
  if(NOT PROJECT_IS_TOP_LEVEL)

  else()

  endif()

  option(cpp_sandbox_USE_CPM "Use CPM to setup dependencies" ON)

  if(NOT PROJECT_IS_TOP_LEVEL)
    # mark_as_advanced
  endif()
endmacro()
