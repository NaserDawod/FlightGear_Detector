#include "HybridAnomalyDetector.h"
float HybridAnomalyDetector::saveThreshold(Point *points[],int lenVal, Line l, float p){
    if(p>=0.9){
        return SimpleAnomalyDetector::saveThreshold(points, lenVal, l, p);
    }
    else {

        Circle c = findMinCircle(points, lenVal);
        center = new Point(c.center.x, c.center.y);
        return (c.radius * (float) 1.1);
    }
}

float HybridAnomalyDetector::distance(Point p, correlatedFeatures cor){
    if(cor.corrlation >= 0.9){
        return SimpleAnomalyDetector::distance(p,cor);
    }
    return dis(p, *center);
}

