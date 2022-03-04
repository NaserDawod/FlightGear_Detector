

#ifndef FLIGHTGEAR_DETECTOR1_SIMPLEANOMALYDETECTOR_H
#define FLIGHTGEAR_DETECTOR1_SIMPLEANOMALYDETECTOR_H
#include "timeseries.h"
#include "string"
#include "vector"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
using namespace std;
struct correlatedFeatures{
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Point **points;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector{
    float threshold;
    vector<correlatedFeatures> cor;
public:
    SimpleAnomalyDetector();
    ~SimpleAnomalyDetector(){}
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
    virtual float saveThreshold(Point *points[],int lenVal, Line l, float p);
    virtual float distance(Point p, correlatedFeatures cor);
    void setThreshold(float newThreshold){
        threshold = newThreshold;
    }
};
#endif //FLIGHTGEAR_DETECTOR1_SIMPLEANOMALYDETECTOR_H
