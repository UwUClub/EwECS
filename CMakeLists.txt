cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(PROJECT_NAME EwECS)

# Set the project name and language
project(
  ${PROJECT_NAME}
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/UwUClub/R-Type"
  LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(EwECS_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
EwECS_set_project_warnings(
        EwECS_warnings
        FALSE
        ""
        ""
        ""
        "")

include(Dependencies.cmake)
EwECS_setup_dependencies()

include(cmake/StandardProjectSettings.cmake)

add_library(EwECS::EwECS_warnings ALIAS EwECS_warnings)

# Adding the src:

add_library(ecs STATIC)

add_subdirectory(includes)
add_subdirectory(src)

# Adding the tests:
# include(CTest)

# if(BUILD_TESTING)
#   add_subdirectory(test)
# endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  include(cmake/Utilities.cmake)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
