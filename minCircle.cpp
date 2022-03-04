#include "minCircle.h"
#include <math.h>

float dis(Point p1, Point p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

float slope(Point p1, Point p2){
    return (p1.y-p2.y)/(p1.x-p2.x);
}

Circle twoPointsCircle(Point p1, Point p2){
    Point center((p1.x+p2.x)/2, (p1.y+p2.y)/2);
    float r = dis(p1,p2)/2;
    return Circle(center,r);
}

Circle threePointsCircle(Point p1, Point p2, Point p3) {
    Point mid12((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    Point mid13((p1.x + p3.x) / 2, (p1.y + p3.y) / 2);
    Point mid23((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);
    float m1 = (-1) / (slope(p1, p2));
    float m2 = (-1) / (slope(p1, p3));
    float m3 = (-1) / (slope(p2, p3));
    if(p1.x == p2.x){
        mid12 = mid23;
        m1 = m3;
    }
    float x = (m1* mid12.x - mid12.y - m2*mid13.x + mid13.y) / (m1 - m2);
    float y = -m1* mid12.x + mid12.y + m1*x;
    Point center(x,y);
    float r = dis(center, p1);
    return Circle(center,r);
}

Circle simplePointsCircle(vector<Point> points){
    Circle c1 = twoPointsCircle(points[0],points[1]);
    if(dis(points[2], c1.center) <= c1.radius)
        return c1;
    Circle c2 = twoPointsCircle(points[0],points[2]);
    if(dis(points[1], c2.center) <= c2.radius)
        return c2;
    Circle c3 = twoPointsCircle(points[1],points[2]);
    if(dis(points[0], c3.center) <= c3.radius)
        return c3;
    return threePointsCircle(points[0],points[1],points[2]);
}

void swap(Point** points,size_t i, size_t j){
    Point* temp = points[i];
    points[i] = points[j];
    points[j] = temp;
}

Circle helpFIndMinCircle(Point** points, vector<Point> Rpoints,size_t size){
    if(size == 0 || Rpoints.size() == 3) {
        int sizeR = Rpoints.size();
        if(sizeR == 0){
            return Circle(Point(0,0),0);
        }
        if(sizeR == 1){
            return Circle(Rpoints[0], 0);
        }
        if(sizeR == 2){
            return twoPointsCircle(Rpoints[0], Rpoints[1]);
        }
        return simplePointsCircle(Rpoints);
    }
    int i = rand() % size;
    Point p = *points[i];
    swap(points,i, (size - 1));
    Circle c = helpFIndMinCircle(points,Rpoints, size-1);
    if (dis(p, c.center) <= c.radius){
        return c;
    }
    Rpoints.push_back(p);
    return helpFIndMinCircle(points,Rpoints, size-1);
}

Circle findMinCircle(Point** points,size_t size){
    vector<Point> Rpoints;
    return helpFIndMinCircle(points,Rpoints,size);
}

