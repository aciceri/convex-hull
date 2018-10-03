#include "algorithm.h"
#include <math.h>

tPointsCloud readPointsFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) perror("This file doesn't exist");
    tPointsCloud pc;
    pc.n=0;

    char ch;
    while(!feof(f)) {
        ch = fgetc(f);
        if(ch == '\n') pc.n++;
    }

    fseek(f, 0, SEEK_SET);


    pc.point = (tPoint*) malloc(sizeof(tPoint)*pc.n);
    for(int i=0; i<pc.n; i++)
        fscanf(f, "%lf %lf\n", &pc.point[i].x, &pc.point[i].y);

    fclose(f);

    return pc;
}

tPoint computeCentroid(tPointsCloud pc) {
    tPoint p;

    p.x = 0;
    p.y = 0;

    for(int i=0; i<pc.n; i++) {
        p.x += pc.point[i].x;
        p.y += pc.point[i].y;
    }
    p.x /= pc.n;
    p.y /= pc.n;

    return p;
}


double angle(tPoint p) {
    double x,y;
    x = p.x;
    y = p.y;
    if (x > 0 && y > 0)
        return atan(y / x);
    else if (x < 0 && y > 0)
        return atan(-x / y) + M_PI / 2;
    else if (x < 0 && y < 0)
        return atan(y / x) + M_PI;
    else if (x > 0 && y < 0)
        return atan(-x / y) + M_PI / 2 + M_PI;
    else if (x == 0 && y > 0)
        return M_PI / 2;
    else if (x < 0 && y == 0)
        return M_PI;
    else if (x == 0 && y < 0)
        return M_PI / 2 + M_PI;
    else return 0;

}

int comp(const void *p, const void *q) {
    double px = ((tPoint *) p)->x;
    double py = ((tPoint *) p)->y;
    double qx = ((tPoint *) q)->x;
    double qy = ((tPoint *) q)->y;

    /*if((-px*qy+py*qx)>0) return 1;
    else return -1;
    return 0;*/

	if(angle(*((tPoint *) p)) > angle(*((tPoint *) q))) return 1;
	else return -1;
}


tPointsList* sortPoints(tPointsCloud pc, tPoint centroid) {
    for(int i=0; i<pc.n; i++) {
        pc.point[i].x -= centroid.x;
        pc.point[i].y -= centroid.y;
    }

    qsort((void * ) pc.point, pc.n, sizeof(pc.point[0]), comp);

    for(int i=0; i<pc.n; i++)
        printf("%lf %lf %lf\n", pc.point[i].x, pc.point[i].y,
                atan((pc.point[i].y)/(pc.point[i].x)));

    tPointsList* l = (tPointsList *) malloc(sizeof(tPointsList));
    tPointsList* ptr = l;
    for(int i=0; i<pc.n; i++) {
        ptr->point = pc.point[i];
        ptr->point.x += centroid.x;
        ptr->point.y += centroid.y;

        if (i < pc.n-1) {
            ptr->next = (tPointsList *) malloc(sizeof(tPointsList));
            ptr->next->prev = ptr;
            ptr = ptr->next;
        }
        else
            ptr->next = l;
    }
    l->prev = ptr;

    return l;
}


int isConvexAngle(tPoint a, tPoint b, tPoint c) {
    //return (a.x-b.x)*(c.y-a.y)-(a.y-b.y)*(c.x-b.x) <= 0 ? 1 : 0;
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x) >= 0 ? 1 : 0;
}


tPointsCloud computeConvexHull(tPointsCloud pc) {
    tPoint centroid = computeCentroid(pc);
    tPointsList* l = sortPoints(pc, centroid);
    tPointsCloud hull;
    tPointsList *ptr = l;

    hull.n=0;
    hull.point = malloc(sizeof(tPoint));

	int i=0;
    do {
        if (!isConvexAngle(ptr->point, ptr->next->point, ptr->next->next->point)) {
            printf("fsd\n");
            ptr->next = ptr->next->next;
            free(ptr->next->prev);
            ptr->next->prev = ptr;
		}
        else {
            hull.n++;
            hull.point = realloc(hull.point, hull.n*sizeof(tPoint));
            hull.point[hull.n-1] = ptr->point;
            ptr = ptr->next;
        }
		i++;
    } while(i<=100);

    return hull;
}

void writeHullOnFile(tPointsCloud hull, const char* filename) {
    FILE* f = fopen(filename, "w");

    for(int i=0; i<hull.n; i++)
        fprintf(f, "%lf %lf\n", hull.point[i].x, hull.point[i].y);

    fprintf(f, "%lf %lf\n", hull.point[0].x, hull.point[0].y);

    fclose(f);
}
