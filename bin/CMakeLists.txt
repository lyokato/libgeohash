INCLUDE_DIRECTORIES(${geohash_SOURCE_DIR}/include)

FILE(GLOB test_files ${geohash_SOURCE_DIR}/tests/*.c)
ADD_EXECUTABLE(geohash ${geohash_SOURCE_DIR}/bin/geohash.c)
TARGET_LINK_LIBRARIES(geohash geohash)
INSTALL(TARGETS geohash DESTINATION bin)

