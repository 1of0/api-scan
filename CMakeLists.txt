cmake_minimum_required(VERSION 3.3)

set(CMAKE_TOOLCHAIN_FILE cmake/clang.cmake)

project(libsodium_interface_parser)

set(INCLUDE_DIRECTORIES
	${CLANG_INCLUDE_DIR}
	${CLANG_SRC_ROOT}include/clang
)

message(WARNING ${CMAKE_CXX_LINK_EXECUTABLE})

include_directories(${INCLUDE_DIRECTORIES})

set(SOURCE_FILES main.cpp)
add_executable(libsodium_interface_parser ${SOURCE_FILES})