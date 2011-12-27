#include "libgeohash.h"
#include <stdlib.h>

int 
main(int argc, char** argv)
{
    char *hash;
    GEOHASH_area *area;
    GEOHASH_neighbors *neighbors;

    area = GEOHASH_decode("");
    if (area == NULL)
        return EXIT_SUCCESS;

    GEOHASH_release_area(area);

    hash = GEOHASH_encode();
    neighbors = GEOHASH_get_neighbors(hash);
    neighbors->north;
    neighbors->east;
    neighbors->west;
    neighbors->south;
    neighbors->north_east;
    neighbors->north_west;
    neighbors->south_east;
    neighbors->south_west;

    GEOHASH_release_neighbors(neighbors);

    return EXIT_SUCCESS;
}
