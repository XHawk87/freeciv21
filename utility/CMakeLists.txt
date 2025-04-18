# Generate specenum_gen.h
add_custom_command(
  OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/specenum_gen.h
  COMMAND
    ${Python3_EXECUTABLE}
    ${CMAKE_CURRENT_SOURCE_DIR}/generate_specenum.py
    ${CMAKE_CURRENT_BINARY_DIR}/specenum_gen.h
  VERBATIM
  DEPENDS
    generate_specenum.py
)


# Configuration headers
set(BUG_URL ${FREECIV_BUG_URL})
# The first one is intended for public usage but we don't support shared
# libfreeciv
configure_file(cmake_fc_config.h.in fc_config.h)

add_library(
  utility
  STATIC
  astring.cpp
  bitvector.cpp
  bugs.cpp
  capability.cpp
  deprecations.cpp
  distribute.cpp
  fcbacktrace.cpp
  fciconv.cpp
  fcintl.cpp
  fcthread.cpp
  genhash.cpp
  genlist.cpp
  inputfile.cpp
  iterator.cpp
  log.cpp
  netfile.cpp
  rand.cpp
  registry.cpp
  registry_ini.cpp
  section_file.cpp
  shared.cpp
  support.cpp
  timing.cpp
  version.cpp
  # Generated
  ${CMAKE_CURRENT_BINARY_DIR}/specenum_gen.h
)

# Add backward.hpp to the include path
set(BACKWARD_DEFINES "")
list(APPEND BACKWARD_DEFINES BACKWARD_HAS_UNWIND=${BACKWARD_HAS_UNWIND})
list(APPEND BACKWARD_DEFINES BACKWARD_HAS_BACKTRACE=${BACKWARD_HAS_BACKTRACE})
list(APPEND BACKWARD_DEFINES BACKWARD_HAS_DW=${BACKWARD_HAS_DW})
list(APPEND BACKWARD_DEFINES BACKWARD_HAS_BACKTRACE_SYMBOLS=${BACKWARD_HAS_BACKTRACE_SYMBOLS})
set_source_files_properties(
  fcbacktrace.cpp PROPERTIES
  INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/dependencies/backward-cpp-1.6
  COMPILE_DEFINITIONS "${BACKWARD_DEFINES}")

target_include_directories(utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(utility PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(utility PRIVATE ${STACK_UNWINDING_LIBRARY})
target_link_libraries(utility PRIVATE ${STACK_SYMBOLS_LIBRARY})
target_link_libraries(utility PUBLIC Qt6::Core Qt6::Network)
target_link_libraries(utility PRIVATE KF6::Archive)
if (WIN32 OR MSYS OR MINGW)
  target_link_libraries(utility PRIVATE ws2_32 wsock32)
endif()
if ((MSYS OR MINGW) AND NOT (FREECIV_DEBUG OR FREECIV_TESTMATIC))
  target_link_libraries(utility PRIVATE imagehlp)
endif()

# Suppress warnings from specenum_gen.h
freeciv_add_flag_if_supported(
  utility -Wno-tautological-constant-out-of-range-compare)

if(FREECIV_ENABLE_NLS)
  target_include_directories(utility PUBLIC ${Intl_INCLUDE_DIRS})
  target_link_libraries(utility PUBLIC ${Intl_LIBRARIES})
endif()

# Tests
if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
