
#ifndef FLIGHTGEAR_DETECTOR1_HYBRIDANOMALYDETECTOR_H
#define FLIGHTGEAR_DETECTOR1_HYBRIDANOMALYDETECTOR_H
#include "SimpleAnomalyDetector.h"
#include "minCircle.h"
#include "SimpleAnomalyDetector.h"
#include "minCircle.h"
class HybridAnomalyDetector:public SimpleAnomalyDetector {
    Point *center;
public:
    HybridAnomalyDetector(){}
    virtual ~HybridAnomalyDetector(){
        delete center;
    }
    virtual float saveThreshold(Point *points[],int lenVal, Line l,float p);
    virtual float distance(Point p, correlatedFeatures cor);
};
#endif //FLIGHTGEAR_DETECTOR1_HYBRIDANOMALYDETECTOR_H
