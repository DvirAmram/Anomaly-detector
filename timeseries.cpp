//Niv Nahman 318012564 and Dvir Amram 318192200
#include "timeseries.h"
#include <iostream>
#include <vector>
#include "string"
#include <map>
/**
 * @param CSVfileName the file we got
 * the function builds a data structure(map) in our case.
 */
TimeSeries::TimeSeries(const char *CSVfileName) {
    ifstream file;
    file.open(CSVfileName);
    std::ifstream fin(CSVfileName);
    if (!fin) {
        std::cout << "Error, could not open file." << std::endl;
    }
    string line, word;
    std::getline(file, line);
    stringstream s(line);
    while(getline(s,word,',')){
        vector<float> vec;
        table.insert(pair<string ,vector<float>>(word,vec));
        keys.push_back(word);
    }
    while(getline(file, line)){
        stringstream s(line);
        getline(s,word,',');
        for (string key : keys) {
            table.find(key)->second.push_back(std::stof(word));
            getline(s,word,',');
        }
    }
}
/**
 * @return the table
 */
    map<string, vector<float>> TimeSeries::getMap() const{
        return table;
    }
    /**
     * @return gets the vector of the keys
     */
    vector<string> TimeSeries::getKeys() const{
        return keys;
    }