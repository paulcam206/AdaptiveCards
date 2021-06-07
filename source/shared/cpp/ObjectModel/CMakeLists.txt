cmake_minimum_required(VERSION 3.16)

# set the project name
project(AdaptiveCardsSharedModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Glob for file list -- N.B. this isn't recommended, but using as a convenience
#   Builders might need to manually clean/regenerate when new files are added.
file(GLOB AdaptiveCardsSharedModel_SRC CONFIGURE_DEPENDS "*.cpp")

if (EMSCRIPTEN)
  add_compile_options(
    "$<$<CONFIG:DEBUG>:-g;-O0>"
    "$<$<CONFIG:RELEASE>:-Oz>")
  #set(EMCXX_COMPILE_FLAGS "-g -s NO_DISABLE_EXCEPTION_CATCHING")
  set(CXX_COMPILE_FLAGS "${CXX_COMPILE_FLAGS} ${EMCXX_COMPILE_FLAGS}")
  include_directories(".")
  file(GLOB AdaptiveCardsSharedModelBindings_SRC CONFIGURE_DEPENDS "bindings/*.cpp")
  #add_library(AdaptiveCardsSharedModel STATIC ${AdaptiveCardsSharedModel_SRC} ${AdaptiveCardsSharedModelBindings_SRC})
  add_executable(AdaptiveCardsSharedModel ${AdaptiveCardsSharedModel_SRC} ${AdaptiveCardsSharedModelBindings_SRC})

  set_target_properties(AdaptiveCardsSharedModel PROPERTIES LINK_FLAGS "--bind -s EXPORT_NAME=AdaptiveCardsSharedModel -s MODULARIZE=1 -s EXPORT_ES6=1 -s ENVIRONMENT='web' --closure 1 -Oz -o foo.js")
  # set_target_properties(AdaptiveCardsSharedModel PROPERTIES LINK_FLAGS "--bind -s EXPORT_NAME=AdaptiveCardsSharedModel -s MODULARIZE=1 -s EXPORT_ES6=1 -s ENVIRONMENT='web' -g -Oz -o foo.js")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_COMPILE_FLAGS}")
else ()
  add_library(AdaptiveCardsSharedModel STATIC ${AdaptiveCardsSharedModel_SRC})
endif ()

target_precompile_headers(AdaptiveCardsSharedModel
  PUBLIC
  pch.h)
