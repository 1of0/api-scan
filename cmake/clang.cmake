set(LLVM_VERSION    "3.7")
set(LLVM_CONFIG     "llvm-config-${LLVM_VERSION}")

execute_process(COMMAND ${LLVM_CONFIG} --includedir     OUTPUT_VARIABLE LLVM_INCLUDE_DIR)
execute_process(COMMAND ${LLVM_CONFIG} --libs           OUTPUT_VARIABLE LLVM_LIBS       )
execute_process(COMMAND ${LLVM_CONFIG} --system-libs    OUTPUT_VARIABLE LLVM_SYS_LIBS   )
execute_process(COMMAND ${LLVM_CONFIG} --cflags         OUTPUT_VARIABLE LLVM_C_FLAGS    )
execute_process(COMMAND ${LLVM_CONFIG} --cxxflags       OUTPUT_VARIABLE LLVM_CXX_FLAGS  )
execute_process(COMMAND ${LLVM_CONFIG} --ldflags        OUTPUT_VARIABLE LLVM_LD_FLAGS   )
execute_process(COMMAND ${LLVM_CONFIG} --src-root       OUTPUT_VARIABLE LLVM_SRC_ROOT   )

string(STRIP "${LLVM_INCLUDE_DIR}"   LLVM_INCLUDE_DIR   )
string(STRIP "${LLVM_LIBS}"          LLVM_LIBS          )
string(STRIP "${LLVM_SYS_LIBS}"      LLVM_SYS_LIBS      )
string(STRIP "${LLVM_C_FLAGS}"       LLVM_C_FLAGS       )
string(STRIP "${LLVM_CXX_FLAGS}"     LLVM_CXX_FLAGS     )
string(STRIP "${LLVM_LD_FLAGS}"      LLVM_LD_FLAGS      )
string(STRIP "${LLVM_SRC_ROOT}"      LLVM_SRC_ROOT      )

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

set(CMAKE_C_COMPILER    "clang-${LLVM_VERSION}"         )
set(CMAKE_CXX_COMPILER  "clang++-${LLVM_VERSION}"       )
set(CMAKE_LINKER        "llvm-link-${LLVM_VERSION}"     )
set(CMAKE_AR            "llvm-ar-${LLVM_VERSION}"       )
set(CMAKE_NM            "llvm-nm-${LLVM_VERSION}"       )
set(CMAKE_OBJDUMP       "llvm-objdump-${LLVM_VERSION}"  )
set(CMAKE_RANLIB        "llvm-ranlib-${LLVM_VERSION}"   )

set(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS}   ${LLVM_C_FLAGS}"    )
set(CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}"  )
set(CMAKE_EXE_LINKER_FLAGS      "${CMAKE_EXE_LINKER_FLAGS}    ${LLVM_LD_FLAGS} ${CLANG_LIBS}")
set(CMAKE_MODULE_LINKER_FLAGS   "${CMAKE_MODULE_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}")
set(CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}")
set(CMAKE_STATIC_LINKER_FLAGS   "${CMAKE_STATIC_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}")

set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> -o <TARGET> <OBJECTS> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>"       )
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> -o <TARGET> <OBJECTS> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>" )

include_directories(
	${CLANG_INCLUDE_DIR}
	${CLANG_SRC_ROOT}include/clang
)