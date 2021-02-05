cmake_minimum_required(VERSION 3.9)

project(duh)
set(DUH_SOURCE
  control-icons.cpp
)

if(NOT TARGET BlitEngine)
  message(FATAL_ERROR "32Blit targets not defined, make sure you include 32Blit first!")
endif()

add_library(DUH STATIC ${DUH_SOURCE})
target_include_directories(DUH PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(DUH BlitEngine)
blit_assets_yaml(DUH assets.yml)