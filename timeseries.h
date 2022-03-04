

#ifndef FLIGHTGEAR_DETECTOR1_TIMESERIES_H
#define FLIGHTGEAR_DETECTOR1_TIMESERIES_H
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
class TimeSeries{
    map<string, vector<float>> time_series;
    vector<string> names;
public:
    TimeSeries(const char* csv);

    const map<string, vector<float>>& getMap() const;

    const vector<string>& getNames() const;

    int getLines(){
        return time_series.find(names[0])->second.size();
    }

    int getsize() const;
};
#endif //FLIGHTGEAR_DETECTOR1_TIMESERIES_H
