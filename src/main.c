#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <geohash/geohash.h>

void show_usage()
{
    fprintf(stderr, "usage: \n");
    fprintf(stderr, "    geohash 'hash'\n\n");
    fprintf(stderr, "example: \n");
    fprintf(stderr, "    geohash c216ne\n");
    fprintf(stderr, "    geohash c23nb62w20sth\n");
    fprintf(stderr, "    geohash xn774c06kdtve\n");
}

void show_area(const char *hash)
{
    GEOHASH_area *area;
    area = GEOHASH_decode(hash);
    printf("=========================================\n");
    printf("AREA\n");
    printf("-----------------------------------------\n");
    printf("MAX LATITUDE:   %f\n", area->latitude.max);
    printf("MIN LATITUDE:   %f\n", area->latitude.min);
    printf("MAX longitude: %f\n", area->longitude.max);
    printf("MIN longitude: %f\n", area->longitude.min);
    GEOHASH_free_area(area);
}

void show_neighbors(const char *hash)
{

    GEOHASH_neighbors *neighbors;
    neighbors = GEOHASH_get_neighbors(hash);
    printf("=========================================\n");
    printf("NEIGHBORS\n");
    printf("-----------------------------------------\n");
    printf("NORTH:        %s\n", neighbors->north);
    printf("SOUTH:        %s\n", neighbors->south);
    printf("WEST:         %s\n", neighbors->west);
    printf("EAST:         %s\n", neighbors->east);
    printf("NORTH_WEST:   %s\n", neighbors->north_west);
    printf("NORTH_EAST:   %s\n", neighbors->north_east);
    printf("SOUTH_WEST:   %s\n", neighbors->south_west);
    printf("SOUTH_EAST:   %s\n", neighbors->south_east);
    GEOHASH_free_neighbors(neighbors);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "no argument\n\n");
        show_usage();
        return EXIT_FAILURE;
    }

    if (!GEOHASH_verify_hash(argv[1])) {
        fprintf(stderr, "invalid hash: %s\n\n", argv[1]);
        show_usage();
        return EXIT_FAILURE;
    }

    show_area(argv[1]);
    show_neighbors(argv[1]);

    return EXIT_SUCCESS;
}

