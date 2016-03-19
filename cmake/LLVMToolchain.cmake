include(${CMAKE_CURRENT_LIST_DIR}/LLVMEnvironment.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ClangLibs.cmake)

set(CMAKE_C_COMPILER    "clang-${LLVM_VERSION}"       )
set(CMAKE_CXX_COMPILER  "clang++-${LLVM_VERSION}"     )
set(CMAKE_LINKER        "llvm-link-${LLVM_VERSION}"   )
set(CMAKE_AR            "llvm-ar-${LLVM_VERSION}"     )
set(CMAKE_NM            "llvm-nm-${LLVM_VERSION}"     )
set(CMAKE_OBJDUMP       "llvm-objdump-${LLVM_VERSION}")
set(CMAKE_RANLIB        "llvm-ranlib-${LLVM_VERSION}" )

set(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} ${LLVM_C_FLAGS}"                           )
set(CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}"                       )
set(CMAKE_EXE_LINKER_FLAGS      "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}"   )
set(CMAKE_MODULE_LINKER_FLAGS   "${CMAKE_MODULE_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}")
set(CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}")
set(CMAKE_STATIC_LINKER_FLAGS   "${CMAKE_STATIC_LINKER_FLAGS} ${LLVM_LD_FLAGS} ${CLANG_LIBS}")

set(CMAKE_C_LINK_EXECUTABLE     "<CMAKE_C_COMPILER> -o <TARGET> <OBJECTS> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>"    )
set(CMAKE_CXX_LINK_EXECUTABLE   "<CMAKE_CXX_COMPILER> -o <TARGET> <OBJECTS> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>")