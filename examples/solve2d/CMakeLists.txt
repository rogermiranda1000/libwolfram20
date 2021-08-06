cmake_minimum_required(VERSION 3.16)
project(solve2d)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)

set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_WOLFRAM_DIR ${APP_ROOT_DIR}/../../Wolfram)
include_directories(${APP_ROOT_WOLFRAM_DIR})

add_subdirectory(${APP_ROOT_WOLFRAM_DIR} build)

add_executable(solve2d main.cpp)

target_link_libraries(solve2d Wolfram)
target_link_libraries(solve2d curl)
