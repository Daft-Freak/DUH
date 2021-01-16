cmake_minimum_required(VERSION 3.9)

project(duh)
set(32BLIT_PATH "../" CACHE PATH "Path to 32blit.cmake")
set(DUH_SOURCE
  duh.cpp
)

if(NOT EXISTS ${32BLIT_PATH}/32blit.cmake)
  message(FATAL_ERROR "Define location of 32Blit API with -D32BLIT_PATH=<path to 32blit.cmake>")
endif()
include(${32BLIT_PATH}/32blit.cmake)

add_library(DUH STATIC ${DUH_SOURCE})
target_include_directories(DUH PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(DUH BlitEngine)