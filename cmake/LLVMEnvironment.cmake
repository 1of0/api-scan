include(${CMAKE_CURRENT_LIST_DIR}/Utils.cmake)

if (DEFINED LLVM_VERSION)
	set(VERSION_POSTFIX "-${LLVM_VERSION}")
endif()

set(LLVM_CONFIG "llvm-config${VERSION_POSTFIX}")

exec("${LLVM_CONFIG}"   "--includedir"    LLVM_INCLUDE_DIR)
exec("${LLVM_CONFIG}"   "--libs"          LLVM_LIBS       )
exec("${LLVM_CONFIG}"   "--system-libs"   LLVM_SYS_LIBS   )
exec("${LLVM_CONFIG}"   "--cflags"        LLVM_C_FLAGS    )
exec("${LLVM_CONFIG}"   "--cxxflags"      LLVM_CXX_FLAGS  )
exec("${LLVM_CONFIG}"   "--ldflags"       LLVM_LD_FLAGS   )
exec("${LLVM_CONFIG}"   "--src-root"      LLVM_SRC_ROOT   )