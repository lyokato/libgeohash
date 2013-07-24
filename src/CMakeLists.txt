set(include_path ${CMAKE_SOURCE_DIR}/include/geohash/ )

file(GLOB LIBRARY_HEADERS ${include_path}/*.h)

# Dynamic library
add_library( geohash_dynamic SHARED
   geohash
   )

target_link_libraries( geohash_dynamic )

set_target_properties(geohash_dynamic
   PROPERTIES
   OUTPUT_NAME geohash
   PUBLIC_HEADER ${LIBRARY_HEADERS}
   )

install( TARGETS geohash_dynamic
   LIBRARY DESTINATION lib
   )

# Static library
add_library( geohash_static
   geohash
   )

target_link_libraries( geohash_static )

set_target_properties(geohash_static
   PROPERTIES
   OUTPUT_NAME geohash
   PUBLIC_HEADER ${LIBRARY_HEADERS}
   )

install( TARGETS geohash_static
   ARCHIVE DESTINATION lib
   PUBLIC_HEADER DESTINATION include
   )

# Executable
add_executable( geohash
   main
   )

target_link_libraries( geohash
   geohash_static
   )
