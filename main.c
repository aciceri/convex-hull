#include <stdio.h>
#include "algorithm.h"

int main(int argc, char** argv) {
    if(argc != 3) {
        perror("Error: you must specify the filenames!");
        return -1;
    }

    /*tPoint *a = (tPoint *) malloc(sizeof(tPoint));
    tPoint *b = (tPoint *) malloc(sizeof(tPoint));
    a->x = 0;
    a->y = 1;
    b->x = 1;
    b->y = 1;
    printf("%d\n", comp((void *)a, (void *)b));*/

    tPointsCloud pc = readPointsFromFile(argv[1]);
    tPointsCloud hull = computeConvexHull(pc);

    writeHullOnFile(hull, argv[2]);

    return 0;
}
