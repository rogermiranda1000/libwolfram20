cmake_minimum_required(VERSION 3.9)

add_library(Wolfram STATIC
	WAEngine.cpp
	WAImage.cpp
	WAPod.cpp
	WAPodState.cpp
	WAQuery.cpp
	WASubpod.cpp
	WAResult.cpp
	WAError.cpp
)
