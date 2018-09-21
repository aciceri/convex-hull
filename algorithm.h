#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    double x, y;
} tPoint;

typedef struct {
    unsigned int n;
    tPoint* point; 
} tPointsCloud;

typedef struct tPointsList{
    tPoint point;
    struct tPointsList *next, *prev;
} tPointsList;


tPointsCloud readPointsFromFile(const char* filename);
tPoint computeCentroid(tPointsCloud pc);
tPointsList* sortPoints(tPointsCloud pc, tPoint centroid);
double isConvexAngle(tPoint a, tPoint b, tPoint c);
tPointsCloud computeConvexHull(tPointsCloud pc);
void writeHullOnFile(tPointsCloud hull, const char* filename); 
