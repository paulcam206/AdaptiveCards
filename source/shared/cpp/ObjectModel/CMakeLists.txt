cmake_minimum_required(VERSION 3.16)

# set the project name
project(ObjectModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Glob for file list -- N.B. this isn't recommended, but using as a convenience
#   Builders might need to manually clean/regenerate when new files are added.
file(GLOB ObjectModel_SRC CONFIGURE_DEPENDS "*.cpp")

if (EMSCRIPTEN)
  add_compile_options(
    "$<$<CONFIG:DEBUG>:-g;-O0>"
    "$<$<CONFIG:RELEASE>:-Oz>")
  #set(EMCXX_COMPILE_FLAGS "-g -s NO_DISABLE_EXCEPTION_CATCHING")
  set(CXX_COMPILE_FLAGS "${CXX_COMPILE_FLAGS} ${EMCXX_COMPILE_FLAGS}")
  include_directories(".")
  file(GLOB ObjectModelBindings_SRC CONFIGURE_DEPENDS "bindings/*.cpp")
  #add_library(ObjectModel STATIC ${ObjectModel_SRC} ${ObjectModelBindings_SRC})
  add_executable(ObjectModel ${ObjectModel_SRC} ${ObjectModelBindings_SRC})

  set_target_properties(ObjectModel PROPERTIES LINK_FLAGS "--bind -g -Oz -o foo.js")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS}")
else ()
  add_library(ObjectModel STATIC ${ObjectModel_SRC})
endif ()

target_precompile_headers(ObjectModel
  PUBLIC
  pch.h)
