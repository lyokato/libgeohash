INCLUDE_DIRECTORIES(${geohash_SOURCE_DIR}/include)

FILE(GLOB src_files ${geohash_SOURCE_DIR}/src/*.c)
ADD_LIBRARY(geohash_dynamic SHARED ${src_files})
ADD_LIBRARY(geohash_static STATIC ${src_files})

SET_TARGET_PROPERTIES(geohash_dynamic PROPERTIES OUTPUT_NAME geohash)

FILE(GLOB header_files ${geohash_SOURCE_DIR}/include/*.h)
INSTALL(FILES ${header_files} DESTINATION include)
INSTALL(TARGETS geohash_dynamic DESTINATION lib)

