cmake_minimum_required(VERSION 3.9)
project(solve)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)

set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_WOLFRAM_DIR ${APP_ROOT_DIR}/../../Wolfram)
include_directories(${APP_ROOT_WOLFRAM_DIR})

add_subdirectory(${APP_ROOT_WOLFRAM_DIR} build)

add_executable(solve main.cpp)

target_link_libraries(solve Wolfram)
target_link_libraries(solve curl)
