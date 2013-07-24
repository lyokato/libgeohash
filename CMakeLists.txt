cmake_minimum_required (VERSION 2.8)

#
# geohash project
project ( geohash )

#
# Set build output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
# Build as Position Independent Code
add_definitions(-fPIC)

#
# Add build targets swtich between build types
ADD_CUSTOM_TARGET(debug
	${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${PROJECT_SOURCE_DIR})

ADD_CUSTOM_TARGET(release
	${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${PROJECT_SOURCE_DIR})

ADD_CUSTOM_TARGET(relwithdebinfo
	${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo ${PROJECT_SOURCE_DIR})

ADD_CUSTOM_TARGET(minsizerel
	${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=MinSizeRel ${PROJECT_SOURCE_DIR})

#
# Toggle verbosity
ADD_CUSTOM_TARGET(verbose
	${CMAKE_COMMAND} -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE ${PROJECT_SOURCE_DIR})

ADD_CUSTOM_TARGET(quiet
	${CMAKE_COMMAND} -DCMAKE_VERBOSE_MAKEFILE:BOOL=FALSE ${PROJECT_SOURCE_DIR})

#
# Include paths
include_directories(
	${CMAKE_BINARY_DIR}/include
	)

#
# Include paths
link_directories(
	${CMAKE_BINARY_DIR}/lib
	)

#
# Generate uninstall manifest
configure_file(
	"${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

#
# Uninstall target
add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_uninstall.cmake)

#
# Set warning levels
add_definitions(
	-pedantic
	-pedantic-errors
	-Wall
	-Wextra
	-Werror
	-Wno-missing-field-initializers
	)

#
# Generate uninstall manifest
configure_file(
	"${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

#
# Import development build over-rides
include(config.cmake OPTIONAL)

#
# Add source directory
add_subdirectory(src)

#
# Enable CTest test runner
enable_testing()

#
# Add test directory
add_subdirectory(tests)

