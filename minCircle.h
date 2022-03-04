
#ifndef FLIGHTGEAR_DETECTOR1_MINCIRCLE_H
#define FLIGHTGEAR_DETECTOR1_MINCIRCLE_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "anomaly_detection_util.h"
using namespace std;
// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};

Circle findMinCircle(Point** points,size_t size);
Circle twoPointsCircle(Point p1, Point p2);
Circle threePointsCircle(Point p1, Point p2, Point p3);
Circle simplePointsCircle(vector<Point> points, int size);
float dis(Point p1, Point p2);
#endif //FLIGHTGEAR_DETECTOR1_MINCIRCLE_H
