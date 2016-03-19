#
# Wrapper around execute_process() that strips the output
#
function(EXEC COMMAND ARGS OUTPUT)
	execute_process(COMMAND "${COMMAND}" "${ARGS}" OUTPUT_VARIABLE TEMP)
	string(STRIP "${TEMP}" TEMP)
	set(${OUTPUT} ${TEMP} PARENT_SCOPE)
endfunction()
