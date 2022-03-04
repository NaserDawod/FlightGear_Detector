#include "timeseries.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
TimeSeries::TimeSeries (const char *csv) {
    ifstream csv_file;
    csv_file.open(csv);
    if(!csv_file.is_open()) throw std::runtime_error("Could not open file");
    string line, name, value;
    if(csv_file.good()) {
        getline(csv_file, line);
        stringstream ss(line);
        while(getline(ss, name, ',')){
            vector<float> vec;
            time_series[name] = vec;
            names.push_back(name);
        }
    }
    while (getline(csv_file,line)) {
        stringstream ss(line);
        vector<string>::iterator it = names.begin();
        while(getline(ss, value, ',')){
            float x = stof(value);
            time_series.find(*it)->second.push_back(x);
            ++it;
        }
    }
    csv_file.close();
}

const map<string, vector<float>>& TimeSeries::getMap() const{
    return time_series;
}

const vector<string>& TimeSeries::getNames() const{
    return names;
}
int TimeSeries::getsize() const{
    return names.size();
}
