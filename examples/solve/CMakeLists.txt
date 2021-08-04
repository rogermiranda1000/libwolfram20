cmake_minimum_required(VERSION 3.16)
project(solve)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE DEBUG)

set(APP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(APP_ROOT_WOLFRAM_DIR ${APP_ROOT_DIR}/../../Wolfram)
include_directories(${APP_ROOT_WOLFRAM_DIR})

add_library(Wolfram STATIC
	${APP_ROOT_WOLFRAM_DIR}/WAEngine.cpp
	${APP_ROOT_WOLFRAM_DIR}/WAImage.cpp
	${APP_ROOT_WOLFRAM_DIR}/WAPod.cpp
	${APP_ROOT_WOLFRAM_DIR}/WAPodState.cpp
	${APP_ROOT_WOLFRAM_DIR}/WAQuery.cpp
	${APP_ROOT_WOLFRAM_DIR}/WASubpod.cpp
)

add_executable(solve main.cpp)

target_link_libraries(solve Wolfram)
target_link_libraries(solve curl)
