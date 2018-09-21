#include <stdio.h>
#include "algorithm.h"

int main(int argc, char** argv) {
    if(argc != 3) {
        perror("Error: you must specify the filenames!");
        return -1;
    }

    tPointsCloud pc = readPointsFromFile(argv[1]);  
    tPointsCloud hull = computeConvexHull(pc);

    writeHullOnFile(hull, argv[2]);

    return 0;
}
