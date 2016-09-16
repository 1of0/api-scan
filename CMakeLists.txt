cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE cmake/LLVMToolchain.cmake)

project(api-scan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

file(GLOB SOURCE_FILES
    src/*.h
    src/*.cpp
)

include_directories(
	${CMAKE_SOURCE_DIR}/libs/tclap/include
)

add_executable(api-scan ${SOURCE_FILES})
