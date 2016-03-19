include(${CMAKE_CURRENT_LIST_DIR}/Utils.cmake)

if (NOT DEFINED LLVM_VERSION)
	set(LLVM_VERSION "3.7")
endif()

set(LLVM_CONFIG "llvm-config-${LLVM_VERSION}")

exec("${LLVM_CONFIG}"   "--includedir"    LLVM_INCLUDE_DIR)
exec("${LLVM_CONFIG}"   "--libs"          LLVM_LIBS       )
exec("${LLVM_CONFIG}"   "--system-libs"   LLVM_SYS_LIBS   )
exec("${LLVM_CONFIG}"   "--cflags"        LLVM_C_FLAGS    )
exec("${LLVM_CONFIG}"   "--cxxflags"      LLVM_CXX_FLAGS  )
exec("${LLVM_CONFIG}"   "--ldflags"       LLVM_LD_FLAGS   )
exec("${LLVM_CONFIG}"   "--src-root"      LLVM_SRC_ROOT   )