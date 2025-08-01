# Win32 et al requires cmake version 3.16 because we use a newer command
#   "file(GET_RUNTIME_DEPENDENCIES ..." that is only available at v3.16+
# On other platforms (*nix, MacOS) we need to support older 3.12+ for the
#   server and other components
cmake_minimum_required(VERSION 3.21...3.22 FATAL_ERROR)

# Set vcpkg if exists. Used by MacOS and Visual Studio
if(DEFINED ENV{VCPKG_ROOT} AND FREECIV_USE_VCPKG)
  message(STATUS "Microsoft VCPKG enabled, setting toolset specific settings.")
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

# Detect MS Visual Studio
if (CMAKE_GENERATOR MATCHES "Visual Studio")
  message(STATUS "Microsoft Visual Studio enabled, setting toolset specific settings.")
  set(CMAKE_GENERATOR_TOOLSET "ClangCl")
  message(STATUS "VS Cmake Generator Toolset: ${CMAKE_GENERATOR_TOOLSET}")
  set(CMAKE_GENERATOR_PLATFORM "x64")
  message(STATUS "VS Cmake Generator Platform: ${CMAKE_GENERATOR_PLATFORM}")
endif()

# Set up cmake search path
if (EMSCRIPTEN)
  message(STATUS "Using Emscripten-specific settings")
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/emscripten)
endif()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Always generate the compilation database by default
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set the build defaults
include(cmake/FreecivBuildOptions.cmake)

# Add support for Auto Revision
include(AutoRevision)

# Set some variables from AutoRevision for use here and later
list(LENGTH FC21_REV_TAG_LIST FC21_REV_TAG_LIST_LENGTH)

# When we tag a stable release we only get 3 of the 4 components populated,
# so we manually set some of the variables we need for the full version.
if (${FC21_REV_TAG_LIST_LENGTH} EQUAL 3)
  list(GET FC21_REV_TAG_LIST 0 FC21_MAJOR_VERSION)
  list(GET FC21_REV_TAG_LIST 1 FC21_MINOR_VERSION)
  list(GET FC21_REV_TAG_LIST 2 FC21_PATCH_VERSION)
  set(FC21_VERSION_LABEL "stable")
  set(IS_STABLE_VERSION true)
  set(FREECIV21_VERSION "${FC21_MAJOR_VERSION}.${FC21_MINOR_VERSION}.${FC21_PATCH_VERSION}")
else()
  list(GET FC21_REV_TAG_LIST 0 FC21_MAJOR_VERSION)
  list(GET FC21_REV_TAG_LIST 1 FC21_MINOR_VERSION)
  list(GET FC21_REV_TAG_LIST 2 FC21_VERSION_LABEL)
  list(GET FC21_REV_TAG_LIST 3 FC21_PATCH_VERSION)
  set(IS_STABLE_VERSION false)
  set(FREECIV21_VERSION "${FC21_MAJOR_VERSION}.${FC21_MINOR_VERSION}")
endif()

# Set project
project(freeciv21 VERSION ${FREECIV21_VERSION} LANGUAGES C CXX)

# Gather all the tailored settings we need for Windows builds early.
if(WIN32 OR MSYS)
  # We need to alter the out of box values of these variables for Win32 et al builds
  set(CMAKE_INSTALL_DATAROOTDIR ".")
  set(CMAKE_INSTALL_BINDIR ".")
  set(PROJECT_NAME "data")
  set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_DATAROOTDIR}/doc/")
  get_filename_component(CLANG_PATH ${CMAKE_CXX_COMPILER} PATH)
endif()

add_compile_definitions(PUBLIC $<$<CONFIG:Debug>:FREECIV_DEBUG>)

# After project() because the list of languages has to be known
include(FreecivDependencies)
include(FreecivHelpers)

# Put all executables at the root of the build tree
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# We do this after all targets with third-party code have been created, so
#   the options only apply to code we own.
include(EnableCompilerWarnings)

# Include subdirectories with the actual project definitions
add_subdirectory(utility)
add_subdirectory(common)
add_subdirectory(data)

if (FREECIV_ENABLE_CLIENT)
  add_subdirectory(client)
endif()
if (FREECIV_BUILD_LIBSERVER)
  add_subdirectory(server)
endif()

# Always add tools, conditionals are inside
add_subdirectory(tools)

# Add docs
add_subdirectory(docs)

# Use Auto Revision variables to convert some templates to real files at build
# time. Avoid overwriting if the version didn't change.
configure_file("utility/fc_version.h.in" utility/fc_version.h.new
               @ONLY NEWLINE_STYLE UNIX)
file(COPY_FILE "${CMAKE_BINARY_DIR}/utility/fc_version.h.new"
               "${CMAKE_BINARY_DIR}/utility/fc_version.h"
     ONLY_IF_DIFFERENT)

# Include Installation Commands
include(FreecivInstall)

# Packaging (CPack)
include(CPackConfig)
