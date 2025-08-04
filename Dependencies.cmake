if(CPP_SANDBOX_USE_CPM)
  include(cmake/CPM.cmake)
endif()

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(cpp_sandbox_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  #if(NOT TARGET spdlog::spdlog)
  #  if(CPP_SANDBOX_USE_CPM)
  #    cpmaddpackage(
  #      NAME
  #      spdlog
  #      VERSION
  #      1.15.2
  #      GITHUB_REPOSITORY
  #      "gabime/spdlog")
  #  else()
  #    find_package(spdlog REQUIRED)
  #  endif()
  #endif()

  if(CPP_SANDBOX_BUILD_TESTS)
    if(NOT TARGET Catch2::Catch2WithMain)
      if(CPP_SANDBOX_USE_CPM)
        cpmaddpackage("gh:catchorg/Catch2@3.8.1")
      else()
        find_package(Catch2 REQUIRED)
      endif()
    endif()
  endif()

  if(NOT WIN32)
    if(NOT TARGET Iconv::Iconv)
      find_package(Iconv REQUIRED)
    endif()
  endif()

endfunction()
