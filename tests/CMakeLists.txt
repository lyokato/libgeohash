INCLUDE_DIRECTORIES(${geohash_SOURCE_DIR}/include)

FILE(GLOB test_files ${geohash_SOURCE_DIR}/tests/*.c)
FOREACH(filename ${test_files})
    GET_FILENAME_COMPONENT(testname ${filename} NAME_WE)
    ADD_EXECUTABLE(${testname} ${filename})
    TARGET_LINK_LIBRARIES("${testname}" cunit geohash)
    ADD_TEST(${testname} "${geohash_BINARY_DIR}/tests/${testname}")
ENDFOREACH()
