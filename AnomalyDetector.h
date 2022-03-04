
#ifndef FLIGHTGEAR_DETECTOR1_ANOMALYDETECTOR_H
#define FLIGHTGEAR_DETECTOR1_ANOMALYDETECTOR_H
#include "timeseries.h"
#include "string"
using namespace std;
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};
#endif //FLIGHTGEAR_DETECTOR1_ANOMALYDETECTOR_H
