cmake_minimum_required(VERSION 3.16)

# set the project name
project(ObjectModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Glob for file list -- N.B. this isn't recommended, but using as a convenience
#   Builders might need to manually clean/regenerate when new files are added.
file(GLOB ObjectModel_SRC CONFIGURE_DEPENDS "*.cpp")

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  include_directories(".")
  file(GLOB ObjectModelBindings_SRC CONFIGURE_DEPENDS "bindings/*.cpp")
  #add_library(ObjectModel STATIC ${ObjectModel_SRC} ${ObjectModelBindings_SRC})
  add_executable(ObjectModel ${ObjectModel_SRC} ${ObjectModelBindings_SRC})
  set_target_properties(ObjectModel PROPERTIES LINK_FLAGS "--bind -o foo.js")
else ()
  add_library(ObjectModel STATIC ${ObjectModel_SRC})
endif ()

target_precompile_headers(ObjectModel
  PUBLIC
  pch.h)
