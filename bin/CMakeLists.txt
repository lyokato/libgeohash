INCLUDE_DIRECTORIES(${geohash_SOURCE_DIR}/include)

ADD_EXECUTABLE(geohash ${geohash_SOURCE_DIR}/src/geohash.c ${geohash_SOURCE_DIR}/bin/geohash.c)
TARGET_LINK_LIBRARIES(geohash geohash_dynamic)
INSTALL(TARGETS geohash DESTINATION bin)

