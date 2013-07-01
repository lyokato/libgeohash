#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/Basic.h>
#include "geohash.h"
#include <stdlib.h>
#include "stdio.h"

void verify_hash(double lat, double lon, int len, const char* expected)
{
    char *hash;
    hash = GEOHASH_encode(lat, lon, len);
    CU_ASSERT_STRING_EQUAL(hash, expected);
    free(hash);
    //CU_ASSERT_PTR_NULL();
}

void test_geohash_encode(void)
{
    verify_hash(       45.37,       -121.7,  6, "c216ne"        );
    verify_hash(  47.6062095, -122.3320708, 13, "c23nb62w20sth" );
    verify_hash(  35.6894875,  139.6917064, 13, "xn774c06kdtve" );
    verify_hash( -33.8671390,  151.2071140, 13, "r3gx2f9tt5sne" );
    verify_hash(  51.5001524,   -0.1262362, 13, "gcpuvpk44kprq" );
}

void verify_area(
        const char *hash, 
        double lat_min, double lon_min, 
        double lat_max, double lon_max)
{
    GEOHASH_area *area;
    area = GEOHASH_decode(hash);
    CU_ASSERT_DOUBLE_EQUAL(area->latitude.max,   lat_max, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(area->latitude.min,   lat_min, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(area->longitude.max, lon_max, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(area->longitude.min, lon_min, 0.001);
    GEOHASH_free_area(area);
}

void test_geohash_decode(void)
{
    verify_area("c216ne", 45.3680419921875, -121.70654296875, 45.37353515625, -121.695556640625);
    verify_area("C216Ne", 45.3680419921875, -121.70654296875, 45.37353515625, -121.695556640625);
    verify_area("dqcw4", 39.0234375, -76.552734375, 39.0673828125, -76.5087890625);
    verify_area("DQCW4", 39.0234375, -76.552734375, 39.0673828125, -76.5087890625);
}

void verify_adjacent(const char *origin, GEOHASH_direction dir, const char *expected)
{
    char *hash;
    hash = GEOHASH_get_adjacent(origin, dir);
    CU_ASSERT_STRING_EQUAL(hash, expected);
    free(hash);
}

void test_geohash_adjacent(void)
{
    verify_adjacent("dqcjq", GEOHASH_NORTH, "dqcjw");
    verify_adjacent("dqcjq", GEOHASH_SOUTH, "dqcjn");
    verify_adjacent("dqcjq", GEOHASH_WEST,  "dqcjm");
    verify_adjacent("dqcjq", GEOHASH_EAST,  "dqcjr");
}

void verify_neighbors(
        const char *origin,
        const char *hash1,
        const char *hash2,
        const char *hash3,
        const char *hash4,
        const char *hash5,
        const char *hash6,
        const char *hash7,
        const char *hash8
        )
{
    GEOHASH_neighbors *neighbors;
    neighbors = GEOHASH_get_neighbors(origin);

    CU_ASSERT_STRING_EQUAL(neighbors->north,      hash1);
    CU_ASSERT_STRING_EQUAL(neighbors->south,      hash2);
    CU_ASSERT_STRING_EQUAL(neighbors->west,       hash3);
    CU_ASSERT_STRING_EQUAL(neighbors->east,       hash4);
    CU_ASSERT_STRING_EQUAL(neighbors->north_west, hash5);
    CU_ASSERT_STRING_EQUAL(neighbors->north_east, hash6);
    CU_ASSERT_STRING_EQUAL(neighbors->south_west, hash7);
    CU_ASSERT_STRING_EQUAL(neighbors->south_east, hash8);

    GEOHASH_free_neighbors(neighbors);
}

void test_geohash_neighbors(void)
{
    verify_neighbors("dqcw5", "dqcw7", "dqctg", "dqcw4", "dqcwh", "dqcw6", "dqcwk", "dqctf", "dqctu");
    verify_neighbors("xn774c", "xn774f", "xn774b", "xn7749", "xn7751", "xn774d", "xn7754", "xn7748", "xn7750");
    verify_neighbors("gcpuvpk", "gcpuvps", "gcpuvph", "gcpuvp7", "gcpuvpm", "gcpuvpe", "gcpuvpt", "gcpuvp5", "gcpuvpj");
    verify_neighbors("c23nb62w", "c23nb62x", "c23nb62t", "c23nb62q", "c23nb62y", "c23nb62r", "c23nb62z", "c23nb62m", "c23nb62v");
}

void test_geohash_verification(void)
{
    CU_ASSERT_EQUAL(GEOHASH_verify_hash("dqcw5"), 1);
    CU_ASSERT_EQUAL(GEOHASH_verify_hash("dqcw7"), 1);
    CU_ASSERT_EQUAL(GEOHASH_verify_hash("abcwd"), 0);
    CU_ASSERT_EQUAL(GEOHASH_verify_hash("dqcw5@"), 0);
}

int main(int argc, char **argv)
{
    CU_pSuite suite;

    CU_initialize_registry();

    suite = CU_add_suite("GeoHashTestSuite", NULL, NULL);

    CU_add_test( suite, "GeoHashDecodeTest",       test_geohash_decode       );
    CU_add_test( suite, "GeoHashEncodeTest",       test_geohash_encode       );
    CU_add_test( suite, "GeoHashAdjacentTest",     test_geohash_adjacent     );
    CU_add_test( suite, "GeoHashNeighborsTest",    test_geohash_neighbors    );
    CU_add_test( suite, "GeoHashVerificationTest", test_geohash_verification );

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}
