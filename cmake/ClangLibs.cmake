include(${CMAKE_CURRENT_LIST_DIR}/LLVMEnvironment.cmake)

set(CLANG_LIBS
	-lclangTooling
	-lclangFrontendTool
	-lclangFrontend
	-lclangDriver
	-lclangSerialization
	-lclangCodeGen
	-lclangParse
	-lclangSema
	-lclangStaticAnalyzerFrontend
	-lclangStaticAnalyzerCheckers
	-lclangStaticAnalyzerCore
	-lclangAnalysis
	-lclangARCMigrate
	-lclangRewrite
	-lclangRewriteFrontend
	-lclangEdit
	-lclangAST
	-lclangLex
	-lclangBasic
	${LLVM_LIBS}
	${LLVM_SYS_LIBS}
	-lcurses
)
string(REPLACE ";" " " CLANG_LIBS "${CLANG_LIBS}")

include_directories(
	${CLANG_INCLUDE_DIR}
	${CLANG_SRC_ROOT}include/clang
)