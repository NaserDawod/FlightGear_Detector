#include "string"
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include <vector>

using namespace std;
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    threshold = 0.9;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    const vector<string>& names = ts.getNames();
    int lenName = ts.getsize();  // num values
    int lenVal = ts.getMap().find(names[0])->second.size();  //for - names ////check here
    float data[lenName][lenVal];
    for(int i =0; i<lenVal; i++){
        for(int j = 0; j < lenName; j++){
            data[j][i] = ts.getMap().find(names[j])->second[i];
        }
    }
    for(int i =0; i<lenName; i++){
        int c = (-1);
        float m = 0;
        for(int j = i + 1; j<lenName; j++){
            float p = pearson(data[i], data[j], lenVal);
            if(p < 0){
                p = p * (-1);
            }
            if(p > m) {
                m = p;
                c = j;
            }
        }
        if (m > 0.5) {
            Point *points[lenVal] ;
            for (int k = 0;k<lenVal;k++) {
                Point *p = new Point(data[i][k],data[c][k]);
                points[k] = p;
            }
            Line l = linear_reg(points,lenVal);
            float maxdis = saveThreshold(points, lenVal, l, m);
            struct correlatedFeatures f = {names[i] ,names[c],m,l, maxdis , points};
            cor.push_back(f);
        }
    }
}
float SimpleAnomalyDetector::saveThreshold(Point *points[],int lenVal, Line l, float p){
    float maxdis = 0;
    for (int j = 0; j < lenVal; ++j) {
        float dis = dev(*points[j], l) ;
        if(dis > maxdis){
            maxdis = dis;
        }
    }
    maxdis = maxdis * (1.1);
    return maxdis;
}

float SimpleAnomalyDetector::distance(Point p, correlatedFeatures cor){
    float distance = dev(p, cor.lin_reg);
    return distance;
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts) {
    vector<AnomalyReport> reports;
    int lenCor = cor.size();
    for (int k = 0; k < lenCor; ++k) {
        vector<float> f1 = ts.getMap().find(cor[k].feature1)->second;
        vector<float> f2 = ts.getMap().find(cor[k].feature2)->second;
        int len = f1.size();
        for (int i = 0; i < len; i++) {
            float dist = distance(Point(f1[i], f2[i]), cor[k]);
            if (dist > cor[k].threshold) {
                string s = cor[k].feature1 + "-" + cor[k].feature2;
                AnomalyReport re(s, (i + 1));
                reports.push_back(re);
            }
        }
    }
    return reports;
}

vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel(){
    return cor;
}

