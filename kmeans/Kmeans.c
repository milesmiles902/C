#include < >
#include < >
#include "Kmeans.h"
#include "point.h"
#include "hashmap.h"

int n = 10;
int itters = 15;

const long points_number = 100000;

double dist(Point* p1, Point* p2) {
  Point p ={p1->x, p1->y};
  sub(&p, p2);
  double result = modulus(&p);
  return result;
}

void average(PointArray* xs, Point* ret) {
  long i;
  ret->x = xs->points[0].x;
  ret->y = xs->points[0].y;
  for (i=1; i<xs; i++) {
    add(ret, &(xs->points[i]);
  }
  divide(ret, xs->size);
  return;
}

long closest(Point* p, PointArray* choices) {
  long i;
  double minVal = dist(p, &(choices->points[0]);
  long min = 0;
  for (i=1; i < choices->size; i++) {
    double actualDist = dist(p, &(choices->points[i]));
    if (actualDist < minVal) {
      minVal = actualDist;
     min = i;
    }
  }
  return min;
}

void calcClusters( ) {}

void run ( ) {}


