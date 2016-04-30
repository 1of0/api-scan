cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE cmake/LLVMToolchain.cmake)

project(api-scan)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

set(SOURCE_FILES
	Main.cpp Main.h
	FunctionScanner.cpp FunctionScanner.h
	FunctionInfoASTConsumer.cpp FunctionInfoASTConsumer.h
	Translator.cpp Translator.h
	XmlFormatter.cpp XmlFormatter.h
	Util.cpp Util.h
)

include_directories(
	${CMAKE_SOURCE_DIR}/libs/tclap/include
)

add_executable(api-scan ${SOURCE_FILES})
