//Niv Nahman 318012564 and Dvir Amram 318192200
#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <fstream>
#include <sstream>
#include <vector>
#include "iostream"
#include "map"
using namespace std;

class TimeSeries {
    map<string, vector<float>> table;
    vector<string> keys;
public:
    TimeSeries(string CSVfileName);
    TimeSeries(const char *CSVfileName);
    map<string, vector<float>> getMap() const;
    vector<string> getKeys() const;

};
#endif /* TIMESERIES_H_ */
