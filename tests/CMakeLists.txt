macro(equilibrium_test module)
	set(test_name test_${module})
	add_executable(${test_name} ${CMAKE_CURRENT_SOURCE_DIR}/${test_name}.c)
	target_link_libraries(${test_name} equilibrium)
	add_test(NAME ${test_name} COMMAND ${test_name})
	message(STATUS "\tTest about '${module}' added")
endmacro()

equilibrium_test(rbtree)
