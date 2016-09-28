cmake_minimum_required(VERSION 2.8)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_TOOLCHAIN_FILE cmake/LLVMToolchain.cmake)

project(api-scan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

file(GLOB SOURCE_FILES
    src/*.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/libs/tclap/include
)

add_executable(api-scan ${SOURCE_FILES})
