set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(CUNIT REQUIRED)

file(GLOB test_files *.c)

foreach(filename ${test_files})
	get_filename_component(testname
		${filename} NAME_WE
		)

	add_executable(${testname}
		${filename}
		)

	target_link_libraries("${testname}"
		cunit geohash_static
		)

	add_test(${testname}
		"${CMAKE_BINARY_DIR}/bin/${testname}"
		)
endforeach()
