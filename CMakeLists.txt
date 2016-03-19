cmake_minimum_required(VERSION 3.3)

set(CMAKE_TOOLCHAIN_FILE cmake/clang.cmake)

project(libsodium_interface_parser)

set(SOURCE_FILES main.cpp)
add_executable(libsodium_interface_parser ${SOURCE_FILES})